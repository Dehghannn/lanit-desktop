#ifndef USER_H
#define USER_H
#include <QString>
#include <QTimer>
#include <QHostAddress>
#include <QObject>

class User : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString nickName READ nickName WRITE setNickName NOTIFY nickNameChanged)
    Q_PROPERTY(bool isOnline READ isOnline WRITE setIsOnline NOTIFY isOnlineChanged)
public:
    User(QObject *parent=0);
    virtual ~User() {}
    QString nickName() const;
    void setNickName(const QString &nickName);

    bool isOnline() const;
    void setIsOnline(bool isOnline);

    QHostAddress userIP() const;
    void setUserIP(const QHostAddress &userIP);
    void setUserIP(const QString &userIP);
    bool operator == (const User &obj);
public slots:
    void setOffline();
    void keepOnline();
signals:
    void nickNameChanged();
    void isOnlineChanged();

private:
    QString m_nickName;
    bool m_isOnline;
    QHostAddress m_userIP;
    QTimer *timer;
};
#endif // USER_H
