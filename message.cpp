#include "message.h"

Message::Message()
{

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
