#include "video_window.h"

#include <QPainter>
#include<QDebug>

video_window::video_window(QWidget *parent) : QFrame(parent)
{

    this->SetImg(QImage(":/images/images/novideo.png"));
    //    this->setFixedSize(800,600);
    //    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
}

void video_window::SetImg(QImage im)
{
    this->img=im;
    update();
}
void video_window::paintEvent(QPaintEvent *p)
{
    QPainter* pPainter = new QPainter(this);
    pPainter->drawImage(rect(), img,img.rect());

    QWidget::paintEvent(p);
    int www = rect().width();
    printf("Rect:%d",www);
    _flushall();

    //--> vẽ các bounding box
    QPen penYellow(Qt::yellow); // Màu vàng cho bounding box bình thường
    QPen penRed(Qt::red);       // Màu đỏ cho bounding box được chọn

//    QPainter *painter = new QPainter(this);
//    if(!Vector_BoundingBox.empty())
//        for (const BoundingBox &box : Vector_BoundingBox)
//        {
//            if (box.id == ID_Selected)
//            {
//                pPainter->setPen(penRed);
//            }
//            else
//            {
//                pPainter->setPen(penYellow);
////                qDebug() << "======================KHANG=======================";
//            }
//            pPainter->drawRect(box.x, box.y, box.width, box.height);
//        }
    delete pPainter;
}
