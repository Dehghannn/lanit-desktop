#ifndef RECEIVE_H
#define RECEIVE_H

#include <QObject>
#include <QRunnable>
#include <QTcpSocket>
#include <QHostAddress>
#include <QFile>
#include <QFileInfo>
#include <QThread>
#include <QTimer>
#include "datapacket.h"
#include "transfer.h"
///
/// \brief The Transfer class handles all the functionality related to a single transfer
///
class Receive : public Transfer
{
    Q_OBJECT
public:
    Receive(qintptr handle, QObject *parent = nullptr); /// this constructs a receive transfer    
    void run() override;

    QString getDestIP();

    const QString &path() const;
    void setPath(const QString &newPath);

public slots:
    void onUserResponded(bool); /// connect this slot to a signal from gui

signals:
    void progressUpdated(qint64 bytesRead);
    void newFileRequest(QString FileName, qint64 fileSize, QString address);
    void userResponded();

    // these private members will be accessed directly in run only
private:
    int port = 8891;
    qintptr handle;
    quint16 m_transferID; /// @todo use a transfer id to identify connections


    //file receive variables
    QString m_targetIP;
    qint64 numberOfReads;
    qint64 bytesRead = 0;
    QString m_path;
    void readIncomingRequest();
    void respondToRequest(DataPacket::AnswerType answer);
    /**
     * @brief waitForUserResponse
     * wait for user to interact with gui and accept or reject the transfer
     */
    void waitForUserResponse();
    QByteArray readBuffer;
    QByteArray fileBuffer;
    const qint64 maxBufferSize = 50000000;
    DataPacket::AnswerType response = DataPacket::No;

protected:
    /* protected members of the parent class
    QString fileName;
    QFile *file;
    qint64 fileSize;
    int stepSize = 5000; /// 5 KBytes for each write
    quint8 m_completionPercent; /// @todo calculate this and signal out periodically
    quint8 m_status = NotStarted;
*/
};


#endif // RECEIVE_H
