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
        TimeStamp,
        State
    };
    enum MessageState : int{
        WaitForUserConfirmation = 0, /// incoming files waiting for user to interact with gui
        ReadyToSend, /// outgoing files waiting for other user to confirm transfer
        Transfering, /// transfering both for incoming and outgoing
        Failed
    };
    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    void addFileMessage(FileMessage *fileMessage);
    bool insertRows(int row, int count, const QModelIndex &parent);
    Q_INVOKABLE void acceptFile(int index);
    Q_INVOKABLE void rejectFile(int index);
public slots:
    void onProgressUpdated(int index, int progress); /// @todo dont need progress number here
    void onFileMessageStateChanged(int index);
private:
    QList<FileMessage*> fileList;
    QHash<int, QByteArray> roles;
    int getMessageState(int index) const;
};

#endif // FILELISTMODEL_H
