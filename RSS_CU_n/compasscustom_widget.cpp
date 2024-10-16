#include "compasscustom_widget.h"
#include <cmath>
#include<QDebug>
#include<qmath.h>
#define M_PI 3.14159265358979323846

CompassCustom_Widget::CompassCustom_Widget(QWidget *parent)
    : QWidget(parent), angleMainArrow(0), angleRedArrow(0), angleSideArrow(0) {}

void CompassCustom_Widget::setMainArrowAngle(int angle) {
    angleMainArrow = angle;
    update();
}

void CompassCustom_Widget::setRedArrowAngle(int angle) {
    angleRedArrow = angle;
    update();
}

void CompassCustom_Widget::setSideArrowAngle(int angle) {
    angleSideArrow = angle;
    update();
}

void CompassCustom_Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int w = width();
    int h = height();
    int radius = qMin(w, h) / 2;
    QPoint center(w / 2, h / 2);

    // Đặt màu nền
    painter.setBrush(QColor(0, 40, 40));
    painter.drawRect(rect());

    // Vẽ mặt số la bàn
    drawCompass(painter, center, radius);

    QRect widgetRect = rect();
    painter.setRenderHint(QPainter::Antialiasing);

    // Vẽ thang đo dọc bên phải
    drawLeftArc(painter, widgetRect, 10);

}

double qDegreesToRadians_k(double degrees) {
    return degrees * M_PI / 180.0;
}

//==============>compass ở giữa
void CompassCustom_Widget::drawCompass(QPainter &painter, const QPoint &center, int radius)
{
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(QColor(0, 200, 200), 2));  // Màu cyan
    painter.drawEllipse(center, radius, radius);   // Vẽ hình tròn của la bàn


    painter.setPen(QPen(QColor(0, 200, 200), 1));
    QFont font = painter.font();
    font.setPointSize(6);
    painter.setFont(font);

    for (int i = 0; i < 360; i += 30)
    {
        double angleRad = qDegreesToRadians_k(i - 90);  //để 0 độ là phía Bắc
        int x1 = center.x() + radius * cos(angleRad);
        int y1 = center.y() + radius * sin(angleRad);
        int x2 = center.x() + (radius - 8) * cos(angleRad);
        int y2 = center.y() + (radius - 8) * sin(angleRad);

        painter.drawLine(x1, y1, x2, y2);

        //  các số độ chính (0, 90, 180, 270)
        if (i % 90 == 0) {
            QString text;
            switch (i) {
            case 0: text = "0"; break;       // 0 độ ở phía Bắc
            case 90: text = "90"; break;     // 90 độ ở phía Đông
            case 180: text = "180"; break;   // 180 độ ở phía Nam
            case 270: text = "270"; break;   // 270 độ ở phía Tây
            }

            int text_x = center.x() + (radius - 15) * cos(angleRad)-5;  // Lùi vào trong compass một xíu nữa
            int text_y = center.y() + (radius - 15) * sin(angleRad) + 5;

            painter.drawText(text_x, text_y, text);  // Vẽ số đo
        }
    }

    // Vẽ các vạch bé
    for (int i = 0; i < 360; i += 10)
    {
        // Bỏ qua vạch lớn
        if (i % 30 == 0) continue;

        double angleRad = qDegreesToRadians_k(i - 90);  // Đổi để 0 độ là phía Bắc
        int x1 = center.x() + radius * cos(angleRad);
        int y1 = center.y() + radius * sin(angleRad);
        int x2 = center.x() + (radius - 5) * cos(angleRad);  // Vạch bé cách tâm 10
        int y2 = center.y() + (radius - 5) * sin(angleRad);

        painter.setPen(QPen(QColor(0, 200, 200), 1));
        painter.drawLine(x1, y1, x2, y2);  // Vẽ vạch bé
    }

    //vẽ vòng tròn ở trong chứa giá trị góc
    painter.setPen(QPen(QColor(0,255,218), 3));
    painter.drawEllipse(center, radius/3, radius/3);

    int Curren_angle_BLUE_target = 100, Curren_angle_RED_target = 145;


    // ====> Tính toán tọa độ cho mũi tên màu XANH
    QPoint p1, p2;
    double radian_1 = Curren_angle_BLUE_target * M_PI / 180.0;
    p1.setX(center.x() + (radius/3 + 3) * sin(radian_1)); // Tọa độ x
    p1.setY(center.y() - (radius/3 + 3) * cos(radian_1)); // Tọa độ y (trừ đi vì trục y tăng lên khi đi xuống)

    p2.setX(center.x() + (radius - 5) * sin(radian_1));
    p2.setY(center.y() - (radius - 5) * cos(radian_1));

    drawArrow_blue(painter, p1, p2);

    // =====> Tính toán tọa độ cho mũi tên màu ĐỎ
    QPoint p3, p4;
    double radian_2 = Curren_angle_RED_target * M_PI / 180.0;
    p3.setX(center.x() + (radius/3 + 3) * sin(radian_2)); // Tọa độ x
    p3.setY(center.y() - (radius/3 + 3) * cos(radian_2)); // Tọa độ y (trừ đi vì trục y tăng lên khi đi xuống)

    p4.setX(center.x() + (radius - 5) * sin(radian_2));
    p4.setY(center.y() - (radius - 5) * cos(radian_2));

    drawArrow_red(painter, p3, p4);


    QString text = QString::number(Curren_angle_BLUE_target) + "°";
    QFont font2 = painter.font();
    font2.setPointSize(8);
    painter.setPen(QPen(QColor(0,255,218), 3));
    painter.setFont(font2);
    painter.drawText(center.x()-8, center.y()+5, text);  // Vẽ số đo


}
void CompassCustom_Widget::drawArrow_blue(QPainter &painter, const QPoint &p1, const QPoint &p2)
{
    painter.setPen(QPen(QColor(0,245, 210), 1));

    //chiều dài của phần đáy của tam giác
    double baseLength = 10.0;
    double height = 10.0; //(từ đáy đến đỉnh)

    //góc giữa p1 và p2
    double angle = atan2(p2.y() - p1.y(), p2.x() - p1.x());

    // hai điểm đáy
    QPointF baseP1(p1.x() - (baseLength / 2) * cos(angle + M_PI / 2),
                   p1.y() - (baseLength / 2) * sin(angle + M_PI / 2));

    QPointF baseP2(p1.x() + (baseLength / 2) * cos(angle + M_PI / 2),
                   p1.y() + (baseLength / 2) * sin(angle + M_PI / 2));

    QPolygonF triangle;//polygon cho tam giác này
    triangle << QPointF(baseP1) << QPointF(baseP2) << p2;

    painter.setBrush(QColor(0,245, 210));
    painter.drawPolygon(triangle);
}
void CompassCustom_Widget::drawArrow_red(QPainter &painter, const QPoint &p1, const QPoint &p2)
{
    painter.setPen(QPen(Qt::red, 2));
    //      painter.drawLine(p1, p2);

    double angle = atan2(p2.y() - p1.y(), p2.x() - p1.x());

    int arrowHeadLength = 10;

    double arrowHeadAngle = M_PI / 7; // Góc hẹp cho mũi tên nhọn

    QPointF arrowP1 = p2 + QPointF(-arrowHeadLength * cos(angle - arrowHeadAngle),
                                   -arrowHeadLength * sin(angle - arrowHeadAngle));
    QPointF arrowP2 = p2 + QPointF(-arrowHeadLength * cos(angle + arrowHeadAngle),
                                   -arrowHeadLength * sin(angle + arrowHeadAngle));

    QPolygonF arrowHead;
    arrowHead << p2 << arrowP1 << arrowP2;

    painter.setBrush(Qt::red);
    painter.drawPolygon(arrowHead);
}

