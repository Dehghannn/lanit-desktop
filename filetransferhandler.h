#ifndef FILETRANSFERHANDLER_H
#define FILETRANSFERHANDLER_H

#include <QObject>
#include <QThreadPool>
#include <QTcpServer>
#include <QTcpSocket>
#include "transfer.h"
#include "receive.h"
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

public slots:
    void newOutgoingFile(QString address, QString fileName);

signals:
private:
    QThreadPool pool;
    int port;



    // QTcpServer interface
protected:
    void incomingConnection(qintptr handle);
};

#endif // FILETRANSFERHANDLER_H
