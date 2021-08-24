#ifndef UDPLISTENER_H
#define UDPLISTENER_H

#include <QObject>

class UDPlistener : public QObject
{
    Q_OBJECT
public:
    explicit UDPlistener(QObject *parent = nullptr);

signals:

};

#endif // UDPLISTENER_H
