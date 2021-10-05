#ifndef DATAPACKET_H
#define DATAPACKET_H


class DataPacket
{
public:
    DataPacket();

    enum{
      TextMessage,
      File,
      FileRequest
    };
    int size() const;
    void setSize(int newSize);

    int type() const;
    void setType(int newType);

private:
    int m_size;
    int m_type;
    unsigned char* ptr;
};

#endif // DATAPACKET_H
