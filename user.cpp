#include "user.h"

User::User(QObject *parent)
{
    setNickName("New User");
    setIsOnline(false);
    timer = new QTimer;
    timer->setInterval(2000);
    timer->setSingleShot(false);
    connect(timer, &QTimer::timeout, this, &User::setOffline);
    timer->start();

}

QString User::nickName() const
{
    return m_nickName;
}

void User::setNickName(const QString &nickName)
{
    m_nickName = nickName;
    emit nickNameChanged();
}

bool User::isOnline() const
{
    return m_isOnline;
}

void User::setIsOnline(bool isOnline)
{
    m_isOnline = isOnline;
    emit isOnlineChanged();
}

QHostAddress User::userIP() const
{
    return m_userIP;
}

void User::setUserIP(const QHostAddress &userIP)
{
    m_userIP = userIP;
}

void User::setUserIP(const QString &userIP)
{
    m_userIP.setAddress(userIP);
}

bool User::operator ==(const User &obj)
{
    if(this->userIP() == obj.userIP())
        return true;
    return false;
}

void User::setOffline()
{
    m_isOnline = false;
    emit isOnlineChanged();
}

void User::keepOnline()
{
    setIsOnline(true);
    timer->setInterval(2000);
}
