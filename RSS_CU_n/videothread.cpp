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
    QByteArray videoBuff;

    while(true)
    {
        while(videoSocket->hasPendingDatagrams())
        {
            int len = videoSocket->pendingDatagramSize();
            QHostAddress host;
            quint16 port;
            QByteArray data;
            data.resize(len);

            videoSocket->readDatagram(data.data(),len,&host,&port);
            int newFrameID = (uchar)data.at(1);
            qDebug() <<"frame chunk id:"<<int(data.at(0));
            data.remove(0,2);

            if(newFrameID!=frameID)//new frame
            {
                frameID=newFrameID;
                imgVideo.loadFromData(videoBuff);
//                emit newVideo();
                videoBuff.clear();
                videoBuff.append(data);

            }
            else {
                videoBuff.append(data);
                }

        }
    }
}
