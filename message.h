#ifndef MESSAGE_H
#define MESSAGE_H
#include <QString>
#include <QMetaType>
#include <QTime>
/**
 * @brief The Message class represents a message in a chat
 */
class Message
{
public:
    Message();
    QString text() const;
    void setText(const QString &text);

    bool isOwn() const;
    void setIsOwn(bool isOwn);

    bool isFile() const;
    void setIsFile(bool isFile);

    QString getUserIP() const;
    void setUserIP(const QString &value);

    QString getTime() const;
    void setTime(const QString &time);

private:
    QString m_text;
    QString m_time = "";
    bool m_isOwn = false;
    bool m_isFile = false;
    QString userIP;

};
Q_DECLARE_METATYPE(Message);
#endif // MESSAGE_H
