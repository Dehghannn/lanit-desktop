#ifndef CHATLISTMODEL_H
#define CHATLISTMODEL_H

#include <QAbstractListModel>

#include <QList>
#include "message.h"
class ChatListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ChatListModel();


    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void addMessage(Message &message);
    void reset();


    QString getUserIP() const;
    void setUserIP(const QString &value);

private:
    QList<Message> messageList;
    QString userIP; /// IP of the other person in the chat

};

#endif // CHATLISTMODEL_H
