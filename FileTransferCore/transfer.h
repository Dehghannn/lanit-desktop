#ifndef TRANSFER_H
#define TRANSFER_H

#include <QObject>
#include <QRunnable>
#include <QTcpSocket>
#include <QHostAddress>
#include <QThread>
#include <QFile>
#include <QFileInfo>
#include <QEventLoop>
#include <QElapsedTimer>
#include "datapacket.h"
///
/// \brief The Transfer class handles all the functionality related to a single transfer
///
class Transfer : public QObject, public QRunnable
{
    Q_OBJECT
public:
    Transfer(QObject *parent = nullptr):QObject(parent){};
    Transfer(QString Address, QString fileName, QObject *parent = nullptr); /// this constructs a send transfer
    virtual ~Transfer();
    void run();

    void startTransfer();
    enum State: unsigned char{
        NotStarted,
        Pending,
        Transfering,
        Finished,
        Failed
    };


    State status() const;
    void setStatus(State newStatus);

    const QString &targetIP() const;
    void setTargetIP(const QString &newTargetIP);

public slots:
    void readyRead();
    void disconnected();
    void socketBytesWritten(qint64 bytesWritten);
signals:
    void progressUpdated(qint64 bytesWritten);
    void statusChanged(State status);
    void finished();

    // these private members will be accessed directly in run only
private:
    int port = 8891;
    static quint16 transferCount;
    quint16 m_transferID; /// @todo use a transfer id to identify connections


    //file transfer variables
    QString m_targetIP;
    qint64 numberOfWrites;
    qint64 bytesWritten = 0;

    void waitForAck(QTcpSocket *socket);
    void sendFileRequest();
    bool getRequestResponse();
    void readFromFile();
protected:
    /// objects used in send and receive transfers
    QString fileName;
    QFile *file = nullptr;
    QTcpSocket *socket = nullptr;
    QFileInfo *info = nullptr;
    qint64 fileSize;
    int stepSize = 10; /// 5 KBytes for each write
    State m_status = NotStarted;
    bool m_readyRead = false;
    bool m_bytesWritten = false;
    QByteArray fileBuffer;
    const qint64 fileBufferReadSize = 2000000;
    qint64 fileBufferSize = 0;
    bool exit = false;

};


#endif // TRANSFER_H
