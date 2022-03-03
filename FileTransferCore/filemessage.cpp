#include "filemessage.h"
FileMessage::FileMessage(QString path)
{
    QFileInfo info;
    info.setFile(path);
    m_fileSize = info.size();
    m_fileName = info.fileName();
}

FileMessage::FileMessage()
{

}

void FileMessage::updateProgress(qint64 bytesTransfered)
{
    m_progress = (bytesTransfered * 100) / m_fileSize;
    emit progressUpdated(m_index, m_progress);
}

void FileMessage::onTransferFinished()
{
    setState(FileMessage::Finished);
    qDebug() << "Transfer finished on file " << m_index << Finished;
}

int FileMessage::state() const
{
    return m_state;
}

void FileMessage::setState(int newState)
{
    m_state = newState;
    emit stateChanged(m_index);
}

void FileMessage::setFileSize(qint64 newFileSize)
{
    m_fileSize = newFileSize;
}

void FileMessage::acceptFileMessage()
{
    emit fileIsAccepted(true);
    setState(Accepted);
}

void FileMessage::rejectFileMessage()
{
    emit fileIsAccepted(false);
    setState(Rejected);
}

void FileMessage::setFileName(const QString &newFileName)
{
    m_fileName = newFileName;
}

int FileMessage::index() const
{
    return m_index;
}

void FileMessage::setIndex(int index)
{
    m_index = index;
}

QString FileMessage::fileName() const
{
    return m_fileName;
}

qint64 FileMessage::fileSize() const
{
    return m_fileSize;
}

int FileMessage::progress() const
{
    return m_progress;
}
