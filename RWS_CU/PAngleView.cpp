#include "PAngleView.h"

#include <QPainter>
QRadialGradient* radialGradient;
PAngleView::PAngleView(QWidget *parent) : QFrame(parent)
{
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);
    this->setCursor(Qt::ArrowCursor);
    resetView();

}

void PAngleView::hoverEnter(QHoverEvent *)
{

    highLight();
}

void PAngleView::hoverLeave(QHoverEvent *)
{
    resetView();
}

void PAngleView::hoverMove(QHoverEvent *)
{
    highLight();

}
void PAngleView::highLight()
{
    this->setStyleSheet("background-color: rgb(16, 32, 64);color:rgb(255, 255, 255);font: bold 12pt \"MS Shell Dlg 2\";border : 3px solid gray;");
    repaint();
}
void PAngleView::resetView()
{
    //this->setStyleSheet("background-color: rgb(16, 32, 64);color:rgb(255, 255, 255);");
    this->setStyleSheet("background-color: rgb(16, 32, 64);color:rgb(255, 255, 255);font: 12pt \"MS Shell Dlg 2\";");
    repaint();

}
void PAngleView::paintEvent(QPaintEvent *)
{
     QPainter p(this);
     p.setBrush(*radialGradient);
     p.drawEllipse(this->rect());
}

void PAngleView::resizeEvent(QResizeEvent *)
{
    QPointF ct(this->width()/2,this->height()/2);
    radialGradient =  new QRadialGradient(ct, this->width()/2, ct);
    radialGradient->setColorAt(0.0, QColor(35, 140, 35));
    radialGradient->setColorAt(1.0, QColor(35, 35, 140));
}
void PAngleView::setRobotPosition(double x, double y, float dir)
{
    robotX = x;
    robotY = y;
    robotTheta = dir;
}
bool PAngleView::event(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::HoverEnter:
        hoverEnter(static_cast<QHoverEvent*>(event));
        return true;
        break;
    case QEvent::HoverLeave:
        hoverLeave(static_cast<QHoverEvent*>(event));
        return true;
        break;
    case QEvent::HoverMove:
        hoverMove(static_cast<QHoverEvent*>(event));
        return true;
        break;
    default:
        break;
    }
    return QWidget::event(event);
}
