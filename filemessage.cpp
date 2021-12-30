#include "filemessage.h"
FileMessage::FileMessage(QString path)
{
    QFileInfo info;
    info.setFile(path);
    fileSize = info.size();
}

void FileMessage::updateProgress(qint16 bytesTransfered)
{
    m_progress = (bytesTransfered / fileSize) * 100;
    emit progressUpdated(m_progress);
}

int FileMessage::progress() const
{
    return m_progress;
}
