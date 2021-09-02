#ifndef CHAT_H
#define CHAT_H

#include <QObject>
/**
 * @brief The Chat class represents each chat with each user that holds a list of messages
 */
class Chat : public QObject
{
    Q_OBJECT
public:
    explicit Chat(QObject *parent = nullptr);

signals:

};

#endif // CHAT_H
