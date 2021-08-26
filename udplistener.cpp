#include "udplistener.h"

UDPlistener::UDPlistener(QObject *parent) : QObject(parent)
{
    if (!usocketListener.bind(QHostAddress::AnyIPv4, port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
        qDebug("failed to bind udp listener socket!");
        exit(EXIT_FAILURE);
    }
    connect(&usocketListener, &QUdpSocket::readyRead, this, &UDPlistener::UDPread);

}

void UDPlistener::UDPread()
{
    while (usocketListener.hasPendingDatagrams()) {
        QNetworkDatagram datagram = usocketListener.receiveDatagram();
        emit newDataGram(datagram);
        qDebug() <<"received: "  <<  datagram.data() << "from: " << datagram.senderAddress().toString();
    }
}

