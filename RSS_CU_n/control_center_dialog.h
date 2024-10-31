#ifndef CONTROL_CENTER_DIALOG_H
#define CONTROL_CENTER_DIALOG_H

#include <QMainWindow>

namespace Ui {
class Control_Center_Dialog;
}

class Control_Center_Dialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit Control_Center_Dialog(QWidget *parent = nullptr);
    ~Control_Center_Dialog();

private:
    Ui::Control_Center_Dialog *ui;
};

#endif // CONTROL_CENTER_DIALOG_H
