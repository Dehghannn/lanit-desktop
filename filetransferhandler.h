#ifndef FILETRANSFERHANDLER_H
#define FILETRANSFERHANDLER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "transfer.h"
/**
 * @brief The FileTransferHandler class handles all transfers in one place
 */
class FileTransferHandler : public QObject
{
    Q_OBJECT
public:
    explicit FileTransferHandler(QObject *parent = nullptr);

public slots:
    void newOutgoingFile(QString fileName);

signals:
private:



};

#endif // FILETRANSFERHANDLER_H
