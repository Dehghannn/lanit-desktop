#ifndef APP_H
#define APP_H

#include <QObject>
#include <QFileDialog>
#include <QStandardPaths>
#include "udpbroadcaster.h"
#include "user.h"

class App : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString nickName READ nickName WRITE setNickName NOTIFY nickNameChanged)
    Q_PROPERTY(QList<User*> userList READ userList  NOTIFY userListChanged)
public:
    explicit App(QObject *parent = nullptr);
    UDPbroadcaster *BroadCaster;
    QString nickName() const;
    void setNickName(const QString &nickName);
    QList<User*> userList();
    Q_INVOKABLE QString getNickNamebyIP(QString ip);
    Q_INVOKABLE void getAttachedFile();
public slots:
    void startUDPservice();
    void newDatagramReceived(QNetworkDatagram datagram);
    void onCreatedNewUser(QString userIP);
signals:
    void nickNameChanged(QString nickname);
    void userListChanged();
    void newOutgoingFile(QString fileName);
private:
    QString m_nickName;
    QList<User*> m_usersList; /// list of users available
    /**
     * @brief getUserIndex
     * @param user
     * @return -1 if not found else the index in userslist
     */
    int getUserIndex(User &user);
    QFileDialog fileDialog; ///used this object to get file names to transfer
};

#endif // APP_H
