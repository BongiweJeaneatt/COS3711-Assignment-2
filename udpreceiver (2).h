#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QObject>
#include <QUdpSocket>

class UDPReceiver : public QObject {
    Q_OBJECT

public:
    explicit UDPReceiver(QObject *parent = nullptr);

signals:
    void xmlReceived(const QString &xmlData);

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket *socket;
    const quint16 port = 45454;
};

#endif