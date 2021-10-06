#ifndef DATAPACKET_H
#define DATAPACKET_H
#include <QFile>
#include "message.h"

class DataPacket
{
public:
    DataPacket();

    enum{
      TextMessage,
      File,
      FileRequest,
      Response
    };
    quint16 contentSize() const;
    void setContentSize(quint16 newSize);

    qint8 type() const;
    void setType(qint8 newType);
    void setFromMessage(const Message &message);
    void setFromFile(const QFile &file);
    void setAcceptedResponse();
    void setRejectedResponse();
    unsigned char* Data();
    void fromData(QByteArray data);

private:
    quint16 m_contentSize;
    qint8 m_type;
    QByteArray data;
};

#endif // DATAPACKET_H
