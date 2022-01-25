#include <QCoreApplication>
#include "filetransferhandler.h"
#include <QHostAddress>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString fileName = "/home/dehghannn/Downloads/30nama/Lucifer_S01E08_720p_BluRay_30nama_30NAMA.mkv";
    QHostAddress IP = QHostAddress::LocalHost;
    FileTransferHandler handler;
    handler.setSavePath("/home/dehghannn/Pictures/r/");
    handler.start();
    handler.newOutgoingFile(IP.toString(), fileName);
    return a.exec();
}
