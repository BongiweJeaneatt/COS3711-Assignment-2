#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMenuBar>
#include <QDateTime>
#include <QXmlStreamWriter>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    setupMenu();
    broadcaster = new UDPBroadcaster(this);
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    auto *central = new QWidget(this);
    auto *layout = new QVBoxLayout(central);

    customerNameEdit = new QLineEdit();
    itemNameEdit = new QLineEdit();
    itemTypeCombo = new QComboBox();
    itemTypeCombo->addItems({"Book", "Magazine"});
    itemQuantitySpin = new QSpinBox();
    itemQuantitySpin->setMinimum(1);
    addTransactionBtn = new QPushButton("Add Transaction");

    layout->addWidget(customerNameEdit);
    layout->addWidget(itemNameEdit);
    layout->addWidget(itemTypeCombo);
    layout->addWidget(itemQuantitySpin);
    layout->addWidget(addTransactionBtn);

    transactionModel = new QStandardItemModel(this);
    treeView = new QTreeView(this);
    treeView->setModel(transactionModel);
    layout->addWidget(treeView);

    connect(addTransactionBtn, &QPushButton::clicked, this, &MainWindow::addTransaction);

    setCentralWidget(central);
}

void MainWindow::setupMenu() {
    QMenu *fileMenu = menuBar()->addMenu("File");
    QAction *broadcastAction = fileMenu->addAction("Broadcast");
    connect(broadcastAction, &QAction::triggered, this, &MainWindow::broadcastData);
}

void MainWindow::addTransaction() {
    QString customer = customerNameEdit->text();
    QString item = itemNameEdit->text();
    QString type = itemTypeCombo->currentText();
    int quantity = itemQuantitySpin->value();
    QString date = QDateTime::currentDateTime().toString(Qt::ISODate);

    QList<QStandardItem*> found = transactionModel->findItems(customer);
    QStandardItem *customerNode = found.isEmpty() ? new QStandardItem(customer) : found.first();
    if (found.isEmpty()) transactionModel->appendRow(customerNode);

    QString itemStr = QString("%1 (%2) x%3 on %4").arg(item, type).arg(quantity).arg(date);
    customerNode->appendRow(new QStandardItem(itemStr));

    customerNameEdit->clear();
    itemNameEdit->clear();
    itemQuantitySpin->setValue(1);
}

void MainWindow::broadcastData() {
    QString xml;
    QXmlStreamWriter writer(&xml);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("transactions");

    for (int i = 0; i < transactionModel->rowCount(); ++i) {
        QStandardItem *customer = transactionModel->item(i);
        writer.writeStartElement("customer");
        writer.writeAttribute("name", customer->text());
        for (int j = 0; j < customer->rowCount(); ++j) {
            writer.writeTextElement("transaction", customer->child(j)->text());
        }
        writer.writeEndElement();
    }

    writer.writeEndElement();
    writer.writeEndDocument();

    broadcaster->sendXML(xml);
}