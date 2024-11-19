#ifndef VIDEOTHREAD_H
#define VIDEOTHREAD_H

#include <QImage>
#include <QObject>
#include <QQueue>
#include <QThread>
#include <QUdpSocket>

class VideoThread : public QThread
{
    Q_OBJECT
public:
    explicit VideoThread(QObject *parent = nullptr);
    void run();
    QUdpSocket* videoSocket;
//    QImage imgVideo;
    QQueue<QByteArray> videoBuff;
    QByteArray getFrame();
//signals:
//    void newVideo();
};

#endif // VIDEOTHREAD_H
