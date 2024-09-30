#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QUdpSocket>
#include <QDateTime>
#include <QKeyEvent>
#include <QFileDialog>
//#include "c_aver_capture.h"
#include "c_gimbal_control.h"
//#include "opencv2/core/core.hpp"
////#include "opencv2/objdetect.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include "opencv2/features2d/features2d.hpp"
//#include "opencv2/nonfree/nonfree.hpp"
//#include "opencv2/flann/flann.hpp"
//#include "opencv2/calib3d/calib3d.hpp"
//#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <fstream>
#include <time.h>
//#include <videostab.h>
//using namespace cv;
namespace Ui {
class MainWindow;
}
typedef struct
{
    int id;
    int mClass;
    double ctx,cty;
    double w,h;
    unsigned long long time;
    bool active;

}VideoTarget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QUdpSocket *socket,*videoSocket;
    void sendFrameVideo();
    c_gimbal_control mControl;
//    c_aver_capture mAverCap;
    void CaptureVideoCamera();
private:
    int frameID=0,chunkID=0;
    QImage imgVideo;
public slots:
    void updateData();
    void timer30ms();
    void reloadConfigParams();
protected slots:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private slots:
    void on_slider_range_valueChanged(int value);

    void on_bt_control_pulse_mode_clicked(bool checked);

    void on_bt_video_main_clicked(bool checked);

    void on_pushButton_show_setup_clicked(bool checked);

    void on_pushButton_clear_msg_clicked();

    void on_bt_control_2_pulse_clicked(bool checked);

    void on_bt_control_1_pulse_clicked(bool checked);

//    void on_comboBox_currentIndexChanged(int index);

    void on_bt_send_pid_clicked();

    void on_bt_video_test_2_clicked();

    void on_bt_video_thermal_3_clicked();

    void on_bt_video_main_2_clicked();

    void updateInfo();
//    void on_textEdit_textChanged();

    void on_slider_fov_valueChanged(int value);

    void on_bt_save_setting_clicked();

    void on_pushButton_play_video_clicked();

    void on_pushButton_power_off_clicked();

    void on_bt_control_1_pulse_clicked();

    void on_bt_control_2_pulse_clicked();


    void on_bt_send_pid_2_clicked();

    void on_bt_save_setting_2_clicked();

//    void on_bt_zero_set_clicked();

//    void on_bt_joystick_clicked(bool checked);

    void on_bt_send_pid_track_clicked();

    void on_pushButton_record_clicked(bool checked);

    void on_pushButton_show_setup_clicked();

    void on_bt_video_thermal_clicked(bool checked);

    void on_pushButton_load_setup_clicked();

    void on_pushButton_load_setup_2_clicked();

    void on_bt_zero_set_2_clicked();

    void on_slider_fov_sliderReleased();

    void on_bt_video_test_2_clicked(bool checked);

    void on_bt_video_his_equal_clicked(bool checked);

    void on_connectButton_clicked();

    void on_bt_control_file_2_clicked();

    void on_bt_control_file_2_pressed();

    void on_bt_control_file_2_released();

    void on_bt_control_file_3_pressed();

    void on_bt_control_file_3_released();

    void on_bt_zero_set_3_pressed();

    void on_bt_zero_set_3_clicked(bool checked);

    void on_bt_control_file_4_pressed();

    void on_bt_control_file_4_released();

    void on_bt_control_file_5_pressed();

    void on_bt_control_file_5_released();

    void on_bt_control_file_7_pressed();

    void on_bt_control_file_7_released();

    void on_bt_video_thermal_pressed();

    void on_bt_video_thermal_released();

    void on_bt_video_main_pressed();

    void on_bt_video_main_released();

    void on_bt_control_file_2_clicked(bool checked);

    void on_pushButton_show_setup_pressed();

    void on_bt_control_file_6_pressed();

    void on_bt_control_focusauto_pressed();

    void on_bt_control_focusauto_released();

    void on_bt_control_kv_pressed();

    void on_bt_control_kv_released();

    void on_bt_control_kv_clicked(bool checked);

    void on_bt_control_focusauto_clicked(bool checked);

    void on_radioButton_uplimit_toggled(bool checked);

    void on_radioButton_downlimit_toggled(bool checked);

    void on_radioButton_leftlimit_toggled(bool checked);

    void on_radioButton_rightlimit_toggled(bool checked);

    void on_radioButton_nolimit_toggled(bool checked);

    void on_bt_video_thermal_toggled(bool checked);

    void on_bt_video_main_toggled(bool checked);

    void on_bt_video_off_toggled(bool checked);

    void on_bt_tracksizeup_clicked();

    void on_bt_tracksizeup_2_clicked();

    void on_pushButton_sightup_clicked();

    void on_pushButton_sight_right_clicked();

    void on_bt_control_usb_toggled(bool checked);

    void on_bt_control_usb_2_toggled(bool checked);

    void on_bt_stab_2_clicked();

    void on_bt_f_1_clicked();

    void on_bt_f_2_clicked();

    void on_bt_f_3_clicked();

    void on_bt_f_4_clicked();

    void on_bt_f_5_clicked();

    void on_bt_f_6_clicked();

    void on_bt_video_thermal_clicked();

    void on_bt_f_2_clicked(bool checked);

    void on_bt_f_1_clicked(bool checked);

    void on_bt_control_focusauto_2_clicked(bool checked);

    void on_toolButton_sightup_clicked();

private:
    bool isEqualizeHis = false;
    bool nightMode = false;
    QTimer *updateTimer;
    QTimer *controlTimer;
    Ui::MainWindow *ui;
    void sendFrame();
    std::vector<VideoTarget> vTargetList;
    double sight_x,sight_y;
    double trackpoint_x,trackpoint_y;
    int trackSize = 90;
    int trackermode = 0;
    int frame_process_W = 720.0;
    int frame_process_H = 576.0;
    void ReadVideoTargets(QStringList data);
    void DrawVideoTargets(QPainter *p);
    void draw_sight_cv(int posx, int posy);
    void ReadVideoInfo(QStringList data);
    void processDatagram(QByteArray data);
    double track_p =2,track_i=0,track_d=0;
    double fallVideo=0;
//    double mScaleX = 1,mScaleY=1;
    void processDetectorData(QByteArray data);
    void draw_sight_paint(QPainter *p);
    void draw_sight_paint(QPainter *p, int posx, int posy);
    void processDatagramLaser(QByteArray data);
    void processKeyBoardEvent(int key);
    void showMessage(QString msg);
    QString msgShown;
    int msgTime=0;
    void trackerShutdown();
    void usbInit();
    void draw_trackpoint(QPainter *p, int posx, int posy);
    void setStimstate(int value);
};

#endif // MAINWINDOW_H
