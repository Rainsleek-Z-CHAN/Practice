#ifndef SQLITE_H
#define SQLITE_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVector>
#include "user.h"
class sqLite
{
public:

    static sqLite *getDatabaseInstence();  //静态的获取数据库对象的函数

    //插入一个用户信息
    bool insertUsr(user &usr);

    //根据name查找用户
    bool findUsr(QString name);

    //匹配name和pwd
    bool judge(QString name, QString pwd);

    //匹配name和答案
    bool judge2(QString name ,QString answer);

    //返回密保问题
    QString verify(QString name);

    //返回密码
    QString verify2(QString name);

    //返回性别
    QString verify3(QString name);

    //返回年龄
    QString verify4(QString name);
private:
    sqLite();
    QSqlDatabase db_;
};

#endif // SQLITE_H

