#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include"widget.h"
#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QMessageBox>
namespace Ui {
class MyTcpServer;
}

class MyTcpServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyTcpServer(QWidget *parent = 0);
    ~MyTcpServer();

private:
    Ui::MyTcpServer *ui;
    QTcpServer *tcpServer;
    QList<QTcpSocket*> tcpClient;
    QTcpSocket *currentClient;
    QWidget *w1;

private slots:
    void NewConnectionSlot();
    void disconnectedSlot();
    void ReadData();
    void on_btnConnect_clicked();
    void on_btnClear_clicked();
    void on_pushButton_clicked();
};

#endif // MYTCPSERVER_H
