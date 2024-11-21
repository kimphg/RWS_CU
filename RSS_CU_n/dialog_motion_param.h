#ifndef DIALOG_MOTION_PARAM_H
#define DIALOG_MOTION_PARAM_H

#include <QDialog>
#include <QUdpSocket>

namespace Ui {
class Dialog_motion_param;
}

class Dialog_motion_param : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_motion_param(QWidget *parent = nullptr);
    ~Dialog_motion_param();

private slots:
    void on_bt_send_pid_clicked();

private:
    Ui::Dialog_motion_param *ui;
    void setParam(QString com, float value);
    QUdpSocket *socket;
};

#endif // DIALOG_MOTION_PARAM_H
