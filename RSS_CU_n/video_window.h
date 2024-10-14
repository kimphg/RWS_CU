#ifndef VIDEO_WINDOW_H
#define VIDEO_WINDOW_H

#include <QWidget>

class video_window : public QWidget
{
    Q_OBJECT
public:
    explicit video_window(QWidget *parent = nullptr);
public:
    void SetImg(QImage img);
signals:

};

#endif // VIDEO_WINDOW_H
