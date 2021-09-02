#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);

signals:
private:
    QTcpServer *server;
    int port = 8890;
public slots:
    void incommingConnection();
    void dataRead();

};

#endif // TCPSERVER_H
