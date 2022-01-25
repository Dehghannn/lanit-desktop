#include "filetransferhandler.h"

FileTransferHandler::FileTransferHandler(int port, QObject *parent) : QTcpServer(parent)
{
    pool.setMaxThreadCount(20);
    this->port = port;
}

void FileTransferHandler::start()
{
    if(!this->listen(QHostAddress::AnyIPv4, port)){
        qCritical() << this->errorString();
        return;
    }
    qInfo() << "Started file server";
}

void FileTransferHandler::quit()
{
    this->close();
}

void FileTransferHandler::newOutgoingFile(QString address, QString fileName)
{
    Transfer *transferer = new Transfer(address, fileName, this);
    transferer->autoDelete();
    pool.start(transferer);
}

void FileTransferHandler::newOutgoingFile(QString address, QString fileName, FileMessage *fileMessage)
{
    Transfer *transferer = new Transfer(address, fileName, this);
    transferer->autoDelete();
    connect(transferer, &Transfer::progressUpdated, fileMessage, &FileMessage::updateProgress, Qt::QueuedConnection);
    pool.start(transferer);
}

const QString &FileTransferHandler::savePath() const
{
    return m_savePath;
}

void FileTransferHandler::setSavePath(const QString &newSavePath)
{
    m_savePath = newSavePath;
}

void FileTransferHandler::incomingConnection(qintptr handle)
{
    Receive *receiver = new Receive(handle, this);
    receiver->setPath(m_savePath);
    receiver->autoDelete();
    emit newIncomingFile(receiver);
    pool.start(receiver);
}
