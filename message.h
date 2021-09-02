#ifndef MESSAGE_H
#define MESSAGE_H
#include <QString>
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

private:
    QString m_text = "";
    bool m_isOwn = false;
    bool m_isFile = false;

};

#endif // MESSAGE_H
