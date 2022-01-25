#include "transfer.h"
quint16 Transfer::transferCount = 0;
Transfer::Transfer(QString Address, QString fileName, QObject *parent):QObject(parent)
{
    qDebug() << "transfer object created";
    transferCount++;
    m_transferID = transferCount;
    this->fileName = fileName;
    setStatus(NotStarted);
    m_targetIP = Address;

}

Transfer::~Transfer()
{
    qDebug() << "transfer object destroyed";
    delete file;
    delete socket;
    delete info;

}

void Transfer::run()
{
    qDebug() << "started transfering thread";
    ///implement the multithreaded write function here
    QEventLoop bytesWrittenWaiterLoop;
    QEventLoop ackWaiterLoop;
    socket = new QTcpSocket(nullptr);
    connect(socket, &QTcpSocket::readyRead, this, &Transfer::readyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Transfer::disconnected);
    //connect(socket, &QTcpSocket::bytesWritten, this, &Transfer::socketBytesWritten, Qt::QueuedConnection);
    connect(socket, &QTcpSocket::bytesWritten, &bytesWrittenWaiterLoop, &QEventLoop::quit, Qt::QueuedConnection);
    connect(socket, &QTcpSocket::readyRead, &ackWaiterLoop, &QEventLoop::quit, Qt::QueuedConnection);
    file = new QFile(fileName);
    info = new QFileInfo;
    info->setFile(*file);
    fileSize = file->size();
    if(!file->open(QIODevice::ReadOnly)){
        qCritical() << "can't open file";
        return;
    }
    qInfo() << "Sending file " << fileName;
    qInfo() << "by size of " << fileSize;
    numberOfWrites = fileSize / stepSize;
    numberOfWrites += (fileSize % stepSize != 0); // rounding to next integer
    qDebug() << "numberOfWrites : " << numberOfWrites;
    socket->connectToHost(m_targetIP, port);
    if(!socket->waitForConnected(10000)){
        qInfo() << "failed to connect to receiver";
        qInfo() << socket->errorString();
        setStatus(Failed);
        file->close();
        return;
        /// @todo retry maybe
    }
    if(socket->isOpen()){
        qInfo() << "connected to host";
    }
    sendFileRequest();
    setStatus(Pending);
    if(!getRequestResponse()){
        ///file was rejected or request timed out
        file->close();
        return;
    }

    //now that user accepted transfer let's start

    //DataPacket sendPacket;
    char * seeker;
    int len = stepSize;
    char * endOfBuffer;
    setStatus(Transfering);
    qint64 packetCount = 0; ///used for updating transfer progress every totalPacketsBeforeUpdateProgress
    qDebug() << "Entering Transfer loop...";
    fileBuffer.append(fileBufferReadSize, '0');
    readFromFile();
    seeker = fileBuffer.data();
    endOfBuffer = fileBuffer.data() + fileBufferSize;
    QElapsedTimer *timer = new QElapsedTimer;
    timer->start();
    while(bytesWritten < fileSize){
        if(exit){
            return;
        }
        if(seeker == endOfBuffer){
            bytesWrittenWaiterLoop.exec();            
            readFromFile();
            seeker = fileBuffer.data();
            endOfBuffer = fileBuffer.data() + fileBufferSize;
            if(fileBufferSize < stepSize)
                len = fileBufferSize;
            emit progressUpdated(bytesWritten);
        }
        //qDebug()<< Qt::hex << seeker << endOfBuffer;
        socket->write(seeker, len);
        socket->flush();
        seeker += len;
        bytesWritten += len;
        //qDebug() << bytesWritten << " bytes were written";
        packetCount++;

    }
    emit progressUpdated(bytesWritten);
    qDebug() << "Transfer finished";
    setStatus(Finished);
    file->close();
    ackWaiterLoop.exec();
    qInfo () << "took: " << timer->elapsed() / 1000 << " seconds.";
    emit finished();
}
Transfer::State Transfer::status() const
{
    return m_status;
}

void Transfer::setStatus(State newStatus)
{
    m_status = newStatus;
    emit statusChanged(newStatus);
}

void Transfer::readyRead()
{
    m_readyRead = true;
}

void Transfer::disconnected()
{
    qDebug() << "connection closed";
    exit = true;
}

void Transfer::socketBytesWritten(qint64 bytesWritten)
{
    qDebug() << "bytesWritten called " << bytesWritten;
    //m_bytesWritten = true;
}

const QString &Transfer::targetIP() const
{
    return m_targetIP;
}

void Transfer::setTargetIP(const QString &newTargetIP)
{
    m_targetIP = newTargetIP;
}

void Transfer::waitForAck(QTcpSocket* socket)
{
    socket->waitForReadyRead();
    QByteArray answer = socket->read(3); /// a header is 3 bytes
    DataPacket packet;
    packet.extractPacket(answer);
    if(packet.type() != DataPacket::Ack){
        qDebug() << "failed to get Ack";
    }
}

void Transfer::sendFileRequest()
{
    DataPacket packet;
    qDebug() << info->fileName();
    packet.setFileRequest(info->fileName(), info->size());
    qDebug() << "file size by info = " << info->size() << " file size by file = " << file->size();
    socket->write(packet.Data());
    socket->flush();
    socket->waitForBytesWritten();
}

bool Transfer::getRequestResponse()
{
    QEventLoop loop;
    connect(socket, &QTcpSocket::readyRead, &loop, &QEventLoop::quit, Qt::QueuedConnection);
    loop.exec();
    // wait a full minute for the receiver to answer request
//    if(!socket->waitForReadyRead(60000)){ //60000
//        // timeout happened
//        qDebug() << "request timed out";
//        return false;
//    }else{
        QByteArray answer = socket->readAll();
        DataPacket responsePacket;
        responsePacket.extractPacket(answer);
        if(!responsePacket.isYes()){ // file was rejected
            qDebug() << "File was rejected by the receiver";
            setStatus(Failed);
            return false;
        }
//    }
    qDebug() << "file was accepted";
    return true;
}

void Transfer::readFromFile()
{
    fileBufferSize = file->read(fileBuffer.data(),fileBufferReadSize);
}

