#include "app.h"

App::App(QObject *parent) : QObject(parent)
{

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

QString App::getNickNamebyIP(QString ip)
{
    User *user = new User;
    user->setUserIP(ip);
    int index = getUserIndex(*user);
    return userList().at(index)->nickName();
}

void App::getAttachedFile()
{
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::HomeLocation).last());
    QString fileName;
    if(fileDialog.exec()){
        fileName = fileDialog.selectedFiles().last();
        emit newOutgoingFile(fileName); /// after a file is selected this will trigger a transfer
        qDebug() << fileName;
    }

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

void App::onCreatedNewUser(QString userIP)
{
    User* user = new User;
    user->setUserIP(userIP);
    user->setNickName(userIP);
    m_usersList.append(user);
    emit userListChanged();
    qDebug() << "new user with ip address of " << userIP << " was created";
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
