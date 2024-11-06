#ifndef VIDEO_WINDOW_H
#define VIDEO_WINDOW_H

#include <QFrame>
#include <QWidget>


struct BoundingBox {
    int id;
    int x;
    int y;
    int width;
    int height;
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
signals:

protected slots:
    void paintEvent(QPaintEvent *p);
};

#endif // VIDEO_WINDOW_H
