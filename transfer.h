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
    Transfer(QTcpSocket* socket, QString fileName);

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
    static quint16 transferCount;
    quint16 m_transferID;
    QTcpSocket* socket;
    quint8 m_status = NotStarted;
    QString m_destIP;
    QString fileName;
    QFile file;
    QByteArray fileBuffer;
    //quint64 BytesWritten; dont need bytes written for now
    quint8 m_completionPercent;

    void setCompletionPercent(quint8 newCompletionPercent);

};


#endif // TRANSFER_H
