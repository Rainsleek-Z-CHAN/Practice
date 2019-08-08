#define LOAD_CFG_VARIANT(x) cfg.value(#x)
#define SAVE_CFG_VARIANT(x) cfg.setValue(#x, x)
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QString>
#include<QDialog>
#include<QMessageBox>
#include"addstu.h"
#include "sqlite.h"
#include<QSettings>
#include"findpasswd.h"
#include"mytcpclient.h"
#include"person.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("登陆!"));
    loadcfg();
    connect(this->ui->BtnLogin,SIGNAL(clicked(bool)),this,SLOT(login()));
    connect(this->ui->btnCancel,SIGNAL(clicked(bool)),this,SLOT(regis()));
    ui->pushButton->setStyleSheet("border:none;");
    ui->leAccount->setStyleSheet("border:none;");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::login()
{
    static int count=0;
    //检验是否成功qDebug()<<"login";
    name=this->ui->leAccount->text();
    password=this->ui->lePassword->text();
    if((!name.isEmpty())&&(!password.isEmpty()))
    {
    sqLite* pdb = sqLite::getDatabaseInstence();
    bool ret1 = pdb->findUsr(name);
    if(ret1)
    {
        bool ret2 = pdb->judge(name, password);
        if (ret2)
        {
            savecfg();
            QMessageBox::information(this, "提示!", "登入成功!", "我来了呀~耶嘿!");
            //登录成功显示主窗口
            person *mw=new person;

            //建立连接
            connect(this, SIGNAL(sendUsrname(QString)), mw, SLOT(recUsrname(QString)));
            //发射信号
            emit sendUsrname(name);
            mw->setAttribute(Qt::WA_DeleteOnClose);
            this->close();
            mw->show();}
        else
        {
            QApplication::beep();
            QMessageBox::warning(this, "警告! ", "登入失败!用户名或密码错误! ", "好哒!");
            count++;
            name="";
            password="";
            savecfg();
        }
    }
    else
    {
        QApplication::beep();
        QMessageBox::warning(this, "警告! ", "登入失败! 请您先注册!", "好哒!");
        count++;
        name="";
        password="";
        savecfg();
    }
    }
    else if(name.isEmpty())
    {
        QApplication::beep();
        QMessageBox::warning(this, "警告! ", "登入失败! 请输入名字!", "好哒!");
        count++;
        name="";
        password="";
        savecfg();
    }
   else{
        QApplication::beep();
        QMessageBox::warning(this, "警告!" , "登入失败! 请输入密码!", "好哒!");
        count++;
        name="";
        password="";
        savecfg();
    }


        if(count>=3){
            disconnect(this->ui->BtnLogin,SIGNAL(clicked(bool)),this,SLOT(login()));
        }

}
void MainWindow::regis(){
    addStu d;
    d.exec();

}
void MainWindow::savecfg(){
    QSettings cfg("fzconfig.ini",QSettings::IniFormat);
    qDebug()<<3;
    SAVE_CFG_VARIANT(name);
    SAVE_CFG_VARIANT(password);
    qDebug()<<3;
    cfg.sync();
}
void MainWindow::loadcfg(){
    QSettings  cfg("fzconfig.ini",QSettings::IniFormat);
    name= LOAD_CFG_VARIANT(name).toString();
    password= LOAD_CFG_VARIANT(password).toString();
    ui->leAccount->setText(name);
    ui->lePassword->setText(password);
    qDebug()<<2;

}


void MainWindow::on_pushButton_clicked()
{
    findPasswd d;
    d.exec();
}
