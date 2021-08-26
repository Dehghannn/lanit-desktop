#include "udpbroadcaster.h"

UDPbroadcaster::UDPbroadcaster()
{

    address.setAddress("192.168.43.80");
    if (!usocket.bind(QHostAddress::AnyIPv4, port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
        qDebug("failed to bind udp socket!");
        exit(EXIT_FAILURE);
    }
    Listener = new UDPlistener;


}

void UDPbroadcaster::broadCast()
{
    QByteArray data;
    data =QByteArray::fromStdString( m_nickName.toStdString());
    qDebug() << data;
    qint64 errCode;
    errCode = usocket.writeDatagram(data.data(), data.size(), QHostAddress::Broadcast, port);
    qDebug() << errCode << "Bytes sent";
    qDebug() << "broadcast called!";

}

void UDPbroadcaster::startTimer()
{



    timer = new QTimer();
    timer->setInterval(1000);
    timer->setSingleShot(false);

    timer->moveToThread(QThread::currentThread());
    QObject::connect(timer, &QTimer::timeout, this, &UDPbroadcaster::broadCast);
    timer->start();
    qDebug() << "broadcast started";
}

void UDPbroadcaster::newNickName(QString nickName)
{
    setNickName(nickName);
}

QString UDPbroadcaster::nickName() const
{
    return m_nickName;
}

void UDPbroadcaster::setNickName(const QString &nickName)
{
    m_nickName = nickName;
}
