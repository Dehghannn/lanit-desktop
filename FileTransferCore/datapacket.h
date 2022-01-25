#ifndef DATAPACKET_H
#define DATAPACKET_H
#include <QFile>
#include <QDebug>
#include "message.h"
/**
 * @brief The DataPacket class creates packets to be sent and received through network
 */
class DataPacket
{
public:
    DataPacket();

    enum PacketType:  qint8{
      TextMessage,
      File,
      FileRequest,
      Response,
      Ack
    };
    enum AnswerType: qint8{
        Yes = 5,
        No
    };
    quint16 contentSize() const;
    void setContentSize(quint16 newSize);

    qint8 type() const;
    void setType(qint8 newType);
    //void setType(char newType);
    void setFromMessage(const Message &message);
    void setFromFileData(const QByteArray &fileData, quint16 transferCode);
    void setFileRequest(QString FileName, qint64 fileSize);
    void setAcceptedResponse();
    void setRejectedResponse();
    void setAck();
    QByteArray Data();
    void fromData(QByteArray data);
    /** \brief extractPacket
    *       this function gets an array of bytes and scans the left part of it for a packet
    * \param array is the input data read from tcp socket
    * \return true if a packet is found inside the array. the array is truncated without the packet
    */
    bool extractPacket(QByteArray &array);
    QByteArray getContent();

    const QString &fileName() const;

    qint64 fileSize() const;
    /**
     * @brief isYes
     * in case this is a Response you can easily check the answer with this function
     * @return returns true if the response is set to yes returns false otherwise or even it's not a Response
     */
    bool isYes();

private:
    static const quint8 headerSize = 3;
    quint16 m_contentSize;
    qint8 m_type;
    qint8 response = No; /// use this member for Response packets
    QByteArray data;

    ///file and fileRequest related members
    quint16 m_transferCode;

    ///file request members
    QString m_fileName;
    qint64 m_fileSize; ///file size in MegaBytes

    ///utility
    QByteArray byteToArray(const qint8& input);
    qint8 arrayToByte(const QByteArray& input);
    QByteArray int16toArray(const qint16& input);
    QByteArray int16toArray(const quint16& input);
    quint16 arrayToUint16(const QByteArray& input);
    qint16 arrayToInt16(const QByteArray& input);
    qint64 arrayToInt64(const QByteArray& input);
    QByteArray int64toArray(const qint64& input);

};

#endif // DATAPACKET_H
