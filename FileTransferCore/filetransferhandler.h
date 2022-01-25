#ifndef FILETRANSFERHANDLER_H
#define FILETRANSFERHANDLER_H

#include <QObject>
#include <QThreadPool>
#include <QTcpServer>
#include <QTcpSocket>
#include "transfer.h"
#include "receive.h"
#include "filemessage.h"
/**
 * @brief The FileTransferHandler class handles all transfers in one place
 */
class FileTransferHandler : public QTcpServer
{
    Q_OBJECT
public:
    explicit FileTransferHandler(int port = 8891, QObject *parent = nullptr);
    void start();
    void quit();

    const QString &savePath() const;
    void setSavePath(const QString &newSavePath);

public slots:
    void newOutgoingFile(QString address, QString fileName);
    void newOutgoingFile(QString address, QString fileName, FileMessage* fileMessage);

signals:
    void newIncomingFile(Receive *receiver); /// slot must take care of fileMessage memory allocation
private:
    QThreadPool pool;
    int port;
    QString m_savePath;



    // QTcpServer interface
protected:
    void incomingConnection(qintptr handle);
};

#endif // FILETRANSFERHANDLER_H
