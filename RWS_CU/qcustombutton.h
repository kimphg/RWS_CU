#ifndef QCUSTOM_BUTTON_H
#define QCUSTOM_BUTTON_H

#include <QWidget>
#include <QToolButton>
#include <qevent.h>
class QCustomButton : public QToolButton
{
    Q_OBJECT
public:
    explicit QCustomButton(QWidget *parent = 0);
    void highLight(bool isHighLight);
protected:
    void resetView();
    void hoverEnter(QHoverEvent *event);
    void hoverLeave(QHoverEvent *event);
    void hoverMove(QHoverEvent *event);
    bool event(QEvent *event);

signals:

public slots:
};

#endif // QCUSTOM_BUTTON_H
