#include "control_center_dialog.h"
#include "ui_control_center_dialog.h"

Control_Center_Dialog::Control_Center_Dialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Control_Center_Dialog)
{
    ui->setupUi(this);
}

Control_Center_Dialog::~Control_Center_Dialog()
{
    delete ui;
}

void Control_Center_Dialog::on_pushButton_clicked()  //kết nối lại với video nguồn
{
    QUdpSocket udpSocket;
    QByteArray message = "CCS,RECVID";
    QHostAddress address = QHostAddress("127.0.0.1");
    quint16 port = 5000;

    qint64 bytesSent = udpSocket.writeDatagram(message, address, port);

    if (bytesSent == -1) {
        qDebug() << "Failed to send UDP message:" << udpSocket.errorString();
    } else {
        qDebug() << "UDP message sent successfully!";
    }
}
