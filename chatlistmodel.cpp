#include "chatlistmodel.h"
#include <QDebug>
ChatListModel::ChatListModel()
{

}

int ChatListModel::rowCount(const QModelIndex &parent) const
{
    return messageList.size();
}

QVariant ChatListModel::data(const QModelIndex &index, int role) const
{
    /// @todo change this implementation
    switch(role){
    case Qt::DisplayRole: return messageList.at(index.row()).text();
    case Qt::DecorationRole: return messageList.at(index.row()).isOwn();
    }
    return -1;
}

bool ChatListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if(count > 0){
        QAbstractItemModel::beginInsertRows(parent, row, row + count - 1);
    }else{
        return false;
    }

    QAbstractItemModel::endInsertRows();
    return true;
}
void ChatListModel::addMessage(Message &message)
{
    messageList.append(message);
    ChatListModel::insertRows(messageList.size() - 1, 1, QModelIndex());
//    emit dataChanged()


}

void ChatListModel::reset()
{
    messageList.erase(messageList.begin(), messageList.end());

}

QString ChatListModel::getUserIP() const
{
    return userIP;
}

void ChatListModel::setUserIP(const QString &value)
{
    userIP = value;
}

