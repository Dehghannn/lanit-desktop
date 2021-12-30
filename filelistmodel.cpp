#include "filelistmodel.h"

FileListModel::FileListModel(QObject *parent) : QAbstractListModel(parent)
{
    roles[Progress] = "Progress";
    roles[FileName] = "FileName";
    roles[FileSize] = "FileSize";
    roles[isOwn] = "isOwn";
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
}

void FileListModel::onProgressUpdated(int index, int progress)
{
    emit dataChanged(this->index(index), this->index(index + 1));
}
