#ifndef FILEMESSAGE_H
#define FILEMESSAGE_H
#include "message.h"
#include <QFile>
#include <QFileInfo>
#include <QDebug>

class FileMessage: public QObject, public Message
{
    Q_OBJECT
public:
    /**
     * @brief FileMessage
     * use this constructor for outgoing file messages
     * @param path
     */
    FileMessage(QString path);
    /**
     * @brief FileMessage
     * use default constructor for incoming file messages
     */
    FileMessage();
    enum States{
        Pending = 0,
        Accepted,
        Rejected,
        Failed,
        Finished
    };
    int progress() const;
    qint64 fileSize() const;

    QString fileName() const;

    int index() const;
    void setIndex(int index);

    void setFileName(const QString &newFileName);

    void setFileSize(qint64 newFileSize);
    void acceptFileMessage();
    void rejectFileMessage();

    int state() const;
    void setState(int newState);

public slots:
    void updateProgress(qint64 bytesTransfered);
    void onTransferFinished();
signals:
    void progressUpdated(int index, int progress);
    void fileIsAccepted(bool accepted); /// accepted = 1 is accepted
    void stateChanged(int index);
private:
    int m_index = 0;
    QString m_fileName;
    qint64 m_fileSize;
    int m_progress = 0;
    int m_state = Pending;

};
#endif // FILEMESSAGE_H
