#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    server->listen(QHostAddress::Any, port);
    connect(server, &QTcpServer::newConnection, this, &TcpServer::incommingConnection);


}

int TcpServer::getPort() const
{
    return port;
}

void TcpServer::setPort(int value)
{
    port = value;
}

void TcpServer::incommingConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &TcpServer::dataRead);
    socket->waitForDisconnected();

}

void TcpServer::dataRead()
{
    QByteArray data;
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    data = socket->readAll();
    qDebug() << "read this : " << data;

}
