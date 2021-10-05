#ifndef TCPLISTENER_H
#define TCPLISTENER_H
#include <QTcpSocket>
#include <QObject>
#include <QNetworkProxy>
#include "tcpserver.h"
#include "message.h"
#include "user.h"
#include "chatlistmodel.h"

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
    void newIncommingConnectionFromServer(QTcpSocket* socket);

    /// connection handling slots
    void connected();
    void disConnected();
signals:
    void newIncomingTextMessage(Message message);
    void connectionStateChanged(QString IP, int state);
    void incommingConnection(QString Address); /// used to create a chat in case of incomming connection
private:
    TcpServer *server;
    QList<QTcpSocket*> socketList;
    QTcpSocket* getSocketByIP(QString ip);



};

#endif // TCPLISTENER_H
