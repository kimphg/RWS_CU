#ifndef VIDEO_WINDOW_H
#define VIDEO_WINDOW_H

#include <QFrame>
#include <QWidget>


struct BoundingBox {
    int id;
    float x;
    float y;
    float width;
    float height;
};

class video_window : public QFrame
{
    Q_OBJECT
public:
    explicit video_window(QWidget *parent = nullptr);
public:
    void SetImg(QImage im);
private:
    QImage img;
    QRect bb2rect(BoundingBox bb);
signals:

protected slots:
    void paintEvent(QPaintEvent *p);

public:
    int ID_Selected = -1; // vẽ bounding box đang được chọn là màu đỏ (-1 thì không vẽ - chưa detect được gì)
    QVector<BoundingBox> Vector_BoundingBox; //nhận thông tin các boundingbox được update từ mainwindow --> được vẽ trong paintevent();
    int getID_Selected() const;
    void selectNext();
};

#endif // VIDEO_WINDOW_H
