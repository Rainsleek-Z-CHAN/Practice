#include "addstu.h"
#include "ui_addstu.h"
#include"sqlite.h"
#include<QString>
#include<QDebug>
#include<QMessageBox>
#include<QPushButton>
#include<QDialog>
#include"mainwindow.h"
#include<user.h>
#include<sqlite.h>
#include<QButtonGroup>

addStu::addStu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addStu)
{
    ui->setupUi(this);
    setWindowTitle(tr("register"));
}

addStu::~addStu()
{
    delete ui;
}

void addStu::on_btn_Ok_clicked()
{
    name=this->ui->le_Name->text();
    QString passwd=this->ui->le_Passwd->text();
    QString passwds=this->ui->le_Passwds->text();
    QString question=this->ui->le_Que->text();
    QString answer=this->ui->le_Ans->text();
    QString age=this->ui->cbb_Age->currentText();
    QString sex=ui->rbtn_Male->isChecked() ? "man" : "girl";
    if(name.length()<1||passwd.length()<6||question.length()<1||answer.length()<1){
        if(name.length()<1){
            QApplication::beep();
            QMessageBox::warning(this,"警告!","您未输入姓名!","好哒!");
        }
         else if(passwd.length()<6){
            QApplication::beep();
            QMessageBox::warning(this,"警告!","您输入密码过短!","好哒!");
        }
        else if(question.length()<1){
            QApplication::beep();
            QMessageBox::warning(this,"警告!","您未输入密保问题!","好哒!");
        }
        else{
            QApplication::beep();
            QMessageBox::warning(this,"警告!","您未输入密保问题答案!","好哒!");
        }
    }
    else if(passwd==passwds){
      int res=QMessageBox::question(this,"请确认信息! ",name+'\n'+passwd,"好哒! ","算了吧! ");
      //qDebug()<<res;
      if(res==0){
          user user(name, passwd,passwds, sex, age, question,answer);
          sqLite* pdb = sqLite::getDatabaseInstence();
          bool rds=pdb->findUsr(name);
          if(rds){
              QApplication::beep();
              QMessageBox::warning(this,"提示!","名字重复!","好哒!");
          }
          else{
          bool ret = pdb->insertUsr(user);
          if (ret)
          {
              QMessageBox::information(this,"提示! ","注册成功! ","太好啦!(☆▽☆)! ");
              //发射信号
              emit send(name,passwd);
          }
         qDebug()<<1;
          returnmain();}

      }

   }
    else{
        QApplication::beep();
        QMessageBox::warning(this,"警告! ","两次密码不符! ","好哒! ");
    }

}
void addStu::returnmain(){

    this->close();

}

void addStu::on_btn_Cancel_clicked()
{
    this->close();
}
