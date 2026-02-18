#include "udpreceiver.h"

UDPReceiver::UDPReceiver(QObject *parent) : QObject(parent) {
    socket = new QUdpSocket(this);
    socket->bind(port, QUdpSocket::ShareAddress);
    connect(socket, &QUdpSocket::readyRead, this, &UDPReceiver::processPendingDatagrams);
}

void UDPReceiver::processPendingDatagrams() {
    while (socket->hasPendingDatagrams()) {
        QByteArray data;
        data.resize(int(socket->pendingDatagramSize()));
        socket->readDatagram(data.data(), data.size());
        emit xmlReceived(QString::fromUtf8(data));
    }
}