#ifndef TRANSFER_H
#define TRANSFER_H

#include <QObject>
#include <QRunnable>
#include <QTcpSocket>
#include <QHostAddress>
#include <QFile>
///
/// \brief The Transfer class handles all the functionality related to a single transfer
///
class Transfer : public QRunnable
{
public:
    Transfer(qintptr handle, QString fileName); /// this constructs a receive transfer
    Transfer(QString Address, QString fileName); /// this constructs a send transfer

    void run();

    QString getDestIP();
    void startTransfer();
    enum{
        NotStarted,
        Pending,
        Sending,
        Finished
    };


    quint8 status() const;
    void setStatus(quint8 newStatus);

    quint8 completionPercent() const;


private:
    bool Receive;
    qintptr handle;
    static quint16 transferCount;
    quint16 m_transferID;
    quint8 m_status = NotStarted;
    QString m_destIP;
    QString fileName;
    QFile *file;
    QByteArray fileBuffer;
    //quint64 BytesWritten; dont need bytes written for now
    quint8 m_completionPercent;

    //file transfer variables
    int stepSize = 5000; /// 5 KBytes for each write
    int numberOfWrites;
    quint32 bytesWritten;
    qint64 fileSize;

    void setCompletionPercent(quint8 newCompletionPercent);

};


#endif // TRANSFER_H
