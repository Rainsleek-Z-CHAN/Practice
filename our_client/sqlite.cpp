#include "sqlite.h"
#include <QSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include<QString>
#include "user.h"


sqLite *sqLite::getDatabaseInstence()
{
    static sqLite sqldb;
    return &sqldb;
}

//插入一个用户信息
bool sqLite::insertUsr(user &usr)
{
    QString sql = QString("insert into t_usr values('%1', '%2', '%3', '%4', '%5', '%6','%7')")
            .arg(usr.name())
            .arg(usr.passwd())
            .arg(usr.passwds())
            .arg(usr.sex())
            .arg(usr.age())
            .arg(usr.question())
            .arg(usr.answer());

    // 1.打开数据
    if (!db_.open())
    {
        qDebug() << "open:" << db_.lastError().text();
        return false;
    }

    // 2.执行sql
    QSqlQuery query(db_);
    if (!query.exec(sql))
    {
        qDebug() << "insert:" << query.lastError().text();
        return false;
    }

    //关闭数据库
    db_.close();
    return true;

}

//根据name查找用户
bool sqLite::findUsr(QString name)
{
    QString sql = QString("select name from t_usr where name = :name;");
    //打开数据库
    if(!db_.open())
    {
        qDebug() << "open fail" << db_.lastError().text();
        exit(-1);
    }

    //执行插入操作
    QSqlQuery query(db_);
    query.prepare(sql);
    query.bindValue(":name",QVariant(name));
    query.exec();

    //查询成功
    if(query.next())
    {
        if(name == query.value(0).toString()) //用户存在
        {
           return true;
        }
    }

    //关闭数据库
    db_.close();

    return false;
}

//匹配name和pwd
bool sqLite::judge(QString name, QString pwd)
{
    QString sql = QString("select name, passwd from t_usr where name = :name;");
    //打开数据库
    if(!db_.open())
    {
        qDebug() << "open fail" << db_.lastError().text();
        exit(-1);
    }

    //执行插入操作
    QSqlQuery query(db_);
    query.prepare(sql);
    query.bindValue(":name",QVariant(name));
    query.exec();

    //匹配密码
    if(query.next())
    {
        if(!(pwd == query.value(1).toString()))
        {
          return false;
        }
    }
    qDebug()<<query.value(1).toString();
    //关闭数据库
    db_.close();

    return true;
}

bool sqLite::judge2(QString name, QString answer){
    QString sql = QString("select name, answer from t_usr where name = :name;");
    //打开数据库
    if(!db_.open())
    {
        qDebug() << "open fail" << db_.lastError().text();
        exit(-1);
    }

    //执行插入操作
    QSqlQuery query(db_);
    query.prepare(sql);
    query.bindValue(":name",QVariant(name));
    query.exec();

    //匹配密保问题
    if(query.next())
    {
        if(!(answer == query.value(1).toString()))
        {
          return false;
        }
    }

    //关闭数据库
    db_.close();

    return true;
}

QString sqLite::verify(QString name){
    QString sql = QString("select name, question from t_usr where name = :name;");
    QString que;
    //打开数据库
    if(!db_.open())
    {
        qDebug() << "open fail" << db_.lastError().text();
        exit(-1);
    }

    //执行插入操作
    QSqlQuery query(db_);
    query.prepare(sql);
    query.bindValue(":name",QVariant(name));
    query.exec();
    query.next();
    que=query.value(1).toString();
    //关闭数据库
    db_.close();
    qDebug()<<que;
    return que;
}
QString sqLite::verify2(QString name){
    QString sql = QString("select name, passwd from t_usr where name = :name;");
    QString que;
    //打开数据库
    if(!db_.open())
    {
        qDebug() << "open fail" << db_.lastError().text();
        exit(-1);
    }

    //执行插入操作
    QSqlQuery query(db_);
    query.prepare(sql);
    query.bindValue(":name",QVariant(name));
    query.exec();
    query.next();
    que=query.value(1).toString();
    //关闭数据库
    db_.close();
    qDebug()<<que;
    return que;
}
QString sqLite::verify3(QString name){
    QString sql = QString("select name, sex from t_usr where name = :name;");
    QString que;
    //打开数据库
    if(!db_.open())
    {
        qDebug() << "open fail" << db_.lastError().text();
        exit(-1);
    }

    //执行插入操作
    QSqlQuery query(db_);
    query.prepare(sql);
    query.bindValue(":name",QVariant(name));
    query.exec();
    query.next();
    que=query.value(1).toString();
    //关闭数据库
    db_.close();
    qDebug()<<que;
    return que;
}
QString sqLite::verify4(QString name){
    QString sql = QString("select name, age from t_usr where name = :name;");
    QString que;
    //打开数据库
    if(!db_.open())
    {
        qDebug() << "open fail" << db_.lastError().text();
        exit(-1);
    }

    //执行插入操作
    QSqlQuery query(db_);
    query.prepare(sql);
    query.bindValue(":name",QVariant(name));
    query.exec();
    query.next();
    que=query.value(1).toString();
    //关闭数据库
    db_.close();
    qDebug()<<que;
    return que;
}
sqLite::sqLite()
{
    //先判断连接是否存在
    if(QSqlDatabase::contains("testConnection"))
    {
        db_ = QSqlDatabase::addDatabase("testConnection");
    }
    else
    {
        //1.加载数据库驱动
        db_ = QSqlDatabase::addDatabase("QSQLITE", "testConnection");
        qDebug () << db_.connectionName();//打印连接名称

        //2.设置数据库名
        db_.setDatabaseName("talking.db");
        qDebug () << db_.databaseName();
    }

    //3.打开数据库
       if(db_.open())
       {
           qDebug() << "open success";
       }
       else
       {
           qDebug() << "open:" << db_.lastError().text();
           return;
       }

       //4.操作数据库：执行sql语句(integer类型的主键会自增)
       QString sql = "create table if not exists t_usr(name varchar(50), passwd varchar(20),passwds varchar(20) ,sex varchar(10), age varchar(20), question varchar(20), answer varchar(20));";
       QSqlQuery query(db_);
       if (query.exec(sql))
       {
           qDebug() << "create success.";
       }
       db_.close();
}
