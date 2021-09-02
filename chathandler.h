#ifndef CHATHANDLER_H
#define CHATHANDLER_H

#include <QObject>

class ChatHandler : public QObject
{
    Q_OBJECT
public:
    explicit ChatHandler(QObject *parent = nullptr);

signals:

};

#endif // CHATHANDLER_H
