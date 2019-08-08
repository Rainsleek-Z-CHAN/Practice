#ifndef USER_H
#define USER_H
#include <QString>

class user
{
public:
    user(QString name="", QString passwd="",QString passwds="", QString sex="", QString age="", QString question="",QString answer="");
    QString name() const;
    void setName(const QString &name);

    QString passwd() const;
    void setPasswd(const QString &passwd);

    QString passwds() const;
    void setPasswds(const QString &passwds);

    QString sex() const;
    void setSex(const QString &sex);

    QString age() const;
    void setAge(const QString &age);

    QString question() const;
    void setQuestion(const QString &question);

    QString answer() const;
    void setAnswer(const QString &answer);
private:
    QString name_;
    QString passwd_;
    QString passwds_;
    QString sex_;
    QString age_;
    QString question_;
    QString answer_;
};

#endif // USER_H
