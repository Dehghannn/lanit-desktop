#ifndef UDPBROADCASTER_H
#define UDPBROADCASTER_H
#include <QUdpSocket>
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include "udplistener.h"

class UDPbroadcaster : public QObject
{
    Q_OBJECT
public:
    UDPbroadcaster();

    QString nickName() const;
    void setNickName(const QString &nickName);
    UDPlistener *Listener;

public slots:
    void broadCast();
    void startTimer();
    void newNickName(QString nickName);

private:
    QUdpSocket usocket;
    int port = 8889;
    QTimer *timer;
    QString m_nickName;
    QHostAddress address;


};

#endif // UDPBROADCASTER_H
