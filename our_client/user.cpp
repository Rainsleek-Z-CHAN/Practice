#include "user.h"

user::user(QString name, QString passwd,QString passwds, QString sex, QString age, QString question,QString answer):
    name_(name), passwd_(passwd),passwds_(passwds),sex_(sex), age_(age),question_(question),answer_(answer)
{

}
QString user::name() const
{
    return name_;
}

void user::setName(const QString &name)
{
    name_ = name;
}
QString user::passwd() const
{
    return passwd_;
}

void user::setPasswd(const QString &passwd)
{
    passwd_ = passwd;
}
QString user::passwds() const
{
    return passwds_;
}

void user::setPasswds(const QString &passwds)
{
    passwds_ = passwds;
}
QString user::sex() const
{
    return sex_;
}

void user::setSex(const QString &sex)
{
    sex_ = sex;
}
QString user::age() const
{
    return age_;
}

void user::setAge(const QString &age)
{
    age_ = age;
}
QString user::question() const
{
    return question_;
}

void user::setQuestion(const QString &question)
{
    question_ = question;
}
QString user::answer() const
{
    return answer_;
}

void user::setAnswer(const QString &answer)
{
    answer_ = answer;
}
