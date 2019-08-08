#include "style.h"
#include "ui_style.h"

Style::Style(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Style)
{
    ui->setupUi(this);

    connect(ui->b,&QPushButton::clicked,this,&Style::sendSlot);
    connect(ui->b1,&QPushButton::clicked,this,&Style::sendSlot1);
    connect(ui->b2,&QPushButton::clicked,this,&Style::sendSlot2);
    connect(ui->b3,&QPushButton::clicked,this,&Style::sendSlot3);
    connect(ui->b4,&QPushButton::clicked,this,&Style::sendSlot4);
}

Style::~Style()
{
    delete ui;
}

void Style::sendSlot(){
    emit mySignal();
}
void Style::sendSlot1(){
    emit mySignal1();
}
void Style::sendSlot2(){
    emit mySignal2();
}
void Style::sendSlot3(){
    emit mySignal3();
}
void Style::sendSlot4(){
    emit mySignal4();
}
