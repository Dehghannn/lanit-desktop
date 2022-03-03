QT       += core quick network quickcontrols2 testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FileTransferCore/datapacket.cpp \
    FileTransferCore/filemessage.cpp \
    FileTransferCore/filetransferhandler.cpp \
    FileTransferCore/message.cpp \
    FileTransferCore/receive.cpp \
    FileTransferCore/transfer.cpp \
    app.cpp \
    chathandler.cpp \
    chatlistmodel.cpp \
    filelistmodel.cpp \
    main.cpp \
    tcpserver.cpp \
    tcpservice.cpp \
    udpbroadcaster.cpp \
    udplistener.cpp \
    user.cpp

HEADERS += \
    FileTransferCore/datapacket.h \
    FileTransferCore/filemessage.h \
    FileTransferCore/filetransferhandler.h \
    FileTransferCore/message.h \
    FileTransferCore/receive.h \
    FileTransferCore/transfer.h \
    app.h \
    chathandler.h \
    chatlistmodel.h \
    filelistmodel.h \
    tcpserver.h \
    tcpservice.h \
    udpbroadcaster.h \
    udplistener.h \
    user.h

#FORMS += \
#    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qml.qrc
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

DISTFILES += \
    readme.md

