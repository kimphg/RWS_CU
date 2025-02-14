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
#include "videothread.h"
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

#include<compasscustom_widget.h>
#include <QProcess>
#include<control_center_dialog.h>
#include<video_window.h>

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
    QUdpSocket *socket;
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

    void on_daysight_bt_next_1_clicked();

    void on_daysight_bt_next_2_clicked();

    void on_daysight_bt_next_3_clicked();

    void on_daysight_bt_next_44_clicked();
    void on_bt_irsight_bt_next_1_clicked();

    void on_irsight_bt_next_2_clicked();

    void on_irsight_bt_next_3_clicked();

    void on_irsight_bt_next_4_clicked();

    void on_weapon_bt_next_1_clicked();

    void on_weapon_bt_next_2_clicked();

    void on_weapon_bt_next_3_clicked();

    void on_bt_weapon_init_FC_clicked();

    void on_bt_weapon_warning_fire_clicked();

    void on_bt_fire_conrrections_clicked();

    void on_bt_system_events_clicked();

    void on_pushButton_pause_toggled(bool checked);
    void updateVideo();
    void on_pushButton_open_file_clicked();

    void on_bt_system_diagnostic_clicked();

    void on_pushButton_autoRequestStatus_clicked();

    void on_pushButton_autoRequestStatus_toggled(bool checked);

//    void processActuatorResponse();
//    void processMotionResponse();
//    void processMcuResponse();

    void requestSystemStat();
    void on_pushButton_stab_clicked(bool checked);

    void on_pushButton_elevation_clicked();

    void on_toolButton_azimuth_clicked();

    void on_pushButton_minus_05_clicked();

    void on_pushButton_minus_025_clicked();

    void on_pushButton_025_mrad_second_clicked();

    void on_pushButton_05_mrad_second_clicked();

    void on_pushButton_pid_set_clicked();

public:
    void setButtonStyle(QPushButton *button, const QString &image1Path, const QString &image2Path);

    void sendCommand(QString command);
    void ControlSocket(const QString& ipAddress, quint16 port, const QString& message);
    void StartStatusRequest();
//    void setupUdpListeners();
private:
    int fineMoveMode=0;
    bool isEqualizeHis = false;
    bool nightMode = false;
    VideoThread *videoManager;
    QTimer *updateTimer;
    QTimer *controlTimer;
    QTimer *videotimer;
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
//    void processDatagram(QByteArray data);
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
    void Setup_button_stype();

    QProcess *pythonProcess;

    Control_Center_Dialog *m_Control_Center_Dialog;
    QVector<BoundingBox>Vector_BoundingBox;

//    void SendVisionROIPosition();
    void SendVisionROIPosition(int16_t x, int16_t y);
    void SendVisionROISize(int16_t sx, int16_t sy);
    void SendVisionEstab(bool enable);

    QTimer *RequestStatusTimer;

//    QUdpSocket* actuatorSocket;
//    QUdpSocket* motionSocket;
    //    QUdpSocket* mcuSocket;
    void processUDP(QByteArray data);
    void readMotionStatus(QStringList parts);
    void readTrackerStatus(QStringList parts);
};

#endif // MAINWINDOW_H
