#include "chatlistmodel.h"

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
    return messageList.at(index.row()).text();
}

void ChatListModel::addMessage(Message &message)
{
    messageList.append(message);

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

