#include "qcustomslider.h"

#include <QPainter>

QCustomSlider::QCustomSlider(QWidget *parent) :
    QSlider(parent)
{

}
void QCustomSlider::paintEvent(QPaintEvent *event)
{

//    printf("linepos:%f\n",linepos);
    QSlider::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(QBrush(Qt::black),1));
    int pos = this->sliderPosition();
    float max = this->maximum();
    float min = this->minimum();
    float margin =6;
    float linepos=0;
    for(int  tickpos = min;tickpos<max;tickpos+=this->tickInterval()*3)
    {
        linepos = height()-margin-(tickpos-min)/(max-min)*(height()-2*margin);
        painter.drawLine(width()*0.1,linepos,width()*0.9,linepos);

    }
    painter.setPen(QPen(QBrush(Qt::white ),1));
    linepos = height()-margin-(pos-min)/(max-min)*(height()-2*margin);
    painter.drawLine(0,linepos,width(),linepos);
    painter.setBrush(QColor(90,160,140,180));
    painter.drawRect(width()/2-18,linepos-10,36,20);
    painter.setPen(QPen(QBrush(Qt::white),2));
    painter.drawText(width()/2-12,linepos+5,QString::number(pos/100.0,'f',2));

//    _flushall();
}
