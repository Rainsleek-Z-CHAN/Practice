#include "person.h"
#include "ui_person.h"
#include"sqlite.h"
#include<QMessageBox>

#include<QLabel>
#include"mytcpclient.h"
#include<QDebug>
person::person(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::person)
{
    ui->setupUi(this);
    setWindowTitle(tr("个人主页!"));
}
void person::recUsrname(QString name){
    this->pname=name;
    qDebug()<<pname;
    sqLite* db = sqLite::getDatabaseInstence();
    picture();
    ui->le_name->setText(pname);
    ui->le_age->setText(db->verify4(pname));

}
void person::picture(){
    sqLite* db = sqLite::getDatabaseInstence();
    if(db->verify3(pname)=="man"){
       image=new QImage("D:/code/our_client/timg1.jpg");

    }
    else{

    image=new QImage("D:/code/our_client/timg2.jpg");}
    QPixmap *pixmap=new QPixmap();
    pixmap->convertFromImage(*image);
    QLabel *label=new QLabel(this);
    label->setGeometry(100,0,400,400);
    label->setPixmap(*pixmap);
    return;
}
person::~person()
{
    delete ui;
}

void person::on_pushButton_3_clicked()
{
    QMessageBox::information(this, "关于我们!", "我们是来自大连理工大学软件学院1809班的软件开发小组，负责从项目企划、项目实现到项目发布的一系列工作。致力于用更好的产品让用户体验到在同一个局域网下聊天的乐趣，并致敬20年前的初代聊天软件，带来新一轮网络文艺复兴!", "请多多支持我们，谢谢ヾ(≧▽≦*)o!");
}

void person::on_pushButton_clicked()
{
    mytcpclient=new MyTcpClient;
    connect(this, SIGNAL(sendUsrname(QString)), mytcpclient, SLOT(recUsrname(QString)));

    //发射信号
    emit sendUsrname(pname);
    mytcpclient->setAttribute(Qt::WA_DeleteOnClose);
    this->close();
    mytcpclient->show();
}

void person::on_pushButton_2_clicked()
{

    this->close();
    mainwindow=new MainWindow;
    mainwindow->show();
}
