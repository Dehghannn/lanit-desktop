#include "app.h"

App::App(QObject *parent) : QObject(parent)
{
    User* user = new User;
    user->setNickName("Hossein");
    user->setUserIP("192.168.1.1");
    m_usersList.append(user);
}

QString App::nickName() const
{
    return m_nickName;
}

void App::setNickName(const QString &nickName)
{
    m_nickName = nickName;
    //    BroadCaster->setNickName(nickName);
    emit nickNameChanged(nickName);
}

QList<User*> App::userList()
{
    return m_usersList;
}

void App::startUDPservice()
{
    BroadCaster = new UDPbroadcaster;
    connect(this, &App::nickNameChanged, BroadCaster, &UDPbroadcaster::newNickName);
    connect(BroadCaster->Listener, &UDPlistener::newDataGram, this, &App::newDatagramReceived);
    BroadCaster->setNickName(m_nickName);
    BroadCaster->startTimer();

}

void App::newDatagramReceived(QNetworkDatagram datagram)
{
    User *user = new User;
    user->setNickName(datagram.data());
    user->setUserIP(datagram.senderAddress());
    for(int i = 0; i < m_usersList.size(); i++){
        qDebug() << m_usersList.at(i)->nickName();
    }
    int index = getUserIndex(*user);
    if(index == -1){
        user->setIsOnline(true);
        m_usersList.append(user);
        emit userListChanged();
    }else{
        m_usersList.at(index)->keepOnline();
        if(user->nickName() != m_usersList.at(index)->nickName()){
            m_usersList.at(index)->setNickName(user->nickName());
            emit userListChanged();
        }
    }
}

int App::getUserIndex(User &user)
{
    for(int i = 0; i < m_usersList.size(); i++){

        if(*m_usersList.at(i) == user){

            return i;
        }
    }
    return -1;
}
