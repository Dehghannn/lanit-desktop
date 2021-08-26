#ifndef UDPLISTENER_H
#define UDPLISTENER_H
#include <QUdpSocket>
#include <QObject>
#include <QNetworkDatagram>
#include <QDebug>

class UDPlistener : public QObject
{
    Q_OBJECT
public:
    explicit UDPlistener(QObject *parent = nullptr);
public slots:

    void UDPread();

signals:
    void newDataGram(QNetworkDatagram datagram);
private:
    QUdpSocket usocketListener;
    int port = 8889;
};

#endif // UDPLISTENER_H
