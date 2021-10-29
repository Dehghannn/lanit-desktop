#ifndef TRANSFER_H
#define TRANSFER_H

#include <QObject>
#include <QRunnable>
#include <QTcpSocket>
#include <QHostAddress>
#include <QFile>
#include <QFileInfo>
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
    void run();

    QString getDestIP();
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

    quint8 completionPercent() const;
public slots:


signals:
    void progressUpdated(qint64 bytesWritten);
    void statusChanged(State status);

// these private members will be accessed directly in run only
private:
    int port = 8891;
    static quint16 transferCount;
    quint16 m_transferID; /// @todo use a transfer id to identify connections


    //file transfer variables
    QString m_destIP;
    int numberOfWrites;
    qint64 bytesWritten;


    void setCompletionPercent(quint8 newCompletionPercent);
protected:

    QString fileName;
    QFile *file;
    qint64 fileSize;
    int stepSize = 5000; /// 5 KBytes for each write
    quint8 m_completionPercent; /// @todo calculate this and signal out periodically
    State m_status = NotStarted;

};


#endif // TRANSFER_H
