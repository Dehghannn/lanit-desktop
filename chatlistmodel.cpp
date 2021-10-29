#include "chatlistmodel.h"
#include <QDebug>
ChatListModel::ChatListModel(QObject* parent): QAbstractListModel(parent)
{
    /// declaring roleNames
    names[MessageRole] = "message";
    names[TimeRole] = "time";
    names[OwnershipRole] = "ownership";

    m_connectionState = "Disconnected";

}

int ChatListModel::rowCount(const QModelIndex &parent) const
{
    return messageList.size();
}

QVariant ChatListModel::data(const QModelIndex &index, int role) const
{
    /// @todo change this implementation
    switch(role){
    case MessageRole: return messageList.at(index.row()).text();
    case OwnershipRole: return messageList.at(index.row()).isOwn();
    case TimeRole : return messageList.at(index.row()).getTime();
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

QHash<int, QByteArray> ChatListModel::roleNames() const
{
    return names;
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

const QString &ChatListModel::connectionState() const
{
    return m_connectionState;
}

void ChatListModel::setConnectionState(const QString &newConnectionState)
{
    if (m_connectionState == newConnectionState)
        return;
    m_connectionState = newConnectionState;
    emit connectionStateChanged();
}


