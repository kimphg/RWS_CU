#include "video_window.h"

#include <QPainter>

video_window::video_window(QWidget *parent) : QFrame(parent)
{

    this->SetImg(QImage("novideo.png"));
}

void video_window::SetImg(QImage im)
{
    this->img=im;
}
void video_window::paintEvent(QPaintEvent *p)
{
    QPainter* pPainter = new QPainter(this);
        pPainter->drawImage(rect(), img,img.rect());
        delete pPainter;
        QWidget::paintEvent(p);
        printf("Rect:%d",rect().width());
        _flushall();
}
