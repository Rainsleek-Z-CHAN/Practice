#ifndef STYLE_H
#define STYLE_H

#include <QWidget>

namespace Ui {
class Style;
}

class Style : public QWidget
{
    Q_OBJECT

public:
    explicit Style(QWidget *parent = 0);
    ~Style();
public slots:
    void sendSlot();
    void sendSlot1();
    void sendSlot2();
    void sendSlot3();
    void sendSlot4();

signals:
    void mySignal();
    void mySignal1();
    void mySignal2();
    void mySignal3();
    void mySignal4();
private:
    Ui::Style *ui;
};

#endif // STYLE_H
