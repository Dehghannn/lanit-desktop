#include "filetransferhandler.h"

FileTransferHandler::FileTransferHandler(QObject *parent) : QObject(parent)
{

}

void FileTransferHandler::sendFile(QString PathToFile, User user)
{
    QFile *sendingFile = new QFile(PathToFile);
    sendingFile->open(QIODevice::ReadOnly);
}
