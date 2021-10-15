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
    QByteArray messageText = message.text().toUtf8(); /// need to be in UTF8
    setType(DataPacket::TextMessage);
    setContentSize(messageText.size());
//    QByteArray size(2);
    char c[2];
    c[1] = (m_contentSize & 0xff);
    c[0] = (m_contentSize >> 8);
    data.append(c, 2);
    data.append(m_type);
    data.append(messageText);
    qDebug() << data;
    qDebug() << data.size();
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

QByteArray DataPacket::Data()
{
    return data;
}

void DataPacket::fromData(QByteArray data)
{
    setType(data.at(2)); ///third byte is type
    QByteArray size = data;
    size.truncate(2);
    setContentSize(size.toInt());
    this->data = data.mid(3); /// @todo change this so that the size specified is picked
}
///
/// \brief DataPacket::extractPacket
/// this function gets an array of bytes and scans the left part of it for a packet
/// \param array is the input data read from tcp socket
/// \return true if a packet is found inside the array. the array is truncated without the packet
///
bool DataPacket::extractPacket(QByteArray &array)
{
    if(array.size() < headerSize)
        return false;
    qDebug() <<"read a packet";
    QByteArray size = array.left(2);
    qint16 size_int_byte = static_cast<qint16>(size.data()[0]);
    qint16 size_int = size_int_byte << 8;
    size_int = size_int + static_cast<qint16>(size.data()[1]);
    qDebug() << "packet size is " << size_int;
    setContentSize(size_int);
    setType(array.at(2)); ///@todo handle different types here
    if(array.size() < headerSize + m_contentSize)
        return false;
    switch (m_type) {
        case TextMessage:
            data = array.left(3 + m_contentSize);
            qDebug() << "packet content is: " << data.mid(headerSize);
    }
    if(m_contentSize + headerSize <= array.size()){ /// incomming data is bigger than the first packet
        array = array.mid(headerSize + m_contentSize);
        return true;
    }
    return false;
}

QByteArray DataPacket::getContent()
{
    return data.mid(3);
}
