#include "dialog_motion_param.h"
#include "ui_dialog_motion_param.h"

Dialog_motion_param::Dialog_motion_param(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_motion_param)
{
    ui->setupUi(this);
    socket = new QUdpSocket(this);
    int port = 4004;
    while (socket->bind(port)==false)
    {
        port++;
        //        connect(navSocket,SIGNAL(readyRead()),this, SLOT(ReadNavData()));
        //initAverCapture();
    }
    startTimer(1000);
}
void Dialog_motion_param::timerEvent(QTimerEvent *event)
{
    QByteArray dataout;
    dataout.append("CSS,param");
    socket->writeDatagram(dataout,QHostAddress("192.168.0.7"),4001);
}
Dialog_motion_param::~Dialog_motion_param()
{
    delete ui;
}

void Dialog_motion_param::on_bt_send_pid_clicked()
{
    float value = ui->lineEdit_vp->text().toFloat();
    setParam("vp",value);
    value = ui->lineEdit_vi->text().toFloat();
    setParam("vi",value);
    value = ui->lineEdit_vd->text().toFloat();
    setParam("vd",value);
    value = ui->lineEdit_hp->text().toFloat();
    setParam("hp",value);
    value = ui->lineEdit_hi->text().toFloat();
    setParam("hi",value);
    value = ui->lineEdit_hd->text().toFloat();
    setParam("hd",value);
    value = ui->lineEdit_open_loop->text().toFloat();
    setParam("vopl",value);
    value = ui->lineEdit_vibration_1->text().toFloat();
    setParam("freq1",value);
    value = ui->lineEdit_vibration_2->text().toFloat();
    setParam("freq2",value);
}
void Dialog_motion_param::setParam(QString com,float value)
{
    QByteArray dataout;
    dataout.append("$COM,set,");
    dataout.append(com.toUtf8());
    dataout.append(",");
    dataout.append(QString::number(value));
    //    dataout.append(",");
    socket->writeDatagram(dataout,QHostAddress("192.168.0.7"),4001);

}
