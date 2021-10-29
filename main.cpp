
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


    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    App application;
    ChatHandler chathandle;

    qRegisterMetaType<Message>();

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("appCpp", &application);



    engine.rootContext()->setContextProperty("ChatHandler", &chathandle);// QVariant::fromValue(application.usersList)

    engine.load(url);

    return app.exec();

}
