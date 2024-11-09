#include "videothread.h"

VideoThread::VideoThread(QObject *parent) : QThread(parent)
{
    videoSocket = new QUdpSocket(this);
    if(videoSocket->bind(12345))
    {
        //        connect(navSocket,SIGNAL(readyRead()),this, SLOT(ReadNavData()));
        //initAverCapture();
    }
}

void VideoThread::run()
{
    int frameID=0;
    QByteArray *videoFrame = new QByteArray();
    QByteArray data;
    while(true)
    {
        while(videoSocket->hasPendingDatagrams())
        {
            int len = videoSocket->pendingDatagramSize();
//            QHostAddress host;
//            quint16 port;

            data.resize(len);

            videoSocket->readDatagram(data.data(),len);
            int newFrameID = (uchar)data.at(1);
//            qDebug() <<"frame chunk id:"<<int(data.at(0));
            data.remove(0,2);

            if(newFrameID!=frameID)//new frame
            {
                frameID=newFrameID;
//                imgVideo.loadFromData(videoFrame);
                videoBuff.enqueue(*videoFrame);
//                emit newVideo();
                videoFrame= new QByteArray();
                videoFrame->append(data);

            }
            else {
                videoFrame->append(data);
                }

        }
    }
}
QByteArray VideoThread::getFrame(){
    QByteArray frameOutput;
    if(videoBuff.length()>0)
    {
        frameOutput = videoBuff.dequeue();
        qDebug() <<"buff len:"<<videoBuff.length();
    }
    return frameOutput;
}
