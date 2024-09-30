#include "qcustombutton.h"
static QColor color1 = QColor(179,188,182);
static QColor color2 = QColor(162,172,165);
static QColor color3 = QColor(114,129,119);
static QColor color4 = QColor(69,78,72);
QCustomButton::QCustomButton(QWidget *parent) : QToolButton(parent)
{

    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);
    this->setCursor(Qt::ArrowCursor);
    resetView();
}

void QCustomButton::hoverEnter(QHoverEvent *)
{

//    highLight();
}

void QCustomButton::hoverLeave(QHoverEvent *)
{
    resetView();
}

void QCustomButton::hoverMove(QHoverEvent *)
{
    //highLight();

}
void QCustomButton::highLight(bool isHighLight)
{
    if(isHighLight)setStyleSheet("\
                    QCustomButton {   \
                        color:white; background-color: rgb(114,129,119);   \
                    }   \
                    QCustomButton:checked{\
                        color:white; background-color: rgb(179,188,182);\
                    }\
                    QCustomButton:hover{  \
                        color:white; background-color: rgb(69,78,72); \
                    }  \
                    ");
                                 else
                                 resetView();

}
void QCustomButton::resetView()
{
    //this->setStyleSheet("background-color: rgb(16, 32, 64);color:rgb(255, 255, 255);");
    setStyleSheet("\
                    QCustomButton {   \
                        color:white; background-color: rgba(32, 72, 72,120);   \
                    }   \
                    QCustomButton:checked{\
                        color:white; background-color: rgba(69,78,72,150);\
                    }\
                    QCustomButton:hover{  \
                        color:white; background-color: rgba(69,78,72,150); \
                    }  \
                    ");
    repaint();

}
bool QCustomButton::event(QEvent *event)
{
    /*switch(event->type())
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
    }*/
    return QWidget::event(event);
}
