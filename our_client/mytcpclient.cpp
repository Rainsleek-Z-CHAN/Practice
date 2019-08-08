#include "mytcpclient.h"
#include "ui_mytcpclient.h"
#include <QColorDialog>
#include<QScrollBar>
#include<QTime>
#include<QDataStream>
#include"mainwindow.h"
#include"person.h"
class widget;
MyTcpClient::MyTcpClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyTcpClient)
{
    ui->setupUi(this);
    setWindowTitle(tr("蜜汁聊天!"));
    //初始化TCP客户端
    tcpClient = new QTcpSocket(this);   //实例化tcpClient
    tcpClient->abort();                 //取消原有连接
    ui->btnConnect->setEnabled(true);
    ui->btnSend->setEnabled(false);
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(ReadData()));
    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), \
            this, SLOT(ReadError(QAbstractSocket::SocketError)));//此处\this指的是这一行还没写完，本质上意义和this一样
    connect(tcpClient,SIGNAL(clicked()),this,SLOT(sendfile()));
    connect(ui->edtSend, SIGNAL(currentCharFormatChanged(QTextCharFormat)),
            this, SLOT(currentFormatChanged(const QTextCharFormat)));
    sty = new Style();
    connect(ui->menuButton,SIGNAL(clicked(bool)),this,SLOT(on_changeStyle(bool)));//换肤
    connect(sty,&Style::mySignal,this,&MyTcpClient::dealStyle);
    connect(sty,&Style::mySignal1,this,&MyTcpClient::dealStyle1);
    connect(sty,&Style::mySignal2,this,&MyTcpClient::dealStyle2);
    connect(sty,&Style::mySignal3,this,&MyTcpClient::dealStyle3);
    connect(sty,&Style::mySignal4,this,&MyTcpClient::dealStyle4);
}
 void MyTcpClient::recUsrname(QString name)
 {
     ui->nameLabel-> setText(name);
     username=name;
 }

MyTcpClient::~MyTcpClient()
{
    delete ui;
}

void MyTcpClient::ReadData()
//其对应的信号是readyRead()函数
//读取从服务器发来的消息
{
     QString datagram=ui->edtRecv->toHtml();
     QByteArray byte2 = datagram.toLocal8Bit();
 byte2=byte2+ tcpClient->readAll();
    if(!datagram.isEmpty())
    {

     ui->edtRecv->setHtml(QString::fromLocal8Bit(byte2));
         //ui->edtRecv->setHtml(byte2);
    }
    QScrollBar *scrollbar = ui->edtRecv->verticalScrollBar();
        if (scrollbar)
        {
             scrollbar->setSliderPosition(scrollbar->maximum());
         }



}

void MyTcpClient::ReadError(QAbstractSocket::SocketError)
{
    tcpClient->disconnectFromHost();
    ui->btnConnect->setText(tr("连接"));
    QMessageBox msgBox;
    msgBox.setText(tr("failed to connect server because %1").arg(tcpClient->errorString()));
    msgBox.exec();
    //因为QMessageBox继承QDialog，而QDialog有一个神奇的函数exec()，调用这个函数后，消息循环会在这个函数里面进行更新，而调用它的函数是被“暂停”的，就是说等用户点击按钮后，调用exec()的函数才继续执行。
}
//连接服务器端函数
void MyTcpClient::on_btnConnect_clicked()
{
    if(ui->btnConnect->text()=="连接")
    {
        tcpClient->connectToHost(ui->edtIP->text(), ui->edtPort->text().toInt());
        if (tcpClient->waitForConnected(1000))  // 连接成功则进入if{}//现在是等待1s
        {
            ui->btnConnect->setText("断开");
            ui->btnSend->setEnabled(true);
        //在这种情况下，按钮才可以用
        }
    }
    else
//连接失败的情况
    {
        tcpClient->disconnectFromHost();
        if (tcpClient->state() == QAbstractSocket::UnconnectedState|| tcpClient->waitForDisconnected(1000))  //已断开连接则进入if{}
        {
            ui->btnConnect->setText("连接");
            ui->btnSend->setEnabled(false);
        }
    }
}
//读取编辑栏的数据，并清空
void MyTcpClient::on_btnSend_clicked()
{
    QString time = QDateTime::currentDateTime()
            .toString("yyyy-MM-dd hh:mm:ss");
    QString data ="用户 :";
    data+=username;
    data+=" ";
    data+=time;
    data+="\n";
    data+=ui->edtSend->toHtml();
 //朴实无华**********
    //data+=ui->edtSend->toPlainText();
    if(data != "")
    {
         tcpClient->write(data.toLocal8Bit());
    }
 ui->edtSend->clear();
}

