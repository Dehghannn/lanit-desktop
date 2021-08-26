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
int main(int argc, char *argv[])
{

      QQuickStyle::setStyle("Material");
//    UDPbroadcaster BroadCaster;
//    //UDPlistener listener;
//    QThread thread;
//    QTimer timer;
//    BroadCaster.moveToThread(&thread);
//    QObject::connect(&thread, &QThread::started, &BroadCaster, &UDPbroadcaster::startTimer);
//    BroadCaster.setNickName("Ali");
//    thread.start();

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

//    QStringListModel model;
 //   qRegisterMetaType<User>();
//    model.setStringList(QStringList() << "hello " << "amir "<< "ali");
    QList<User*> listTest;
    User amir;
    amir.setNickName("amir");
    amir.setUserIP("192.168.1.10");
    listTest.append(&amir);
    //engine.rootContext()->setContextProperty("Users", QVariant::fromValue(application)); // QVariant::fromValue(application.usersList)

    engine.load(url);

    return app.exec();

}
