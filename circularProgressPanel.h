/*
 *@author: 缪庆瑞
 *@date:   2020.04.13
 *@brief:  圆形进度面板
 * 该类继承自QWidget，重新实现paintevent()用来绘制整个界面。在PC上效果流畅度都还不错，
 * 但在我们的Arm板子(性能较低，无GPU)上，当该界面动态刷新时就需要占用较多的cpu去绘图，
 * 动态刷新间隔越短或者paintEvent()内部处理越复杂，cpu占用率就越高。虽然该类内将固定不变
 * 的背景图提前绘制到了pixmap上，降低了一定的cpu占用，但还是需要注意不要将刷新间隔设置
 * 的过短，另外可以适当调整角度增量宏OUTER_CIRCLE_ANGLE_INCREMENT，从视觉上提高刷新速度。
 */
#ifndef CIRCULARPROGRESSPANEL_H
#define CIRCULARPROGRESSPANEL_H

#include <QWidget>
#include <QPointF>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

class CircularProgressPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CircularProgressPanel(QWidget *parent = 0,int fixedWidth=260,int fixedHeight=260);
    void setCircleRatio(qreal outerCircleRatio,qreal innerCircleRatio);//设置外圆与内圆占比
    //文本设置接口
    void setTextProperty(QPen textPen = QPen(QColor(Qt::white)),QFont textFont=QFont());//设置文本属性
    void setText(const QString &text);//设置显示的文本
    //小圆运动设置接口
    void setSmallCircleCenter(int angle);//设置小圆圆心(由外圆半径和角度计算而得)
    void smallCircleStartMove(int ms=150);//小圆开始移动
    void smallCircleStopMove(bool returnStartPos = true);//小圆停止移动

protected:
    virtual void paintEvent(QPaintEvent  *event);

private:
    void drawBackgroundPixmap();//绘制背景图
    void drawRotarySmallCircle(QPainter &painter);//绘制旋转的小圆

    QPointF circleCenter;//部件的中心点(即外圆和内圆的圆心)
    qreal outerCircleRadius;//外圆半径
    qreal innerCircleRadius;//内圆半径
    QRectF outerCircleRect;//外圆所在矩形
    QRectF innerCircleRect;//内圆所在矩形
    QPixmap backgroundPixmap;//外圆和内圆绘制的宿主设备

    QPointF smallCircleCenter;//小圆圆心
    QTimer *smallCircleTimer;//刷新小圆位置的定时器
    int smallCircleCurrentAngle;//小圆当前相对circleCenter的角度

    QPen textPen;//文本画笔
    QFont textFont;//文本字体
    QString text;//文本内容

signals:

public slots:
    void smallCircleTimerSlot();//刷新小圆位置的定时器响应槽
};

#endif // CIRCULARPROGRESSPANEL_H
