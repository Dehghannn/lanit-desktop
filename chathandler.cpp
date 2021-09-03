#include "chathandler.h"

ChatHandler::ChatHandler(QObject *parent) : QObject(parent)
{
    numberOfChats = 0;
    m_noActiveChat = true;
    emptyChat = new ChatListModel;
    networkService = new TCPservice;
    serverThread = new QThread;
    networkService->moveToThread(serverThread);
    connect(serverThread, &QThread::started, networkService, &TCPservice::startService);
    connect(networkService, &TCPservice::newIncomingTextMessage, this, &ChatHandler::newIncomingTextMessage);
    connect(this, &ChatHandler::newOutgoingTextMessage, networkService, &TCPservice::newOutgoingTextMessage);
    serverThread->start();
}

void ChatHandler::startNewChat(QString userIP)
{
    User *user = new User;
    user->setUserIP(userIP);
    if(userChatMap.keys().contains(user)){
        setActiveChat(userChatMap.value(user));
    }else{
        ChatListModel *newChatList = new ChatListModel;
        newChatList->setUserIP(user->userIP());
        userChatMap.insert(user, newChatList);
        setActiveChat(userChatMap.value(user));
        setNoActiveChat(false);
    }
}

void ChatHandler::newOutgoingTextMessageChatHandler(QString text)
{
    Message *message = new Message;
    message->setText(text);
    message->setUserIP(activeChat()->getUserIP());
    emit newOutgoingTextMessage(*message);
    //networkService.newOutgoingTextMessage(*message);
    /// @todo complete this

}

void ChatHandler::newIncomingTextMessage(Message message)
{
    User *user = new User;
    ChatListModel *chatListModel = new ChatListModel;
    user->setUserIP(message.getUserIP());
    if(userChatMap.keys().contains(*user)){
        chatListModel = userChatMap.value(*user);
        chatListModel->addMessage(message);
        ///@todo notify user from new message
        qDebug() << "new message from : " << user->userIP();
        qDebug() << message.text();

    }
}

bool ChatHandler::noActiveChat() const
{
    return m_noActiveChat;
}

void ChatHandler::setNoActiveChat(bool noActiveChat)
{
    m_noActiveChat = noActiveChat;
}

ChatListModel* ChatHandler::activeChat() const
{
    if(!m_noActiveChat){
        return m_activeChatptr;
    }
    return emptyChat;

}

void ChatHandler::setActiveChat(ChatListModel *activeChat)
{
    m_activeChatptr = activeChat;
    emit activeChatChanged();
}
