#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void savecfg();
    void loadcfg();
private slots:
    void login();
    void regis();

    void on_pushButton_clicked();

signals:
    //登录成功后发射信号
    void sendUsrname(QString name);


private:
    Ui::MainWindow *ui;

    QString name;
    QString password;
};

#endif // MAINWINDOW_H
