#include "receiverwindow.h"

ReceiverWindow::ReceiverWindow(QWidget *parent) : QMainWindow(parent) {
    display = new QTextEdit(this);
    display->setReadOnly(true);
    setCentralWidget(display);

    receiver = new UDPReceiver(this);
    connect(receiver, &UDPReceiver::xmlReceived, display, &QTextEdit::setPlainText);
}