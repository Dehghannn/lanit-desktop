#include "transfer.h"
quint16 Transfer::transferCount = 0;
Transfer::Transfer(QTcpSocket* socket, QString fileName)
{
    transferCount++;
    m_transferID = transferCount;
    this->socket = socket;
    this->fileName = fileName;
    setStatus(NotStarted);
    m_destIP = socket->peerAddress().toString();
}

void Transfer::run()
{
    ///implement the multithreaded write function here
    /// big issue: you can write to a socket from only the thread it lives in
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
