#ifndef UDPBROADCASTER_H
#define UDPBROADCASTER_H

#include <QObject>
#include <QUdpSocket>

class UDPBroadcaster : public QObject {
    Q_OBJECT

public:
    explicit UDPBroadcaster(QObject *parent = nullptr);
    void sendXML(const QString &xmlData);

private:
    QUdpSocket *socket;
    const quint16 port = 45454;
};

#endif