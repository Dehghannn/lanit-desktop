#ifndef CHATHANDLER_H
#define CHATHANDLER_H

#include <QObject>
#include "tcpservice.h"
#include "chatlistmodel.h"
#include <QThread>

/**
 * @brief The ChatHandler class manages the active chat and passing it to qml
 */
class ChatHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ChatListModel* activeChat READ activeChat WRITE setActiveChat NOTIFY activeChatChanged)
    Q_PROPERTY(bool noActiveChat READ noActiveChat WRITE setNoActiveChat NOTIFY noActiveChatChanged)
public:
    explicit ChatHandler(QObject *parent = nullptr);
    ChatListModel* activeChat() const;
    void setActiveChat(ChatListModel *activeChat);

    bool noActiveChat() const;
    void setNoActiveChat(bool noActiveChat);

public slots:
    void startNewChat(QString userIP);
    void newOutgoingTextMessageChatHandler(QString text);
    void newIncomingTextMessage(Message message); /// @todo implement this
signals:
    void activeChatChanged();
    void noActiveChatChanged();
    void newOutgoingTextMessage(Message message);
private:
    TCPservice *networkService;
    QHash<User, ChatListModel*> userChatMap;
    ChatListModel *m_activeChatptr;
    int numberOfChats;
    bool m_noActiveChat;
    ChatListModel *emptyChat;
    QThread *serverThread;
};

#endif // CHATHANDLER_H
