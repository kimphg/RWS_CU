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
QRect video_window::bb2rect(BoundingBox bb)
{
    QRect output((bb.x-bb.width/2.0)*width(), (bb.y-bb.height/2.0)*height(), bb.width*width(), bb.height*height());
    return output;
}
void video_window::paintEvent(QPaintEvent *p)
{
    QPainter* pPainter = new QPainter(this);
    pPainter->drawImage(rect(), img,img.rect());

    QWidget::paintEvent(p);
//    int www = rect().width();
//    printf("Rect:%d",www);
//    _flushall();

    //--> vẽ các bounding box
    QPen penYellow(Qt::yellow,2); // Màu vàng cho bounding box bình thường
    QPen penRed(Qt::red,3);       // Màu đỏ cho bounding box được chọn

    if(!Vector_BoundingBox.empty())
        for (const BoundingBox &box : Vector_BoundingBox)
        {
            if((box.id==0))//single tracking
            {
                pPainter->setPen(penRed);
                QRect bbrect = bb2rect(box);
//                pPainter->drawRect(bbrect);// todo: draw rect with corners only https://stackoverflow.com/questions/45993826/how-do-i-draw-only-corners-of-a-rectangle-in-android-canvas
               drawRectCorners(pPainter, bbrect, 10);
                pPainter->drawText(bbrect,QString::number(box.mode));
            }
            else if ((box.id == ID_Selected))//selected detection
            {
                pPainter->setPen(penRed);
                QRect bbrect = bb2rect(box);
//                pPainter->drawRect(bbrect);// todo: draw rect with corners only
                 drawRectCorners(pPainter, bbrect, 10);
                pPainter->drawText(bbrect,QString::number(box.id));
            }
            else//not selected detection
            {
                pPainter->setPen(penYellow);
                QRect bbrect = bb2rect(box);
//                pPainter->drawRect(bbrect);// todo: draw rect with corners only
                 drawRectCorners(pPainter, bbrect, 10);
                pPainter->drawText(bbrect,QString::number(box.id));
            }

        }
    delete pPainter;
}

void video_window::drawRectCorners(QPainter* pPainter, const QRect& rect, int cornerLength = 10)
{
    int left = rect.left();
    int right = rect.right();
    int top = rect.top();
    int bottom = rect.bottom();

    // Draw top-left corner
    pPainter->drawLine(left, top, left + cornerLength, top);
    pPainter->drawLine(left, top, left, top + cornerLength);

    // Draw top-right corner
    pPainter->drawLine(right, top, right - cornerLength, top);
    pPainter->drawLine(right, top, right, top + cornerLength);

    // Draw bottom-left corner
    pPainter->drawLine(left, bottom, left + cornerLength, bottom);
    pPainter->drawLine(left, bottom, left, bottom - cornerLength);

    // Draw bottom-right corner
    pPainter->drawLine(right, bottom, right - cornerLength, bottom);
    pPainter->drawLine(right, bottom, right, bottom - cornerLength);
}

int video_window::getID_Selected() const
{
    return ID_Selected;
}

void video_window::selectNext()
{
    if(!Vector_BoundingBox.empty())
    {
        for (const BoundingBox &box : Vector_BoundingBox)
        {
            if (box.id > ID_Selected)
            {
                ID_Selected =box.id;
                return;
            }

        }
        ID_Selected = -1;
        for (const BoundingBox &box : Vector_BoundingBox)
        {
            if (box.id > ID_Selected)
            {
                ID_Selected =box.id;
                return;
            }

        }

    }

}