void MyTcpClient::on_pushButton_clicked()
{
    ui->edtRecv->clear();
}


void MyTcpClient::on_btnFile_clicked()
{
    w1 = new Widget(this) ;//将类指针实例化
        w1->show();
}

void MyTcpClient::on_fontComboBox_currentFontChanged(const QFont &f)
{
    ui->edtSend->setCurrentFont(f);
    ui->edtSend->setFocus();
}

void MyTcpClient::on_boldToolBtn_clicked(bool checked)
{
    if(checked)
        ui->edtSend->setFontWeight(QFont::Bold);
    else
        ui->edtSend->setFontWeight(QFont::Normal);
    ui->edtSend->setFocus();
}


void MyTcpClient::on_italicToolBtn_clicked(bool checked)
{
    ui->edtSend->setFontItalic(checked);
    ui->edtSend->setFocus();
}

void MyTcpClient::on_underlineToolBtn_clicked(bool checked)
{
    ui->edtSend->setFontUnderline(checked);
    ui->edtSend->setFocus();
}

void MyTcpClient::on_colorToolBtn_clicked()
{
    color = QColorDialog::getColor(color, this);
    if (color.isValid()) {
        ui->edtSend->setTextColor(color);
        ui->edtSend->setFocus();
    }
}



void MyTcpClient::on_sizeComboBox_currentIndexChanged(const QString &arg1)
{
    ui->edtSend->setFontPointSize(arg1.toDouble());
    ui->edtSend->setFocus();
}
void MyTcpClient::currentFormatChanged(const QTextCharFormat &format)
{
    ui->fontComboBox->setCurrentFont(format.font());

    // 如果字体大小出错(因为我们最小的字体为9)，使用12
    if (format.fontPointSize() < 9) {
        ui->sizeComboBox->setCurrentIndex(3);
    } else {
        ui->sizeComboBox->setCurrentIndex( ui->sizeComboBox
                                          ->findText(QString::number(format.fontPointSize())));
    }
    ui->boldToolBtn->setChecked(format.font().bold());
    ui->italicToolBtn->setChecked(format.font().italic());
    ui->underlineToolBtn->setChecked(format.font().underline());
    color = format.foreground().color();
}

void MyTcpClient::on_saveToolBtn_clicked()
{
    if (ui->edtRecv->document()->isEmpty()) {
        QMessageBox::warning(0, tr("警告"), tr("聊天记录为空，无法保存！"), QMessageBox::Ok);
    } else {
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        tr("保存聊天记录"), tr("聊天记录"), tr("文本(*.txt);;All File(*.*)"));
        if(!fileName.isEmpty())
            saveFile(fileName);
    }
}
bool MyTcpClient::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("保存文件"),
                             tr("无法保存文件 %1:\n %2").arg(fileName)
                             .arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    out << ui->edtRecv->toPlainText();

    return true;
}

void MyTcpClient::on_pushButton_2_clicked()
{
    //this->close();
    //mainwindow=new MainWindow;
    //mainwindow->show();
    person *mw = new person();

    //建立连接
    connect(this, SIGNAL(sendUsrname(QString)), mw, SLOT(recUsrname(QString)));

    //发射信号
    emit sendUsrname(username);
    qDebug()<<username;
    mw->setAttribute(Qt::WA_DeleteOnClose);
    this->hide();
    mw->show();

}
void MyTcpClient::on_changeStyle(bool){
    sty->show();
}

void MyTcpClient::dealStyle(){

    setStyleSheet("background-image: url(:/png/小清新 (64).jpg);");
}
void MyTcpClient::dealStyle1(){

    setStyleSheet("background-image: url(:/png/小清新 (20).jpg);");
}
void MyTcpClient::dealStyle2(){

    setStyleSheet("background-image: url(:/png/小清新 (29).jpg);");
}
void MyTcpClient::dealStyle3(){

    setStyleSheet("background-image: url(:/png/小清新 (44).jpg);");
}
void MyTcpClient::dealStyle4(){

    setStyleSheet("background-image: url(:/png/小清新 (42).jpg);");
}
