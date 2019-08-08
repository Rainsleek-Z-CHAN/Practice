#include "mytcpserver.h"
#include "ui_mytcpserver.h"
#include"widget.h"//添加头文件
MyTcpServer::MyTcpServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyTcpServer)
{
    ui->setupUi(this);
    tcpServer = new QTcpServer(this);
    ui->edtIP->setText(QNetworkInterface().allAddresses().at(1).toString());   //获取本地IP
    ui->btnConnect->setEnabled(true);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(NewConnectionSlot()));
}

MyTcpServer::~MyTcpServer()
{
    delete ui;
}
void MyTcpServer::NewConnectionSlot()
{
     //获取客户端的连接
    currentClient = tcpServer->nextPendingConnection();
    //加入数组
    tcpClient.append(currentClient);
    ui->cbxConnection->addItem(tr("%1:%2").arg(currentClient->peerAddress().toString().split("::ffff:")[1])\
                                          .arg(currentClient->peerPort()));
    connect(currentClient, SIGNAL(readyRead()), this, SLOT(ReadData()));
    connect(currentClient, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
}

// 客户端数据可读信号，对应的读数据槽函数
void MyTcpServer::ReadData()
{
    // 由于readyRead信号并未提供SocketDecriptor，所以需要遍历所有客户端
    for(int i=0; i<tcpClient.length(); i++)
    {
        QByteArray buffer =tcpClient[i]->readAll();
        if(buffer.isEmpty())    continue;
        static QString IP_Port, IP_Port_Pre;
        IP_Port = tr("[%1:%2]:").arg(tcpClient[i]->peerAddress().toString().split("::ffff:")[1])\
                                     .arg(tcpClient[i]->peerPort());
           ui->edtRecv->append(IP_Port);
           ui->edtSend->setPlainText(IP_Port);
           ui->edtRecv->append(QString::fromLocal8Bit(buffer));
           ui->edtSend->append(QString::fromLocal8Bit(buffer));
    }
    //联合函数
    QString data = ui->edtSend->toPlainText();
    if(data == "")  return;    // 文本输入框为空时
    //全部连接
    if(ui->cbxConnection->currentIndex() == 0)
    {
        for(int i=0; i<tcpClient.length(); i++)
                tcpClient[i]->write(data.toLocal8Bit());
    }
    //指定连接
    else
    {
        QString clientIP = ui->cbxConnection->currentText().split(":")[0];
        int clientPort = ui->cbxConnection->currentText().split(":")[1].toInt();
//        qDebug() << clientIP;
//        qDebug() << clientPort;
        for(int i=0; i<tcpClient.length(); i++)
        {
            if(tcpClient[i]->peerAddress().toString().split("::ffff:")[1]==clientIP\
                            && tcpClient[i]->peerPort()==clientPort)
            {
                tcpClient[i]->write(data.toLatin1());
                return; //ip:port唯一，无需继续检索
            }
        }
    }
}
// disconnected -> disconnectedSlot 客户端断开连接的槽函数
void MyTcpServer::disconnectedSlot()
{
    //由于disconnected信号并未提供SocketDescriptor，所以需要遍历寻找
    for(int i=0; i<tcpClient.length(); i++)
    {
        if(tcpClient[i]->state() == QAbstractSocket::UnconnectedState)
        {
            // 删除存储在combox中的客户端信息
            ui->cbxConnection->removeItem(ui->cbxConnection->findText(tr("%1:%2")\
                                  .arg(tcpClient[i]->peerAddress().toString().split("::ffff:")[1])\
                                  .arg(tcpClient[i]->peerPort())));
            // 删除存储在tcpClient列表中的客户端信息
             tcpClient[i]->destroyed();
             tcpClient.removeAt(i);
        }
    }
}
// 监听--断开
void MyTcpServer::on_btnConnect_clicked()
{
    if(ui->btnConnect->text()=="监听")
    {
        bool ok = tcpServer->listen(QHostAddress::Any, ui->edtPort->text().toInt());
        if(ok)
        {
            ui->btnConnect->setText("断开");
            //ui->btnSend->setEnabled(true);
        }
    }
    else
    {
        for(int i=0; i<tcpClient.length(); i++)//断开所有连接
        {
            tcpClient[i]->disconnectFromHost();
            bool ok = tcpClient[i]->waitForDisconnected(1000);
            if(!ok)
            {
               // 处理异常
            }
            tcpClient.removeAt(i);  //从保存的客户端列表中取去除
        }
        tcpServer->close();     //不再监听端口
        ui->btnConnect->setText("监听");
    }
}


void MyTcpServer::on_btnClear_clicked()
{
    ui->edtRecv->clear();
}


void MyTcpServer::on_pushButton_clicked()
{
    w1 = new Widget(this) ;//将类指针实例化
        w1->show();
}
