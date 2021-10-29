#ifndef RECEIVE_H
#define RECEIVE_H

#include <QObject>
#include <QRunnable>
#include <QTcpSocket>
#include <QHostAddress>
#include <QFile>
#include <QFileInfo>
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
//    void startTransfer();
//    enum{
//        NotStarted,
//        Pending,
//        Transfering,
//        Finished,
//        Failed
//    };


    //quint8 status() const;
    //void setStatus(quint8 newStatus);

    quint8 completionPercent() const;
public slots:


 signals:
    void progressUpdated(qint64 bytesRead);
    void newFileRequest(QString FileName, qint64 fileSize);
    void statusChanged(qint8 status);

// these private members will be accessed directly in run only
private:
    int port = 8891;
    qintptr handle;
    quint16 m_transferID; /// @todo use a transfer id to identify connections


    //file receive variables
    QString m_destIP;
    int numberOfReads;
    qint64 bytesRead = 0;
    QFile *file;
    void setCompletionPercent(quint8 newCompletionPercent);
    /**
     * @brief waitForAnswer
     * this functions waits for the user to say yes or no to a file transfer request
     * @return will return true if the user says yes and false if no answer
     */
    bool waitForAnswer();
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