//==============> cánh cung bên trái
double convertValue(double x) {
    double yMin = 130.0;
    double yMax = 230.0;
    double xMin = -20.0;
    double xMax = 70.0;

    // Chuyển đổi giá trị
    double y = yMin + ((x + 20) * (yMax - yMin) / (xMax - xMin));
    return y;
}

QPoint getCoordinates(double angle, const QPoint& center, double radius) {
    double radian = angle * M_PI / 180.0;

    // Tính toán tọa độ
    QPoint result;
    result.setX(center.x() + radius * cos(radian)); // Tọa độ x
    result.setY(center.y() + radius * sin(radian)); // Tọa độ y (cộng vì trục y tăng lên)

    return result;
}

void CompassCustom_Widget::drawArrow(QPainter& painter, const QPoint& center, const QPoint& target)
{
    double arrowSize = 10.0;
    //    painter.setPen(QPen(Qt::red, 2));
    //    painter.drawLine(center, target);

    //góc giữa điểm đích và tâm
    double angle = atan2(center.y() - target.y(), center.x() - target.x());

    //hai điểm để tạo thành cánh mũi tên
    QPoint arrowP1 = target + QPoint(arrowSize * cos(angle + M_PI / 6), arrowSize * sin(angle + M_PI / 6));
    QPoint arrowP2 = target + QPoint(arrowSize * cos(angle - M_PI / 6), arrowSize * sin(angle - M_PI / 6));

    QPolygon arrowHead;
    arrowHead << target << arrowP1 << arrowP2;
    painter.setBrush(Qt::cyan);
    painter.drawPolygon(arrowHead);
}

void CompassCustom_Widget::drawLeftArc(QPainter &painter, const QRect &widgetRect, int value)
{
    painter.setPen(QPen(Qt::cyan, 1.5));
    int d = 153;
    QRectF arc_rect(0, -10, d, d);
    int startAngle = -130 * 16;
    int spanAngle = -100 * 16;
    painter.drawArc(arc_rect, startAngle, spanAngle);

    QFont font = painter.font();
    font.setPointSize(6);
    painter.setFont(font);

    // Tính toán vị trí để vẽ số 70 ở phía trên
    painter.drawText(QPoint(2, 12), "70°");
    painter.drawText(QPoint(0 + 2, this->height()-5), "-20°");
//--°--'--''
    //***** Vẽ mũi tên màu xanh nhỏ từ giá trị value
    int angle = convertValue(value);
    //    qDebug() << "JABEKNAKN: " << angle;
    QPoint abc = getCoordinates(double( angle), QPoint(arc_rect.center().x(), arc_rect.center().y()), d/2.0 - 2 ); // trừ thêm 2 cho mũi tên đỡ đè lên cug tròn
    //    qDebug() << "GO/*C*/A:  " << abc;

    //    painter.setPen(QPen(Qt::red, 2));
    //    painter.drawPoint(abc);

    drawArrow(painter, QPoint(arc_rect.center().x(), arc_rect.center().y()), abc);
}


