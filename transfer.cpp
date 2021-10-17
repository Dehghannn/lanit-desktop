#include "transfer.h"
quint16 Transfer::transferCount = 0;
Transfer::Transfer(qintptr handle, QString fileName)
{

    this->handle = handle;
    this->fileName = fileName;
    setStatus(NotStarted);
    Receive = true;
}

Transfer::Transfer(QString Address, QString fileName)
{
    transferCount++;
    m_transferID = transferCount;
    this->fileName = fileName;
    setStatus(NotStarted);
    m_destIP = Address;
    Receive = false;

}

void Transfer::run()
{
    ///implement the multithreaded write function here
    QTcpSocket *socket = new QTcpSocket(nullptr);
    if(Receive){
        socket->setSocketDescriptor(handle);
    }else{

        QFile *file = new QFile(fileName);
        file->open(QIODevice::ReadOnly);
        QByteArray buffer;
        fileSize = file->size();
        qInfo() << "Sending file " << fileName;
        qInfo() << "by size of " << fileSize;
        numberOfWrites = fileSize / stepSize;
        numberOfWrites += (fileSize % stepSize != 0); // rounding to next integer
        setStatus(Pending);

        for(int i = 0; i < numberOfWrites; i++){

        }


    }



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
}

quint8 Transfer::completionPercent() const
{
    return m_completionPercent;
}

void Transfer::setCompletionPercent(quint8 newCompletionPercent)
{
    m_completionPercent = newCompletionPercent;
}
