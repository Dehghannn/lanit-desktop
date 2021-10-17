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

void FileTransferHandler::newOutgoingFile(QString fileName)
{

}

void FileTransferHandler::incomingConnection(qintptr handle)
{

}
