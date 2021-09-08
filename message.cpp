#include "message.h"

Message::Message()
{
    m_time = QTime::currentTime().toString();
    m_time.chop(3);
}

QString Message::text() const
{
    return m_text;
}

void Message::setText(const QString &text)
{
    m_text = text;
}

bool Message::isOwn() const
{
    return m_isOwn;
}

void Message::setIsOwn(bool isOwn)
{
    m_isOwn = isOwn;
}

bool Message::isFile() const
{
    return m_isFile;
}

void Message::setIsFile(bool isFile)
{
    m_isFile = isFile;
}

QString Message::getUserIP() const
{
    return userIP;
}

void Message::setUserIP(const QString &value)
{
    userIP = value;
}

QString Message::getTime() const
{
    return m_time;
}

void Message::setTime(const QString &time)
{
    m_time = time;
}
