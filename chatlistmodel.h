#ifndef CHATLISTMODEL_H
#define CHATLISTMODEL_H

#include <QAbstractListModel>

#include <QList>
#include "message.h"
#include "user.h"
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
    User user() const;
    void setUser(const User &user);

private:
    QList<Message> messageList;
    User m_user; /// user related to this chat

};

#endif // CHATLISTMODEL_H
