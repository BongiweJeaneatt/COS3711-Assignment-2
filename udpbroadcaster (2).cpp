#include "udpbroadcaster.h"
#include <QHostAddress>

UDPBroadcaster::UDPBroadcaster(QObject *parent) : QObject(parent) {
    socket = new QUdpSocket(this);
}

void UDPBroadcaster::sendXML(const QString &xmlData) {
    QByteArray data = xmlData.toUtf8();
    socket->writeDatagram(data, QHostAddress::Broadcast, port);
}