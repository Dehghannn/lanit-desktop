#include "tcpservice.h"

TCPservice::TCPservice()
{

}

void TCPservice::startService()
{
    server = new TcpServer;
    connect(server, &TcpServer::newIncomingTextMessage, this, &TCPservice::newIncomingTextFromServer);
    connect(server, &TcpServer::newIncommingConnectionFromServer, this, &TCPservice::newIncommingConnectionFromServer);
}

void TCPservice::newOutgoingTextMessage(Message message)
{
    QTcpSocket *socket;
    socket = getSocketByIP(message.getUserIP());
    if(socket != nullptr){
        DataPacket packet;
        packet.setFromMessage(message);
        socket->write(packet.Data());
    }else{
        startNewConnection(message.getUserIP());
        qDebug()<< "socket did not exist. starting a new connection...";
    }
}

void TCPservice::newIncomingMessage()
{
    /// @todo change this so that can detect files
    QTcpSocket *socket = qobject_cast<QTcpSocket*> (sender());
    QByteArray data = socket->readAll();
    DataPacket packet;
    while (packet.extractPacket(data)) { ///handle all messages here
        if(packet.type() == DataPacket::TextMessage){
            Message *message = new Message;
            message->setText(packet.getContent());
            message->setUserIP(socket->peerAddress().toString());
            emit newIncomingTextMessage(*message);
        }
    }

}

void TCPservice::newIncomingTextFromServer(QString text, QString userIP)
{
    Message *message = new Message;
    message->setText(text);
    message->setIsOwn(false);
    message->setUserIP(userIP);
    /// @todo find a way to set the IP address here
    emit newIncomingTextMessage(*message);
}

void TCPservice::startNewConnection(QString address)
{
    QTcpSocket *socket = new QTcpSocket;
    QHostAddress IPaddress;
    IPaddress.setAddress(address);
    connect(socket, &QTcpSocket::connected, this, &TCPservice::connected);
    connect(socket, &QTcpSocket::disconnected, this, &TCPservice::disConnected);
    connect(socket, &QTcpSocket::readyRead, this, &TCPservice::newIncomingMessage);
    socket->setProxy(QNetworkProxy::NoProxy);
    socket->connectToHost(IPaddress, server->getPort()); /// we dont have to wait for connected here
    socketList.append(socket);
    emit connectionStateChanged(address, ChatListModel::Connecting);

}

void TCPservice::newIncommingConnectionFromServer(QTcpSocket *socket)
{
    socketList.append(socket); ///added incoming connection to list so that no new connection is created
    connect(socket, &QTcpSocket::disconnected, this, &TCPservice::disConnected);
    //    emit connectionStateChanged(socket->peerAddress().toString(), ChatListModel::Connected);
    emit incommingConnection(socket->peerAddress().toString());

}

void TCPservice::connected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*> (sender());
    QString Address = socket->peerAddress().toString();
    qDebug() << "connected to " << Address;
    emit connectionStateChanged(Address, ChatListModel::Connected);
}

void TCPservice::disConnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*> (sender());
    QString Address = socket->peerAddress().toString();
    qDebug() << Address << " disconnected";
    emit connectionStateChanged(Address, ChatListModel::Disconnected);
    socketList.removeAt(socketList.indexOf(socket)); /// remove socket from the connected sockets list
    socket->deleteLater();
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
