# CircularProgessPanel
这是一个基于Qt widget开发的圆形进度面板组件，采用2D绘图(QPainter)的方式绘制。目前该组件风格样式基本是定死在内部代码中的，所以并不适合作为一个基类使用，但可以作为一个圆形进度面板的代码设计参考。
## 示例
![1.gif](./screenshot/1.gif)
## 功能概述
该类继承自QWidget，重新实现paintevent()用来绘制整个界面。在PC上效果流畅度都还不错，但在我们的Arm板子(性能较低，无GPU)上，当该界面动态刷新时就需要占用较多的cpu去绘图，动态刷新间隔越短或者paintEvent()内部处理越复杂，cpu占用率就越高。虽然该类内将固定不变的背景图提前绘制到了pixmap上，降低了一定的cpu占用，但还是需要注意不要将刷新间隔设置的过短，另外可以适当调整角度增量宏OUTER_CIRCLE_ANGLE_INCREMENT，从视觉上提高刷新速度。  
## 版本控制
### V0.1：
该版本在初始化时将外圆(包括小圆)和内圆都画在了QPixmap上，在paintevent()中直接调用drawPixmap()绘制图片。在绘制外圆背景图前，通过对QPainter进行坐标系转换，进而实现小圆的转动效果。  
```
    //绘制外圆背景图(坐标系变换，旋转外圆环) cpu占用相对较高
    painter.save();
    //使用平滑的像素映射转换算法
    painter.setRenderHints(QPainter::SmoothPixmapTransform);
    painter.translate(circleCenter);
    painter.rotate(-smallCircleCurrentAngle);
    painter.translate(-circleCenter);
    painter.drawPixmap(this->rect(),outerCirclePixmap);
    painter.restore();
```
### V0.2：
该版本在初始化时将外圆和内圆画在同一个QPixmap上，在paintevent()中直接调用drawPixmap()绘制图片。然后单独绘制小圆，根据角度的不同实现小圆的旋转效果，同时在小圆周围绘制一个渐变弧，跟着小圆旋转。相较于V0.1版本，降低了些cpu占用。  
```
    /************设置画笔画刷***************/
    //小圆弧画笔(以小圆为中心，在周围绘制一定长度的渐变弧)
    QPen smallCircleArcPen;
    smallCircleArcPen.setWidthF(OUTER_CIRCLE_PEN_WIDTH);
    QConicalGradient conicalGrad;//锥形渐变
    conicalGrad.setCenter(circleCenter);
    conicalGrad.setAngle(smallCircleCurrentAngle);
    conicalGrad.setColorAt(1.0, Qt::white);
    conicalGrad.setColorAt(0.9, QColor("#098BDE"));//与外圆环颜色保持一致
    conicalGrad.setColorAt(0.1, QColor("#098BDE"));//在小圆周围显示一段渐变弧
    conicalGrad.setColorAt(0.0, Qt::white);
    smallCircleArcPen.setBrush(QBrush(conicalGrad));
    //小圆画笔与画刷
    QPen smallCirclePen;
    smallCirclePen.setColor(Qt::white);
    smallCirclePen.setWidthF(2);
    QBrush smallCircleBrush = QBrush(QColor("#1CACF7"));
    /************在设备widget上绘图***************/
    //绘制小圆弧
    painter.setPen(smallCircleArcPen);
    painter.drawArc(outerCircleRect,(smallCircleCurrentAngle-36)*16,72*16);
    //绘制小圆
    painter.setPen(smallCirclePen);
    painter.setBrush(smallCircleBrush);
    painter.drawEllipse(smallCircleCenter,OUTER_CIRCLE_PEN_WIDTH*2,OUTER_CIRCLE_PEN_WIDTH*2);
```

## 作者联系方式:
**邮箱:justdoit_mqr@163.com**  
**新浪微博:@为-何-而来**  