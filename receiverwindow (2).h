#ifndef RECEIVERWINDOW_H
#define RECEIVERWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include "udpreceiver.h"

class ReceiverWindow : public QMainWindow {
    Q_OBJECT

public:
    ReceiverWindow(QWidget *parent = nullptr);

private:
    QTextEdit *display;
    UDPReceiver *receiver;
};

#endif