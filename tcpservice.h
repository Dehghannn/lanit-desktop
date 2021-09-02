#ifndef TCPLISTENER_H
#define TCPLISTENER_H
#include <QTcpSocket>
#include <QObject>
#include "tcpserver.h"
#include "message.h"
#include "user.h"

class TCPservice : public QObject
{
    Q_OBJECT
public:
    TCPservice();
public slots:
    void startService();
    void newMessage(Message message, User &user);
    void newOutgoingTextMessage(Message message);
    void startNewConnection(QString address);
    void connected();
private:
    TcpServer *server;
    QList<QTcpSocket*> socketList;



};

#endif // TCPLISTENER_H
