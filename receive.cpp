#include "receive.h"
Receive::Receive(qintptr handle, QObject *parent):Transfer(parent)
{

    this->handle = handle;
    setStatus(NotStarted);
}

void Receive::run()
{
    ///implement the multithreaded read function here
    QTcpSocket *socket = new QTcpSocket(nullptr);
    socket->setSocketDescriptor(handle);
    setStatus(Pending);
    socket->waitForReadyRead(3000); /// wait 3 seconds for the incoming request

    QByteArray request = socket->readAll();
    DataPacket requestPacket;
    requestPacket.extractPacket(request); /// @todo maybe later check inside a loop
    fileName = requestPacket.fileName();
    fileSize = requestPacket.fileSize();
    emit newFileRequest(fileName, fileSize);
    if(!waitForAnswer()){
        //terminate the transfer here
        setStatus(Failed);
        return;
    }

    /// @todo tell user a new request is available and wait for answer

    // now that user accepted file le's start
    numberOfReads = fileSize / stepSize;
    numberOfReads += (fileSize % stepSize != 0); // round to bigger int
    QByteArray *buffer = new QByteArray;
    QByteArray received_array;
    DataPacket received;
    setStatus(Transfering);
    //QFileInfo fileInfo;
    /// @todo add a directory to the beginning of the file name
    file = new QFile(fileName);
    file->open(QIODevice::WriteOnly);
    for(int i = 0; i < numberOfReads; i++){
        int packetCount = 0;
        socket->waitForReadyRead();
        received_array = socket->readAll();
        while(received.extractPacket(received_array)){
            packetCount++;
            *buffer = received.getContent();
            file->write(*buffer);
            bytesRead += buffer->size();
            emit progressUpdated(bytesRead);
        } /// @todo change this to extract as much as it's empty
        if(packetCount > 1){ //this means more than one packet was received in a single read
            i += packetCount - 1;
        }

    }

    setStatus(Finished);
    file->close();
    file->deleteLater();
    socket->deleteLater();
    delete buffer;




}

QString Receive::getDestIP()
{
    return m_destIP;

}

quint8 Receive::completionPercent() const
{

}

void Receive::setCompletionPercent(quint8 newCompletionPercent)
{

}

bool Receive::waitForAnswer()
{
 ///@todo wait for a signal from user that says the file is accepted or rejected
 return true;
}

