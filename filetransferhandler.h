#ifndef FILETRANSFERHANDLER_H
#define FILETRANSFERHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QFile>
#include <QFileInfo>
#include <user.h>

class FileTransferHandler : public QObject
{
    Q_OBJECT
public:
    explicit FileTransferHandler(QObject *parent = nullptr);
    void sendFile(QString PathToFile, User user);

signals:
    void fileSendingProgress(int sentBytes, QHostAddress targetAddress);

private:
    QHash<QHostAddress, QFile*> filesSending;
    QHash<QHostAddress, QFile*> filesReceiving;

};


#endif // FILETRANSFERHANDLER_H
