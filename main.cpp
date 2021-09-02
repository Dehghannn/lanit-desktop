#include "mainwindow.h"

#include <QApplication>
#include <QTimer>
#include "udpbroadcaster.h"
#include "udplistener.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "app.h"
#include <QQmlContext>
#include <QThread>
#include "user.h"
#include <QStringListModel>
#include <QQuickStyle>
#include "chathandler.h"
int main(int argc, char *argv[])
{

      QQuickStyle::setStyle("Material");

    App application;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("appCpp", &application);


    ChatHandler chathandle;
    User user;
    QHostAddress address(QHostAddress::LocalHost);
    user.setUserIP(address);
    chathandle.startNewChat(user);
    chathandle.newOutgoingTextMessage("hello");
    engine.rootContext()->setContextProperty("ChatHandler", &chathandle); // QVariant::fromValue(application.usersList)

    engine.load(url);

    return app.exec();

}
