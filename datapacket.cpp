#include "datapacket.h"

DataPacket::DataPacket()
{
    setType(TextMessage); /// default to text message
}

int DataPacket::size() const
{
    return m_size;
}

void DataPacket::setSize(int newSize)
{
    m_size = newSize;
}

int DataPacket::type() const
{
    return m_type;
}

void DataPacket::setType(int newType)
{
    m_type = newType;
}
