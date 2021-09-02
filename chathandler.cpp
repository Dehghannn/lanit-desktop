#include "chathandler.h"

ChatHandler::ChatHandler(QObject *parent) : QObject(parent)
{
    numberOfChats = 0;
    m_noActiveChat = true;
    emptyChat = new ChatListModel;
}

void ChatHandler::startNewChat(User &user)
{
    if(userChatMap.keys().contains(user)){
        setActiveChat(userChatMap.value(user));
    }else{
        ChatListModel *newChatList = new ChatListModel;
        newChatList->setUserIP(user.userIP().toString());
        userChatMap.insert(user, newChatList);
        setActiveChat(userChatMap.value(user));
        setNoActiveChat(false);
    }
}

void ChatHandler::newOutgoingTextMessage(QString text)
{
    Message *message = new Message;
    message->setText(text);
    message->setUserIP(activeChat()->getUserIP());
    networkService.startNewConnection(message->getUserIP());
    /// @todo complete this

}

void ChatHandler::newIncomingTextMessage(QString text)
{

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
