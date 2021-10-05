#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    server->listen(QHostAddress::AnyIPv4, port);
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
    emit newIncommingConnectionFromServer(socket);
    socket->waitForDisconnected();

}

void TcpServer::dataRead()
{
    QByteArray data;
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    data = socket->readAll();
    emit newIncomingTextMessage(data, socket->peerAddress().toString());
    qDebug() << "read this : " << data;
    qDebug() << "from : " << socket->peerAddress().toString();

}


