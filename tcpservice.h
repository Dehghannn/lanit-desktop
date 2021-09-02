#ifndef TCPLISTENER_H
#define TCPLISTENER_H
#include <QTcpSocket>
#include <QObject>
#include "tcpserver.h"

class TCPservice : public QObject
{
    Q_OBJECT
public:
    TCPservice();
public slots:
    void startService();
private:
    TcpServer *server;



};

#endif // TCPLISTENER_H
