#ifndef ADDSTU_H
#define ADDSTU_H
#include"mainwindow.h"
#include <QDialog>
#include<QButtonGroup>

namespace Ui {
class addStu;
}

class addStu : public QDialog
{
    Q_OBJECT

public:
    explicit addStu(QWidget *parent = nullptr);
    ~addStu();
    void returnmain();

private slots:
    void on_btn_Ok_clicked();

    void on_btn_Cancel_clicked();
signals:
    void send(QString b,QString c);
private:
    Ui::addStu *ui;
    QButtonGroup getModeSelect;
    QString name;

};

#endif // ADDSTU_H
