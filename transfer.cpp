#include "transfer.h"
quint16 Transfer::transferCount = 0;
Transfer::Transfer(QString Address, QString fileName, QObject *parent):QObject(parent)
{
    transferCount++;
    m_transferID = transferCount;
    this->fileName = fileName;
    setStatus(NotStarted);
    m_destIP = Address;

}

void Transfer::run()
{
    ///implement the multithreaded write function here
    QTcpSocket *socket = new QTcpSocket(nullptr);
    QFile *file = new QFile(fileName, this);
    QFileInfo info;
    info.setFile(*file);
    fileSize = file->size();
    qInfo() << "Sending file " << fileName;
    qInfo() << "by size of " << fileSize;
    numberOfWrites = fileSize / stepSize;
    numberOfWrites += (fileSize % stepSize != 0); // rounding to next integer
    socket->connectToHost(m_destIP, port);
    if(!socket->waitForConnected(10000)){
        qInfo() << "failed to connect to receiver";
        qInfo() << socket->errorString();
        setStatus(Failed);
        /// @todo retry maybe
    }
    DataPacket packet;
    packet.setFileRequest(info.fileName(), info.size());
    socket->write(packet.Data());
    socket->waitForBytesWritten();
    setStatus(Pending);

    // wait a full minute for the receiver to answer request
    if(!socket->waitForReadyRead(60000)){
        // timeout happened
    }else{
        QByteArray answer = socket->readAll();
        DataPacket responsePacket;
        responsePacket.extractPacket(answer);
        /// @todo check if response is yes or no
    }


    //now that user accepted transfer let's start
    file->open(QIODevice::ReadOnly);
    QByteArray *buffer = new QByteArray;
    DataPacket sendPacket;
    for(int i = 0; i < numberOfWrites; i++){
        ///@todo send each part of file and update progress
        if(fileSize - bytesWritten > stepSize){ // check if remaining bytes are larger than a step
            *buffer = file->read(stepSize);
        }else{
            *buffer = file->read((fileSize - bytesWritten));
        }

        sendPacket.setFromFileData(*buffer);
        socket->write(sendPacket.Data());
        bytesWritten += buffer->size();
        emit progressUpdated(bytesWritten);

    }
    delete buffer;
    setStatus(Finished);
    file->close();
    file->deleteLater();
    socket->deleteLater();

}

QString Transfer::getDestIP()
{
    return m_destIP;
}

quint8 Transfer::status() const
{
    return m_status;
}

void Transfer::setStatus(quint8 newStatus)
{
    m_status = newStatus;
    emit statusChanged(newStatus);
}

quint8 Transfer::completionPercent() const
{
    return m_completionPercent;
}

void Transfer::setCompletionPercent(quint8 newCompletionPercent)
{
    m_completionPercent = newCompletionPercent;
}
