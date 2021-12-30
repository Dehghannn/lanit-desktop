#ifndef FILEMESSAGE_H
#define FILEMESSAGE_H
#include "message.h"
#include <QFile>
#include <QFileInfo>

class FileMessage: public QObject, public Message
{
    Q_OBJECT
public:
    FileMessage(QString path);
    int progress() const;
public slots:
    void updateProgress(qint16 bytesTransfered);
signals:
    void progressUpdated(int progress);
private:
    qint16 fileSize;
    int m_progress = 0;
};
#endif // FILEMESSAGE_H
