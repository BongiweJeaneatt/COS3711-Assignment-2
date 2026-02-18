#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include "udpbroadcaster.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addCustomer();
    void addItem();
    void addTransaction();
    void broadcastData();

private:
    QLineEdit *customerNameEdit, *itemNameEdit;
    QComboBox *itemTypeCombo;
    QSpinBox *itemQuantitySpin;
    QPushButton *addTransactionBtn;
    QStandardItemModel *transactionModel;
    QTreeView *treeView;

    UDPBroadcaster *broadcaster;
    void setupUI();
    void setupMenu();
};

#endif // MAINWINDOW_H