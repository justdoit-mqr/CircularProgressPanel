#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "circularProgressPanel.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    CircularProgressPanel *circularProgressPanel;

};

#endif // WIDGET_H
