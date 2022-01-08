#ifndef CHATHANDLER_H
#define CHATHANDLER_H

#include <QObject>
#include "tcpservice.h"
#include "chatlistmodel.h"
#include <QThread>
#include "FileTransferCore/filetransferhandler.h"


/**
 * @brief The ChatHandler class manages the active chat and passing it to qml
 */
class ChatHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ChatListModel* activeChat READ activeChat WRITE setActiveChat NOTIFY activeChatChanged)
    Q_PROPERTY(FileListModel* activeFileList READ activeFileList NOTIFY activeFileListChanged)
    Q_PROPERTY(bool noActiveChat READ noActiveChat WRITE setNoActiveChat NOTIFY noActiveChatChanged)
public:
    explicit ChatHandler(QObject *parent = nullptr);
    FileListModel* activeFileList() const;
    ChatListModel* activeChat() const;
    void setActiveChat(ChatListModel *activeChat);

    bool noActiveChat() const;
    void setNoActiveChat(bool noActiveChat);

public slots:
    void startNewChat(QString userIP);
    void newOutgoingTextMessageChatHandler(QString text);
    void newIncomingTextMessage(Message message);
    void connectionStateChangedSlot(QString Address, int state);
    void incommingConnection(QString Address);
    void onNewOutgoingFile(QString fileName);
signals:
    void activeChatChanged();
    void noActiveChatChanged();
    void newChatStarted(QString userIP);
    void newOutgoingTextMessage(Message message);
    void newMessageNotification(QString ip, QString messageText);
    void activeFileListChanged();
private:
    TCPservice *networkService;
    QHash<User, ChatListModel*> userChatMap;
    ChatListModel *m_activeChatptr;
    FileListModel *m_activeFileListptr;
    int numberOfChats;
    bool m_noActiveChat;
    ChatListModel *emptyChat;
    FileListModel *emptyFileList;
    QThread *serverThread;
    void setConnectionState(ChatListModel* chat, int state);
    FileTransferHandler fileTransferHandler;
};

#endif // CHATHANDLER_H
