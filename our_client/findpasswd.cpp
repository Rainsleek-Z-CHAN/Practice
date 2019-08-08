#include "findpasswd.h"
#include "ui_findpasswd.h"
#include "sqlite.h"
#include<QDebug>
#include<QMessageBox>
findPasswd::findPasswd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::findPasswd)
{
    ui->setupUi(this);
    setWindowTitle(tr("找回密码!"));
}

findPasswd::~findPasswd()
{
    delete ui;
}

void findPasswd::on_btnok_clicked()
{
   name=this->ui->lename->text();
   sqLite* db = sqLite::getDatabaseInstence();
   db->verify(name);
   bool rt = db->findUsr(name);
   qDebug()<<rt;
   if(rt){
       question=db->verify(name);
       ui->leque->setText(question);
       }
   else
   {
       QApplication::beep();
       QMessageBox::warning(this,"警告!","用户名未注册!","好哒!");
   }
}

void findPasswd::on_btncancel_clicked()
{
    this->close();
}

void findPasswd::on_btnfind_clicked()
{
    if(question.isEmpty()){
        QApplication::beep();
        QMessageBox::warning(this,"警告!","您未确认用户名，无密保问题!","好哒!");
    }
    else{
    answer=this->ui->leans->text();
    sqLite* db = sqLite::getDatabaseInstence();
    int rt3=db->judge2(name,answer);
    if(rt3){
        QString pswd=db->verify2(name);
        QMessageBox::information(this, "提示 !", "您的密码是!"+pswd,"终于找回密码了太好惹 !");
        this->close();
    }
    else{
        QApplication::beep();
        QMessageBox::warning(this,"警告!","密保问题错误!","好哒!");
    }
    }
}
