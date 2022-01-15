#ifndef FILELISTMODEL_H
#define FILELISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "FileTransferCore/filemessage.h"
#include <QDebug>

class FileListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit FileListModel(QObject *parent = nullptr);
    enum roleNamesEnum{
        Progress,
        FileName,
        FileSize,
        isOwn,
        TimeStamp
    };
    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    void addFileMessage(FileMessage *fileMessage);
    bool insertRows(int row, int count, const QModelIndex &parent);
public slots:
    void onProgressUpdated(int index, int progress); /// @todo dont need progress number here
private:
    QList<FileMessage*> fileList;
    QHash<int, QByteArray> roles;
};

#endif // FILELISTMODEL_H
