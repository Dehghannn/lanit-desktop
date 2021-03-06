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
    Q_PROPERTY(QString userIP READ userIP WRITE setUserIP NOTIFY userIPChanged)
public:
    User(QObject *parent=0);
    User(const User &user);
    virtual ~User() {}
    QString nickName() const;
    void setNickName(const QString &nickName);

    bool isOnline() const;
    void setIsOnline(bool isOnline);

    QString userIP() const;
    void setUserIP(const QHostAddress &userIP);
    void setUserIP(const QString &userIP);
    bool operator == (const User &obj);
    bool operator == (const User &obj) const;
    void operator = (const User &obj);

public slots:
    void setOffline();
    void keepOnline();
signals:
    void nickNameChanged();
    void isOnlineChanged();
    void userIPChanged();

private:
    QString m_nickName;
    bool m_isOnline;
    QString m_userIP;
    QTimer *timer;
};

inline uint qHash(const User &key, uint seed)
{
    return qHash(key.userIP(), seed);
}
#endif // USER_H
