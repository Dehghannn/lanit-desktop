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

//void DataPacket::setType(char newType)
//{
//    m_type = static_cast<DataPacket::PacketType>(newType);
//}

void DataPacket::setFromMessage(const Message &message)
{
    data.clear();
    QByteArray messageText = message.text().toUtf8(); /// need to be in UTF8
    setType(DataPacket::TextMessage);
    setContentSize(messageText.size());
    QByteArray sizeArray = int16toArray(m_contentSize);
    data.append(sizeArray);
    data.append(m_type);
    data.append(messageText);
    //qDebug() << data;
    //qDebug() << data.size();
}

void DataPacket::setFromFileData(const QByteArray &fileData, quint16 transferCode)
{
    data.clear();
    setType(File);
    setContentSize(sizeof(quint16) + fileData.size()); // size of file + size of transfer code
    //qDebug() << "fileData size is  " <<  fileData.size();
    data.append(int16toArray(m_contentSize));
    data.append(m_type);
    data.append(int16toArray(transferCode));
    data.append(fileData);
}

void DataPacket::setFileRequest(QString FileName, qint64 fileSize)
{
    m_fileName = FileName;
    m_fileSize = fileSize;
    data.clear();
    setType(FileRequest);
    qint16 fileNameSize = FileName.toUtf8().size();
    //qDebug() << fileNameSize;
    setContentSize(sizeof (qint16) + fileNameSize + sizeof(qint64));
    data.append(int16toArray(m_contentSize));
    data.append(m_type);
    data.append(int16toArray(fileNameSize));
    data.append(FileName.toUtf8());
    data.append(int64toArray(fileSize));
    //qDebug() << "64 bit data array size :" << int64toArray(fileSize).size();
    //qDebug() << int16toArray(fileNameSize).size();
    //qDebug() << data.size();
}

void DataPacket::setAcceptedResponse()
{
    data.clear();
    setType(Response);
    response = AnswerType::Yes;
    setContentSize(1); // header + one byte answer type
    data.append(int16toArray(m_contentSize));
    data.append(m_type);
    data.append(byteToArray(response)); /// @todo byte to array may be unnecessary
}

void DataPacket::setRejectedResponse()
{
    data.clear();
    setType(Response);
    response = AnswerType::No;
    setContentSize(1); // header + one byte answer type
    data.append(int16toArray(m_contentSize));
    data.append(m_type);
    data.append(byteToArray(response));

}

void DataPacket::setAck()
{
    data.clear();
    setType(Ack);
    setContentSize(0); //only header
    data.append(int16toArray(m_contentSize));
    data.append(m_type);
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


bool DataPacket::extractPacket(QByteArray &array)
{
    if(array.size() < headerSize)
        return false;
    //qDebug() <<"read a packet";
    QByteArray size_array = array.left(2);
    quint16 size_int = arrayToUint16(size_array);
    //qDebug() << "packet content size : " << size_int;
    setContentSize(size_int);
    setType(array.at(2)); ///@todo handle different types here
    //qDebug() <<"packet type : " << m_type;
    if(array.size() < headerSize + m_contentSize)
        return false;
    switch (m_type) {


    case TextMessage:{
        data = array.left(headerSize + m_contentSize);
        //qDebug() << "packet content is: " << data.mid(headerSize);
        break;
    }


    case File:{
        this->m_transferCode = arrayToUint16(array.mid(headerSize, 2));
        data = array.left(headerSize + m_contentSize); //header + content
        break;
    }

    case FileRequest:{
        QByteArray fileNameSize_array = array.mid(headerSize, 2);
        qint16 fileNameSize = arrayToInt16(fileNameSize_array);
        qDebug() << "fileNameSize = " << fileNameSize;
        m_fileName = array.mid(headerSize + 2, fileNameSize);
        qDebug() << "fileName = " << m_fileName;
        m_fileSize = arrayToInt64(array.mid(headerSize + 2 + fileNameSize, 8)); // take 8 byte after the fileName and convert to int64
        qDebug() << "fileSize = " << m_fileSize;
        data = array.left(headerSize + m_contentSize ); // header +  content
        break;
    }

    case Response:{

        response = arrayToByte(array.mid(headerSize, 1));
        data = array.left(headerSize + 1);
        break;
    }
    case Ack:{
        //qDebug() << "extracted ack packet";
        break;
    }
    default:{
        qInfo() <<"not a valid type";
        exit(1);
    }

    }
    if(m_contentSize + headerSize <= array.size()){ /// incomming data is bigger than the first packet
        array = array.mid(headerSize + m_contentSize);
        return true;
    }
    return false;
}

QByteArray DataPacket::getContent()
{
    switch (m_type) {
    case TextMessage:
        return data.mid(headerSize);
    case File:
        return data.mid(headerSize + sizeof (quint16));
    default:
        return data;
    }
}

const QString &DataPacket::fileName() const
{
    return m_fileName;
}

qint64 DataPacket::fileSize() const
{
    return m_fileSize;
}

bool DataPacket::isYes()
{
    if(m_type != Response || response != Yes){
        return false;
    }
    return true;
}

QByteArray DataPacket::byteToArray(const qint8 &input)
{
    char c = input;
    QByteArray output;
    output.append(c);
    return output;
}

qint8 DataPacket::arrayToByte(const QByteArray &input)
{
    qint8 output = static_cast<qint8>(input.data()[0]);
    return output;
}

QByteArray DataPacket::int16toArray(const qint16 &input)
{
    char c[2];
    c[1] = (input & 0xff);
    c[0] = ((input >> 8) & 0xff);
    QByteArray output;
    output.append(c, 2);
    return output;
}

QByteArray DataPacket::int16toArray(const quint16 &input)
{
    char c[2];
    c[1] = (input & 0xff);
    c[0] = ((input >> 8) & 0xff);
    QByteArray output;
    output.append(c, 2);
    return output;
}

quint16 DataPacket::arrayToUint16(const QByteArray &input)
{
    quint16 output = static_cast<quint16>(input.data()[0]);
    output <<= 8;
    output +=  (static_cast<quint16>(input.data()[1]) & 0xff);
    return output;
}

qint16 DataPacket::arrayToInt16(const QByteArray &input)
{
    qint16 output = static_cast<qint16>(input.data()[0]);
    output <<= 8;
    output +=  (static_cast<qint16>(input.data()[1]) & 0xff);
    return output;

}

qint64 DataPacket::arrayToInt64(const QByteArray &input)
{
    qint64 output = static_cast<qint64>(input.data()[0]);
    //qDebug() << "output = " << output;
    for(int i = 1; i < 8; i++){
        output <<= 8;
        //qDebug() << "output level " << i << "  befor sum = " << Qt::hex << output;
        output += (static_cast<qint64>(input.data()[i]) & 0xff);
        //qDebug() << "output level " << i << " = " << Qt::hex << output;
    }
//    qint64 output;
//    memcpy(&output, &input, 8);
    return output;

}

QByteArray DataPacket::int64toArray(const qint64 &input)
{
    qint64 temp = input;
    char c[8];
    for(int i = 7; i >= 0; i--){
        c[i] = (temp & 0xff);
        temp >>= 8;
    }
    QByteArray output;
    output.append(c, 8);
    //qDebug() << "input of int64toArray = " << input;
    //qDebug() << "output of int64toArray = " << arrayToInt64(output);
    return output;
}
