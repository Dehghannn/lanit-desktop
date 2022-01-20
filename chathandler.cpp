#include "chathandler.h"

ChatHandler::ChatHandler(QObject *parent) : QObject(parent)
{
    numberOfChats = 0;
    m_noActiveChat = true;
    emptyChat = new ChatListModel;
    emptyFileList = new FileListModel;
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

    connect(&fileTransferHandler, &FileTransferHandler::newIncomingFile, this, &ChatHandler::onNewIncomingFileConnection);
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
    fileTransferHandler.start();
}

FileListModel *ChatHandler::activeFileList() const
{
    if(!m_noActiveChat){
        return m_activeFileListptr;
    }
    return emptyFileList;
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
        ChatListModel *newChatList = new ChatListModel(this);
        newChatList->setUserIP(user->userIP());
        userChatMap.insert(*user, newChatList);
        setActiveChat(newChatList);
        emit newChatStarted(userIP);
    }
    delete user; //check later
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
    m_activeFileListptr = &m_activeChatptr->fileListModel;
    emit activeChatChanged();
    emit activeFileListChanged();
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

void ChatHandler::onNewOutgoingFile(QString fileName)
{
    qDebug() << "new outgoing file called with file name : " << fileName;
    FileMessage *fileMessage = new FileMessage(fileName); //FileListModel will be responsible for this object
    fileMessage->setIsOwn(true);
    fileTransferHandler.newOutgoingFile(activeChat()->getUserIP(), fileName, fileMessage);
    ///@todo add the file message to the file list model object
    activeChat()->fileListModel.addFileMessage(fileMessage);
    connect(fileMessage, &FileMessage::progressUpdated, activeFileList(), &FileListModel::onProgressUpdated);

}

void ChatHandler::onNewIncomingFileConnection(Receive *receiver)
{
    connect(receiver, &Receive::newFileRequest, this, &ChatHandler::onNewIncomingFileRequest);

}

void ChatHandler::onNewIncomingFileRequest(QString fileName, qint64 fileSize, QString address)
{
    FileMessage *fileMessage = new FileMessage; ///@todo FileMessage must be compatible with receiving files
    fileMessage->setFileName(fileName);
    fileMessage->setFileSize(fileSize);
    fileMessage->setIsOwn(false);
    Receive *receiver = qobject_cast<Receive*>(sender());
    connect(receiver, &Receive::progressUpdated, fileMessage, &FileMessage::updateProgress);
    ///@todo connect a signal from FileMessage to Receive object here for request response
    ChatListModel* chat = getChatByIP(address);
    if(chat != nullptr){
        chat->fileListModel.addFileMessage(fileMessage);
    }else{
        startNewChat(address);
        chat = getChatByIP(address);
        chat->fileListModel.addFileMessage(fileMessage);
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

ChatListModel* ChatHandler::getChatByIP(QString address)
{
    User user;
    user.setUserIP(address);
    auto iterator = userChatMap.find(user);
    if(iterator != userChatMap.end()){
        return iterator.value();
    }else{
        return nullptr;
    }
}

