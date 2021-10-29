#include "receive.h"
Receive::Receive(qintptr handle, QString fileName, QObject *parent):Transfer(parent)
{

    this->handle = handle;
    this->fileName = fileName;
    setStatus(NotStarted);
}



void Receive::run()
{
    ///implement the multithreaded read function here
    QTcpSocket *socket = new QTcpSocket(nullptr);
    socket->setSocketDescriptor(handle);


    setStatus(Finished);
    file->close();
    file->deleteLater();
    socket->deleteLater();




}
