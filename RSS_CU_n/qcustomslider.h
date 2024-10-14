#ifndef QCUSTOMSLIDER_H
#define QCUSTOMSLIDER_H

#include <QObject>
#include <QSlider>
#include <QWidget>

class QCustomSlider : public QSlider
{
    Q_OBJECT
public:
    explicit QCustomSlider(QWidget *parent = 0);
private:
    void paintEvent(QPaintEvent *event);
};

#endif // QCUSTOMSLIDER_H
