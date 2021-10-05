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
    int size() const;
    void setSize(int newSize);

    int type() const;
    void setType(int newType);
    void setFromMessage(const Message &message);
    void setFromFile(const QFile &file);
    void setAcceptedResponse();
    void setRejectedResponse();
    unsigned char* Data();

private:
    int m_size;
    int m_type;
    unsigned char* ptr;
};

#endif // DATAPACKET_H
