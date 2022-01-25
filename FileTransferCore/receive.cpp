#include "receive.h"
Receive::Receive(qintptr handle, QObject *parent):Transfer(parent)
{
    this->handle = handle;
    setStatus(NotStarted);
}

void Receive::run()
{
    ///implement the multithreaded read function here
    qDebug() << "started receiving thread";
    socket = new QTcpSocket(nullptr);
    connect(socket, &QTcpSocket::disconnected, this, &Receive::disconnected);
    socket->setSocketDescriptor(handle);
    setTargetIP(socket->peerAddress().toString());
    readIncomingRequest();
    waitForUserResponse();
    respondToRequest(response); /// assume answer is yes for now

    /// @todo tell user a new request is available and wait for answer

    // now that user accepted file le's start
    numberOfReads = fileSize / stepSize;
    numberOfReads += (fileSize % stepSize != 0); // round to bigger int
    qDebug() << "numberOfReads = " << numberOfReads;
    QByteArray fileBuffer; /// store data to be written to file
    //int BufferWriteCount = 0; /// number of writes to fileBuffer
    QByteArray received_array;
    DataPacket received;

    //QFileInfo fileInfo;
    /// @todo add a directory to the beginning of the file name
    file = new QFile(m_path + fileName); /// attatching path to file name
    file->open(QIODevice::WriteOnly);
    //file->resize(fileSize);
    setStatus(Transfering);

    qDebug() << "receiving file";
    while(bytesRead < fileSize){
        if(exit){
            return;
        }
        socket->waitForReadyRead(2000);
        received_array = socket->readAll();
        if(!received_array.isEmpty()){
            //qDebug() << "read " <<  received_array.size() << " bytes";
            bytesRead += received_array.size();
            fileBuffer.append(received_array);
            if(fileBuffer.size() >= maxBufferSize){
                file->write(fileBuffer);
                fileBuffer.clear();
                //qDebug() << "total of " << bytesRead << "bytes were read";
                emit progressUpdated(bytesRead);
            }
        }

    }
    if(!fileBuffer.isEmpty()){
        file->write(fileBuffer);
        fileBuffer.clear();
    }
    emit progressUpdated(bytesRead);
    socket->write("");
    setStatus(Finished);
    file->close();
    qDebug() << "receive finished";

}

QString Receive::getDestIP()
{
    return m_targetIP;

}

const QString &Receive::path() const
{
    return m_path;
}

void Receive::setPath(const QString &newPath)
{
    m_path = newPath;
}

void Receive::onUserResponded(bool answer)
{
    if(answer){
        response = DataPacket::Yes;
    }else{
        response = DataPacket::No;
    }
    emit userResponded(); /// emit this signal to end the waiter event loop
}

void Receive::readIncomingRequest()
{
    setStatus(Pending);
    socket->waitForReadyRead(); /// wait 3 seconds for the incoming request

    QByteArray request = socket->readAll();
    DataPacket requestPacket;
    requestPacket.extractPacket(request); /// @todo maybe later check inside a loop
    fileName = requestPacket.fileName();
    fileSize = requestPacket.fileSize();
    emit newFileRequest(fileName, fileSize, targetIP());
}

void Receive::respondToRequest(DataPacket::AnswerType answer)
{
    DataPacket responsePacket;
    switch (answer) {
    case DataPacket::AnswerType::Yes:{
        responsePacket.setAcceptedResponse();
        break;
    }
    case DataPacket::AnswerType::No:{\
        break;
    }

    }
     // assume user said yes for now
    qDebug() <<"sending file request response";
    socket->write(responsePacket.Data());
    socket->waitForBytesWritten();
}

void Receive::waitForUserResponse()
{
    QEventLoop loop;
    connect(this, &Receive::userResponded, &loop, &QEventLoop::quit, Qt::QueuedConnection);
    loop.exec();

}

