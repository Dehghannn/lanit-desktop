#include "datapacket.h"

DataPacket::DataPacket()
{
    setType(TextMessage); /// default to text message
}

quint16 DataPacket::contentSize() const
{
    return m_contentSize;
}

void DataPacket::setContentSize(quint16 newSize)
{
    m_contentSize = newSize;
}

qint8 DataPacket::type() const
{
    return m_type;
}

void DataPacket::setType(qint8 newType)
{
    m_type = newType;
}

void DataPacket::setFromMessage(const Message &message)
{
    QString messageText = message.text();
    setType(DataPacket::TextMessage);
    setContentSize(messageText.size());
    data.append(m_contentSize);
    data.append(m_type);
    data.append(messageText.toUtf8());
}

void DataPacket::setFromFile(const QFile &file)
{

}

void DataPacket::setAcceptedResponse()
{

}

void DataPacket::setRejectedResponse()
{

}

unsigned char *DataPacket::Data()
{

}

void DataPacket::fromData(QByteArray data)
{
    setType(data.at(2)); ///third byte is type
    QByteArray size = data;
    size.truncate(2);
    setContentSize(size.toInt());
    this->data = data.mid(3); /// @todo change this so that the size specified is picked
}
