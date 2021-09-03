#include "tcpservice.h"

TCPservice::TCPservice()
{
    server = new TcpServer;
}

void TCPservice::startService()
{

}

void TCPservice::newOutgoingTextMessage(Message message)
{
    QTcpSocket *socket;
    socket = getSocketByIP(message.getUserIP());
    if(socket != nullptr){
        socket->write(message.text().toUtf8());
    }else{
        startNewConnection(message.getUserIP());
    }
}

void TCPservice::newIncomingMessage()
{
    /// @todo change this so that can detect files
    QTcpSocket *socket = qobject_cast<QTcpSocket*> (sender());
    QString data = socket->readAll();
    Message *message = new Message;
    message->setText(data);
    message->setUserIP(socket->peerAddress().toString());
    emit newIncomingTextMessage(*message);
}

void TCPservice::startNewConnection(QString address)
{
    QTcpSocket *socket = new QTcpSocket;
    QHostAddress IPaddress;
    IPaddress.setAddress(address);
    connect(socket, &QTcpSocket::connected, this, &TCPservice::connected);
    connect(socket, &QTcpSocket::readyRead, this, &TCPservice::newIncomingMessage);
    socket->connectToHost(IPaddress, server->getPort());
        // we need to wait...
//        if(!socket->waitForConnected(5000))
//        {
//            qDebug() << "Error: " << socket->errorString();
//        }
    //socket->bind(QHostAddress::AnyIPv4, server->getPort());
    socketList.append(socket);

}

void TCPservice::connected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*> (sender());
    qDebug() << "connected to " << socket->peerAddress().toString();
}

QTcpSocket* TCPservice::getSocketByIP(QString ip)
{
    for(int i = 0; i < socketList.size(); i++){
        qDebug() << "checking with" << QHostAddress(ip);
        if(socketList.at(i)->peerAddress() == QHostAddress(ip))
            return socketList.at(i);
    }
    return nullptr;
}
