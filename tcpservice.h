#ifndef TCPLISTENER_H
#define TCPLISTENER_H
#include <QTcpSocket>
#include <QObject>
#include <QNetworkProxy>
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
    void newOutgoingTextMessage(Message message);
    void newIncomingMessage();
    void newIncomingTextFromServer(QString text, QString userIP);
    void startNewConnection(QString address);
    void connected();
signals:
    void newIncomingTextMessage(Message message);
private:
    TcpServer *server;
    QList<QTcpSocket*> socketList;
    QTcpSocket* getSocketByIP(QString ip);



};

#endif // TCPLISTENER_H
