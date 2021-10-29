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
    }
}

void FileTransferHandler::quit()
{
    this->close();
}

void FileTransferHandler::newOutgoingFile(QString address, QString fileName)
{
    Transfer *transferer = new Transfer(address, fileName, this);
    pool.start(transferer);
}

void FileTransferHandler::incomingConnection(qintptr handle)
{
    Receive *receiver = new Receive(handle, this);
    pool.start(receiver);
}
