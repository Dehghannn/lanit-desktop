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
    connect(networkService, &TCPservice::connectionStateChanged, this, &ChatHandler::connectionStateChangedSlot);
    connect(networkService, &TCPservice::incommingConnection, this, &ChatHandler::incommingConnection);
    connect(this, &ChatHandler::newOutgoingTextMessage, networkService, &TCPservice::newOutgoingTextMessage);
    connect(this, &ChatHandler::newChatStarted, networkService, &TCPservice::startNewConnection);
    serverThread->start();

    //test Code
    Message *message = new Message;
    message->setText("alooo");
    activeChat()->addMessage(*message);
    Message *message2 = new Message;
    message2->setText("salam halet chetore? chi kara mikoni? khoonevade khooban?");
    message2->setIsOwn(true);
    activeChat()->addMessage(*message2);
    message->setText("ok bye");
    message->setIsOwn(false);
    activeChat()->addMessage(*message);
    message->setText("felan khodahafez");
    message->setIsOwn(true);
    activeChat()->addMessage(*message);
    activeChat()->addMessage(*message);
    activeChat()->addMessage(*message);
    activeChat()->addMessage(*message);
    activeChat()->addMessage(*message);
    activeChat()->addMessage(*message);
    activeChat()->addMessage(*message);
    activeChat()->addMessage(*message);
    activeChat()->addMessage(*message);
    activeChat()->addMessage(*message);
    activeChat()->addMessage(*message);
    activeChat()->addMessage(*message);
    activeChat()->addMessage(*message);
    activeChat()->addMessage(*message);
    activeChat()->addMessage(*message);
    activeChat()->addMessage(*message);
    activeChat()->addMessage(*message);
}

void ChatHandler::startNewChat(QString userIP)
{
    User *user = new User;
    setNoActiveChat(false);
    user->setUserIP(userIP);
    if(userChatMap.keys().contains(*user)){
        setActiveChat(userChatMap.value(*user));
        qDebug() << "user exists";

    }else{
        qDebug() << "creating a new user and chat";
        ChatListModel *newChatList = new ChatListModel;
        newChatList->setUserIP(user->userIP());
        userChatMap.insert(*user, newChatList);
        setActiveChat(newChatList);
        emit newChatStarted(userIP);
    }

}

void ChatHandler::newOutgoingTextMessageChatHandler(QString text)
{
    Message *message = new Message;
    message->setText(text);
    message->setUserIP(activeChat()->getUserIP());
    message->setIsOwn(true);
    emit newOutgoingTextMessage(*message);
    activeChat()->addMessage(*message);
    qDebug() << "message sent to " << activeChat()->getUserIP();
    //networkService.newOutgoingTextMessage(*message);
    /// @todo complete this

}

void ChatHandler::newIncomingTextMessage(Message message)
{
    User *user = new User;
    ChatListModel *chatListModel;
    user->setUserIP(message.getUserIP());
    if(userChatMap.keys().contains(*user)){ /// @todo check if this is necessary (chatListModel will be null if not)
        chatListModel = userChatMap.value(*user);
        ///@todo notify user from new message


    }else{
        qDebug() << "creating a new user and chat";
        chatListModel = new ChatListModel;
        chatListModel->setUserIP(user->userIP());
        userChatMap.insert(*user, chatListModel);
    }
    qDebug() << "new message from : " << user->userIP();
    qDebug() << message.text();
    chatListModel->addMessage(message);
    emit newMessageNotification(message.getUserIP(), message.text());

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
    qDebug() << "active chat user is " << activeChat->getUserIP();
}
void ChatHandler::connectionStateChangedSlot(QString Address, int state)
{
    ChatListModel *chat;
    User user;
    user.setUserIP(Address);
    chat = userChatMap.value(user);
    if(chat != nullptr){
        qDebug() << "Chat Status changed";
        setConnectionState(chat, state);
    }
    qDebug() << "chat was null. no state changed";
}

void ChatHandler::incommingConnection(QString Address)
{
    User *user = new User;
    ChatListModel *chatListModel;
    user->setUserIP(Address);
    if(!userChatMap.keys().contains(*user)){
        qDebug() << "creating a new user and chat";
        chatListModel = new ChatListModel;
        chatListModel->setUserIP(user->userIP());
        userChatMap.insert(*user, chatListModel);
        setConnectionState(chatListModel, ChatListModel::Connected);
    }

}

void ChatHandler::setConnectionState(ChatListModel *chat, int state)
{
    switch (state) {
    case ChatListModel::Connecting:
        chat->setConnectionState("Connecting");
        break;
    case ChatListModel::Connected:
        chat->setConnectionState("Connected");
        break;
    case ChatListModel::Disconnected:
        chat->setConnectionState("Disconnected");
    }
}

