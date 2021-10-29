#ifndef CHATLISTMODEL_H
#define CHATLISTMODEL_H

#include <QAbstractListModel>

#include <QList>
#include "message.h"
class ChatListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ChatListModel(QObject* parent = nullptr);
    Q_PROPERTY(QString connectionState READ connectionState WRITE setConnectionState NOTIFY connectionStateChanged)
    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool insertRows(int row, int count, const QModelIndex &parent);
    QHash<int, QByteArray> roleNames() const;

    void addMessage(Message &message);
    void reset();


    QString getUserIP() const;
    void setUserIP(const QString &value);


    enum {
        MessageRole = Qt::UserRole +1 ,
        TimeRole,
        OwnershipRole
    };

    enum{
        Connected,
        Disconnected,
        Connecting
    };

    const QString &connectionState() const;
    void setConnectionState(const QString &newConnectionState);

signals:
    void connectionStateChanged();

private:
    QList<Message> messageList;
    QString userIP; /// IP of the other person in the chat
    QHash<int, QByteArray> names; /// hash map used for roleNames
    QString m_connectionState;



};

#endif // CHATLISTMODEL_H
