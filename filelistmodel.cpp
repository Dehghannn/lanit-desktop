#include "filelistmodel.h"

FileListModel::FileListModel(QObject *parent) : QAbstractListModel(parent)
{
    roles[Progress] = "Progress";
    roles[FileName] = "FileName";
    roles[FileSize] = "FileSize";
    roles[isOwn] = "isOwn";
    roles[TimeStamp] = "TimeStamp";
    roles[State] = "State";
}

int FileListModel::rowCount(const QModelIndex &parent) const
{
    return fileList.size();
}

QVariant FileListModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case Progress:{
        return fileList.at(index.row())->progress();
    }
    case FileName:{
        return fileList.at(index.row())->fileName();
    }
    case FileSize:{
        return fileList.at(index.row())->fileSize();
    }
    case isOwn:{
        return fileList.at(index.row())->isOwn();
    }
    case TimeStamp:{
        return fileList.at(index.row())->getTime();
    }
    case State:{
        return getMessageState(index.row());
    }
    default:{
        return fileList.at(index.row())->fileName();
    }
    }
}

QHash<int, QByteArray> FileListModel::roleNames() const
{
    return roles;
}

void FileListModel::addFileMessage(FileMessage *fileMessage)
{
    fileMessage->setIndex(fileList.size());
    fileList.append(fileMessage);
    FileListModel::insertRows(fileList.size() -1 , 1, QModelIndex());
}

bool FileListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if(count > 0){
        QAbstractItemModel::beginInsertRows(parent, row, row + count - 1);
    }else{
        return false;
    }

    QAbstractItemModel::endInsertRows();
    return true;
}

void FileListModel::acceptFile(int index)
{
    fileList.at(index)->acceptFileMessage();
}

void FileListModel::rejectFile(int index)
{
    fileList.at(index)->rejectFileMessage();
}

void FileListModel::onProgressUpdated(int index, int progress)
{
    QModelIndex topLeft = createIndex(index, 0);
    QModelIndex bottomRight = createIndex(index + 1, 0);
    static QVector<int> changedRoles = {Progress};
    emit dataChanged(topLeft, bottomRight, changedRoles);
}

void FileListModel::onFileMessageStateChanged(int index)
{
    qDebug() << "file " << index << " state changed";
//    QModelIndex topLeft = createIndex(index, 0);
//    QModelIndex bottomRight = createIndex(index + 1, 0);
//    static QVector<int> changedRoles = {State};
//    emit dataChanged(topLeft, bottomRight);
    beginResetModel();
    endResetModel();
}

int FileListModel::getMessageState(int index) const
{
    FileMessage *m = fileList.at(index);
    int state = m->state();
    if(state == FileMessage::Pending && !m->isOwn()){
        return MessageState::WaitForUserConfirmation;
    }else if(state == FileMessage::Pending && m->isOwn()){
        return MessageState::ReadyToSend;
    }else if(state == FileMessage::Rejected || state == FileMessage::Failed){
        return MessageState::Failed;
    }else{
        return MessageState::Transfering;
    }
}
