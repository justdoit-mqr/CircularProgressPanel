#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->widget->setStyleSheet("background-color:#2B648B;");
    circularProgressPanel = new CircularProgressPanel(this);
    ui->gridLayout->addWidget(circularProgressPanel,0,0,1,1);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    if(ui->pushButton->text() == "start")
    {
        circularProgressPanel->smallCircleStartMove();
        ui->pushButton->setText("stop");
    }
    else if(ui->pushButton->text() == "stop")
    {
        circularProgressPanel->smallCircleStopMove(false);
        ui->pushButton->setText("start");
    }
}

