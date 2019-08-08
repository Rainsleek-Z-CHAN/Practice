#ifndef FINDPASSWD_H
#define FINDPASSWD_H

#include <QDialog>

namespace Ui {
class findPasswd;
}

class findPasswd : public QDialog
{
    Q_OBJECT

public:
    explicit findPasswd(QWidget *parent = nullptr);
    ~findPasswd();

private slots:

    void on_btnok_clicked();

    void on_btncancel_clicked();

    void on_btnfind_clicked();

private:
    Ui::findPasswd *ui;
    QString name;
    QString answer;
    QString question;
};

#endif // FINDPASSWD_H
