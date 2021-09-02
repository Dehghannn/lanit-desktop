#include "tcpservice.h"

TCPservice::TCPservice()
{
    server = new TcpServer;
}

void TCPservice::startService()
{

}

void TCPservice::newMessage(Message message, User &user)
{

}

void TCPservice::newOutgoingTextMessage(Message message)
{
    QTcpSocket *socket = new QTcpSocket;

}

void TCPservice::startNewConnection(QString address)
{
    QTcpSocket *socket = new QTcpSocket;
    QHostAddress IPaddress;
    IPaddress.setAddress(address);
    connect(socket, &QTcpSocket::connected, this, &TCPservice::connected);
    socket->connectToHost(IPaddress, server->getPort());
        // we need to wait...
        if(!socket->waitForConnected(5000))
        {
            qDebug() << "Error: " << socket->errorString();
        }
    //socket->bind(QHostAddress::AnyIPv4, server->getPort());
    socketList.append(socket);

}

void TCPservice::connected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*> (sender());
    qDebug() << "connected to " << socket->peerAddress().toString();
}
