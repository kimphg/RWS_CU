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
