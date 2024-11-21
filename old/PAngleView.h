#ifndef QCUSTOM_FRAME_H
#define QCUSTOM_FRAME_H
#define degrees(x) ((x)*57.295779513)
#define radians(x) ((x)/57.295779513)
#define CONST_NM 1.852// he so chuyen doi tu km sang hai ly
#define PI_NHAN2                    6.2831853072
#define PI_CHIA2                    1.5707963268
#define PI                       3.14159265358979323846
#include <QWidget>
#include <QFrame>
#include <qevent.h>
class PAngleView: public QFrame
{
    Q_OBJECT
public:
    explicit PAngleView(QWidget *parent = 0);
    double robotX,robotY,robotTheta;
    void setRobotPosition(double x, double y, float dir);
protected:
    void highLight();
    void resetView();
    void hoverEnter(QHoverEvent *event);
    void hoverLeave(QHoverEvent *event);
    void hoverMove(QHoverEvent *event);
    bool event(QEvent *event);

signals:

public slots:
protected slots:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent*);
};

#endif // QCUSTOM_FRAME_H
