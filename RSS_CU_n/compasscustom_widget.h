#ifndef COMPASSCUSTOM_WIDGET_H
#define COMPASSCUSTOM_WIDGET_H

#include <QWidget>
#include <QPainter>

class CompassCustom_Widget : public QWidget {
    Q_OBJECT

public:
    explicit CompassCustom_Widget(QWidget *parent = nullptr);

    // Setters để cập nhật các mũi tên
    void setMainArrowAngle(float angle);
    void setRedArrowAngle(float angle);
    void setYellowAngle(float angle);

protected:
    void paintEvent(QPaintEvent *event) override;

public:

    void drawCompass(QPainter &painter, const QPoint &center, int radius);
    void drawMainArrow(QPainter &painter, const QPoint &center, int radius, int angle);
    void drawRedArrow(QPainter &painter, const QPoint &center, int radius, int angle);
    void drawSideGauge(QPainter &painter, const QPoint &center, int radius, int angle);
    void drawLeftArc(QPainter &painter, const QRect &widgetRect);
    void drawArrow(QPainter& painter, const QPoint& center, const QPoint& target);
    void drawArrow_blue(QPainter &painter, const QPoint &p1, const QPoint &p2);
     void drawArrow_red(QPainter &painter, const QPoint &p1, const QPoint &p2);
     void setElevationAngleYellow(float value);

     void setElevationAngleRed(float value);

private:
     float angleMainArrow=0;
     float angleRedArrow=20;
     float angleyellow=10;
     float elevationAngleYellow=20;
     float elevationAngleRed=30;
     void drawArrow_yellow(QPainter &painter, const QPoint &p1, const QPoint &p2);
};

#endif // COMPASSCUSTOM_WIDGET_H
