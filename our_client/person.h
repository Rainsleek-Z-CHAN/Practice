#ifndef PERSON_H
#define PERSON_H

#include <QDialog>
#include<QPixmap>
#include"mainwindow.h"
#include"mytcpclient.h"

namespace Ui {
class person;
}

class person : public QDialog
{
    Q_OBJECT

public:
    explicit person(QWidget *parent = nullptr);
    ~person();
private slots:
    void recUsrname(QString name);
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
signals:
    void sendUsrname(QString name);
private:
    void picture();
private:
    Ui::person *ui;
    QString pname;
    QImage *image;
    MainWindow *mainwindow;
    MyTcpClient *mytcpclient;
};

#endif // PERSON_H
