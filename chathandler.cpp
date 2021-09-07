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
        ChatListModel *newChatList = new ChatListModel; QAbstractItemModelTester(newChatList, QAbstractItemModelTester::FailureReportingMode::Fatal, this);
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
    ChatListModel *chatListModel; // = new ChatListModel;
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
    qDebug() << "active chat user is " << activeChat->getUserIP();
}
