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
    void setFromFileData(const QByteArray &fileData);
    void setFileRequest(QString FileName, qint64 fileSize);
    void setAcceptedResponse();
    void setRejectedResponse();
    QByteArray Data();
    void fromData(QByteArray data);
    /** \brief extractPacket
    *       this function gets an array of bytes and scans the left part of it for a packet
    * \param array is the input data read from tcp socket
    * \return true if a packet is found inside the array. the array is truncated without the packet
    */
    bool extractPacket(QByteArray &array);
    QByteArray getContent();

private:
    static const quint8 headerSize = 3;
    quint16 m_contentSize;
    qint8 m_type;
    QByteArray data;

    ///file and fileRequest related members
    quint16 m_transferCode;

    ///file request members
    QString m_fileNameSize;
    float m_fileSize; ///file size in MegaBytes

    ///utility
    QByteArray int16toArray(const qint16 &input);
    QByteArray int16toArray(const quint16 &input);
    quint16 arrayToUint(const QByteArray &input);
    QByteArray int64toArray(const qint64 &input);

};

#endif // DATAPACKET_H
