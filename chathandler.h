#ifndef CHATHANDLER_H
#define CHATHANDLER_H

#include <QObject>

/**
 * @brief The ChatHandler class manages the active chat and passing it to qml
 */
class ChatHandler : public QObject
{
    Q_OBJECT
public:
    explicit ChatHandler(QObject *parent = nullptr);

signals:

};

#endif // CHATHANDLER_H
