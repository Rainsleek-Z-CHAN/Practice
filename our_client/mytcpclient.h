#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QFileDialog>
#include <QColorDialog>
#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include<QWidget>
#include <QTextCharFormat>
#include"widget.h"//添加头文件
#include"mainwindow.h"
#include "style.h"
class QTcpSocket;
class QFile;
class Widget;//添加声明
namespace Ui {
class MyTcpClient;
}

class MyTcpClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyTcpClient(QWidget *parent = 0);
    ~MyTcpClient();
protected:
    bool saveFile(const QString& fileName);

signals:
    void sendUsrname(QString name);

private:
    Ui::MyTcpClient *ui;
    QTcpSocket *tcpClient;
    QWidget *w1;
    QString username;
    //私有对象

    QColor color;
    QString MyBuffer;
    Style *sty;
private slots:
    //客户端槽函数
    void ReadData();
    void ReadError(QAbstractSocket::SocketError);
    void recUsrname(QString name);

    void on_btnConnect_clicked();//接收从登录页面到来的用户名信息

    void on_btnSend_clicked();
    void on_pushButton_clicked();

    void on_btnFile_clicked();
    void on_fontComboBox_currentFontChanged(const QFont &f);
    void on_boldToolBtn_clicked(bool checked);
    void on_italicToolBtn_clicked(bool checked);
    void on_underlineToolBtn_clicked(bool checked);
    void on_colorToolBtn_clicked();
    void on_sizeComboBox_currentIndexChanged(const QString &arg1);
    //优化功能
    void currentFormatChanged(const QTextCharFormat &format);
    void on_saveToolBtn_clicked();
    void on_pushButton_2_clicked();
    void on_changeStyle(bool);
    void dealStyle();
    void dealStyle1();
    void dealStyle2();
    void dealStyle3();
    void dealStyle4();

};

#endif // MYTCPCLIENT_H
