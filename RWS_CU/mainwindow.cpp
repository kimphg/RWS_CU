#include "dialogconfig.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "kcf/kcf.hpp"
#include <Windows.h>
//#include "aruco/aruco.hpp"
//#include "aruco/aruco_handler.hpp"
#include <QPainter>
#include <QQueue>

#define vendorID 0x2acf
#define productID 0x0102
#define vendorID1 0x0810
#define productID1 0x0001
#define SCR_W 1280
#define SCR_H 1024

#include "UsbDevice.h"
//#include "UsbDevice.h"
HANDLE usbDevHandle ;
int usbDevMode = 0;
int cuconcount = 0;
#define USBMSG_LEN 33
DWORD msgLen =USBMSG_LEN;
// for FILE_FLAG_OVERLAPPED mode
OVERLAPPED osReader = { 0 };
#pragma comment(lib, "ws2_32.lib")
double trackx=0,trackxi=0,trackxo=0;
double tracky=0,trackyi=0,trackyo=0;
double trackHratio = 1;
double h_correction = 0;
float shipSpeed = 0;
int oldSwData=0;
int oldAziint = -999999;
int realAziint = 0;
int oldEleint = -999999;
int realEleint = 0;
int h_angle_offset=0,v_angle_offset = 0;
static QTimer *timer_1sec;
static double h_speed_control = 0;
static double v_speed_control = 0;
static int key_ad = 0;
static int key_ws = 0;
static float viewFov = 60;
//static double mControl.fov = 60;
static QRect vRect = QRect(10,10,1004,748);
static QRect plotRect = QRect(140,20,TRACK_MEM_SIZE,100);
//static int sight_x;//=frame_process_W/2+CConfig::getInt("sightx",0);
//static int sight_y;//=frame_process_H/2+CConfig::getInt("sighty",0);
static int sight_range = 100;
static  QQueue<double> dataPlot;
static VideoCapture cap;
static int frameCount=0;
static bool incomeFrame = false;
static bool camAvailable = false;
static std::vector<int> params;
static cv::Mat frame,frameOrg,frameOld;
static cv::VideoWriter recorder;
//cv::Mat f;
//static cv::Mat *pFrame;
static cv::Rect singleTrackTarget;
static cv::Rect trackrect;
static cv::Rect singleTrackWindow;
static KCF kcf_tracker("gaussian","hog");
static QColor color1 = QColor(179,188,182);
static QColor color2 = QColor(162,172,165);
static QColor color3 = QColor(114,129,119);
static QColor color4 = QColor(69,78,72);
//arucoMarker markers;
//VideoStab stab;
QByteArray videoBuff;
//aruco_handler handler;
//QHash<int,VideoTarget> vTargetList;
unsigned char usbBuf[USBMSG_LEN];
int selectVTargetIndex = -1;
static double ballistic_k=0.002;
double ballistic_calc_time(float d)
{

    double v0 = 850;
    double time = (exp(ballistic_k*d)-1)/(ballistic_k*v0);
    return time;
}
double ballistic_calc_fall_angle(double range)
{
    double time = ballistic_calc_time(range);
    double fall = 0.5*9.8*time*time;
    double angle = atan(fall/range);
    return angle;
}
double ballistic_calc_future_azi(double range,double speed)
{
    double time = ballistic_calc_time(range);
    double futureMeter = speed*time;
    double angle = atan(futureMeter/range);
    return angle;
}
//bool load_matrices(string matricesdoc) { //load existing matrices
//    ifstream a(matricesdoc);
//    vector<float> nums;
//    while (!a.fail()) {
//        float aux;
//        a >> aux;
//        nums.push_back(aux);
//    }
//    a.close();
//    if (nums.size() < 12) { return 0; }
//    for (int i = 0; i < 3; i++) {
//        cameraMatrix.at<float>(i, 0) = nums[i * 3];
//        cameraMatrix.at<float>(i, 1) = nums[i * 3 + 1];
//        cameraMatrix.at<float>(i, 2) = nums[i * 3 + 2];
//    }
//    for (int i = 0; i < nums.size() - 10; i++) {
//        distCoeffs.at<float>(i) = nums[i + 9];
//    }
//    return 1;
//}
#define DEBUG
//Mat testFrame;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//namedWindow("image", 1);
    ui->setupUi(this);
    this->statusBar()->setStyleSheet("background-color: rgb(58, 65, 60); color:rgb(255, 255, 255)");
//    this->setStyleSheet("background-color: rgb(58, 65, 60); color:rgb(255, 255, 255)");
    socket = new QUdpSocket(this);
    videoSocket = new QUdpSocket(this);
    mControl.setSocket(socket);
    CConfig::readFile();
    ui->frame_gui->hide();
    //    trackrect.x = frame.rows*0.45;
    //    trackrect.y = frame.cols*0.45;
    //    trackrect.width = frame.rows*0.1;
    //    trackrect.height = frame.cols*0.1;

    //    cap = cv::cap('test.avi');
    //    label_video_fps
    timer_1sec = new QTimer();
    connect(timer_1sec, SIGNAL(timeout()), this, SLOT(updateInfo()) );
    timer_1sec->start(1000);
    // do something..
    ui->view_azi->setValue(152);

    if(socket->bind(4000))
    {
        //        connect(navSocket,SIGNAL(readyRead()),this, SLOT(ReadNavData()));
        //initAverCapture();
    }
    else
    {
        this->statusBar()->showMessage("Socket failure, port busy");
    }
    if(videoSocket->bind(12345))
    {
        //        connect(navSocket,SIGNAL(readyRead()),this, SLOT(ReadNavData()));
        //initAverCapture();
    }
    else
    {
        this->statusBar()->showMessage("Video socket failure, port busy");
    }
    //    std::string image_path = samples::findFile("d:\\test.jpg");
    //    testFrame = imread("d:\\test.jpg", IMREAD_COLOR);
    updateTimer = new QTimer();
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateData()));
    updateTimer->start(11);

    controlTimer = new QTimer();
    connect(controlTimer, SIGNAL(timeout()), this, SLOT(timer30ms()));
    controlTimer->start(30);
    ui->statusbar-> hide ();
    params.push_back(CV_IMWRITE_JPEG_QUALITY);
    params.push_back(80); //image quality

    //window init
//    this->showFullScreen();
    ui->groupBox_setup->setHidden(true);
    this->setGeometry(0,0,1024,768);
    //    ui->plot_tracker->addGraph();

    frame_process_W = CConfig::getDouble("frame_process_W",720);
    frame_process_H = CConfig::getDouble("frame_process_H",576);
    sight_x=frame_process_W/2.0+CConfig::getDouble("sightx",7);
    sight_y=frame_process_H/2.0+CConfig::getDouble("sighty",0);
    trackSize = CConfig::getInt("trackSize",90);
    ballistic_k = CConfig::getDouble("ballistic_k",0.002);
    reloadConfigParams();
    CConfig::setValue("param_hp",3.85);
    CConfig::setValue("param_hi",5.5);
    CConfig::setValue("param_hd",0);
    CConfig::setValue("param_vp",4);
    CConfig::setValue("param_vi",5.85);
    CConfig::setValue("param_vd",1.25);
//    connect(this, SIGNAL(finished()), &mAverCap, SLOT(deleteLater));
//    mAverCap.start();
}

void MainWindow::usbInit()
{
    // message length = 32

    usbDevHandle = UsbDevice::getDeviceHandle(vendorID, productID,0);

    if (usbDevHandle) {
        usbDevMode = 1;
        showMessage(QString::fromUtf8("USB control default"));
    }
    else{
        showMessage(QString::fromUtf8("USB not found"));
        mControl.joystickMode = 0;
        return;
        usbDevHandle = UsbDevice::getDeviceHandle(vendorID1, productID1,0);
        if (!usbDevHandle) {
            usbDevMode = 2;
            showMessage(QString::fromUtf8("USB control gamepad"));//

        }
        else
        {
            usbDevMode = 0;
            showMessage(QString::fromUtf8("Không có kết nối thiết bị USB"));//
            return ;
        }
    }

    if(usbDevMode){

        osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        if (osReader.hEvent == NULL)
        {
            showMessage(QString::fromUtf8("creating overlapped event; abort." ));
            return ;
        }
    }
}
void MainWindow::reloadConfigParams()
{
    track_p =CConfig::getDouble("track_p",3);//=0,track_d=0;
    track_i =CConfig::getDouble("track_i",0.02);
    track_d =CConfig::getDouble("track_d",0);
    trackHratio = CConfig::getDouble("track_VScale",0.6);
    frame_process_W = CConfig::getDouble("frame_process_W",720);
    frame_process_H = CConfig::getDouble("frame_process_H",576);
    sight_x=frame_process_W/2.0+CConfig::getDouble("sightx",7);
    sight_y=frame_process_H/2.0+CConfig::getDouble("sighty",0);
    trackSize = CConfig::getInt("trackSize",90);
    ballistic_k = CConfig::getDouble("ballistic_k",0.002);
    mControl.reloadConfig();
    trackrect.x = (sight_x+h_correction)-trackSize/2;
    trackrect.y = sight_y-trackSize/1.25/2;
    trackrect.width = trackSize;
    trackrect.height = trackSize/1.25;
    //    kcf_tracker.setInterp_factor(CConfig::getDouble("track_learn_rate",0.075));
}
void MainWindow::sendFrame()
{
    //    socket->writeDatagram(data,QHostAddress("127.0.0.1"),30001);
}
void MainWindow::updateInfo()
{
    CConfig::SaveToFile();
    mControl.sendSetupPacket(14);
    ui->label_video_fps->setText(QString::number(frameCount));
    frameCount = 0;
    // remove old targets
    unsigned long long timeNow = QDateTime::currentMSecsSinceEpoch();
    ui->label_speed->setText(QString::number(shipSpeed));
    ui->label_fovSpeed->setText(QString::number(mControl.fov));
    float aziCorection = ballistic_calc_future_azi(sight_range,shipSpeed*0.514444);
    h_correction = aziCorection/PI*180.0/viewFov*frame.cols;
//    repaint();
//    for(int i = 0;i<vTargetList.size();i++)
//    {
//        if(vTargetList[i].active)
//            if(timeNow-vTargetList[i].time>3000)
//            {
//                vTargetList[i].active = false;
//            }
//    }
    //    repaint();
    //check connection status
    //    if(mControl.isCuAlive)ui->label_cu_connection->setText("OK");
    //    else ui->label_cu_connection->setText(QString::fromUtf8("Mất kết nối"));
    //    if(mControl.isStimAlive)ui->label_stim_stat->setText("OK");
    //    else ui->label_stim_stat->setText(QString::fromUtf8("Mất kết nối"));
    //    ui->label_cu_connection->setText(QString::number(cuconcount));
//    ui->label_stim_stat->setText(QString::number(mControl.isStimAlive));

}

void MainWindow::processKeyBoardEvent(int key)
{
    if(trackermode==0)
    {
        if(key == Qt::Key_Left)
        {
            key_ad = -1;
        }
        else if(key == Qt::Key_Right)
        {
            key_ad = 1;
        }
        else if(key == Qt::Key_Down)
        {
            key_ws=-1;
        }
        else if(key == Qt::Key_Up)
        {
            key_ws = 1;
            //        unsigned char *packet = mControl.outputPelco(0,100);
            //        socket->writeDatagram((char*)packet,7,QHostAddress("192.168.0.204"),4001);
        }

    }
    else
    {
        if(key == Qt::Key_Left)
        {
            trackpoint_x-=5;
        }
        else if(key == Qt::Key_Right)
        {
            trackpoint_x+=5;
        }
        else if(key == Qt::Key_Up)
        {
            trackpoint_y-=5;
        }
        else if(key == Qt::Key_Down)
        {
            trackpoint_y+=5;
            //        unsigned char *packet = mControl.outputPelco(0,100);
            //        socket->writeDatagram((char*)packet,7,QHostAddress("192.168.0.204"),4001);
        }
        if(trackpoint_x<(sight_x+h_correction)-100)trackpoint_x = (sight_x+h_correction)-100;
        if(trackpoint_x>(sight_x+h_correction)+100)trackpoint_x = (sight_x+h_correction)+100;
        if(trackpoint_y<sight_y-100)trackpoint_y = sight_y-100;
        if(trackpoint_y>sight_y+100)trackpoint_y = sight_y+100;
    }
//    if(key == Qt::Key_L)// start tracking at selected target
//    {

//        if(trackermode == 0)
//        {
//            if(selectVTargetIndex>=0&&selectVTargetIndex<vTargetList.size())
//            {
//                if(vTargetList[selectVTargetIndex].active)
//                {
//                    int trackW = vTargetList[selectVTargetIndex].w*frame_process_W;
//                    int trackH = vTargetList[selectVTargetIndex].h*frame_process_H;
//                    float area = (trackW*trackW+trackH*trackH);
//                    if(area>trackSize*trackSize)
//                    {
//                        float reduceRat = sqrt(area/(trackSize*trackSize));
//                        trackW*=reduceRat;
//                        trackH*=reduceRat;
//                    }
//                    if(trackW>trackSize)trackW=trackSize;
//                    if(trackH>trackSize)trackH=trackSize;
//                    trackrect.x = frame.cols*vTargetList[selectVTargetIndex].ctx -trackW/2;
//                    trackrect.y = frame.rows*vTargetList[selectVTargetIndex].cty -trackH/2;//-vTargetList[selectVTargetIndex].h*0.4);
//                    trackrect.width = trackW;//frame.cols*vTargetList[selectVTargetIndex].w*0.8;
//                    trackrect.height = trackH;//frame.rows*vTargetList[selectVTargetIndex].h*0.8;
//                    if(kcf_tracker.Init(frame,trackrect))ui->textBrowser_msg->append("target too big");;
//                    trackermode = 1;
//                    trackpoint_x=sight_x;
//                    trackpoint_y=sight_y;

//                }
//            }

//        }
//        else trackerShutdown();
//    }
//    else if(key == Qt::Key_S){ //change target
//        if(trackermode)trackerShutdown();
//        selectVTargetIndex++;
//        if(selectVTargetIndex>=vTargetList.size())
//        {
//            selectVTargetIndex=-1;
//            return;
//        }
//        while(vTargetList[selectVTargetIndex].active==false)
//        {
//            selectVTargetIndex++;
//            if(selectVTargetIndex>=vTargetList.size())
//            { selectVTargetIndex=-1;break;}
//        }



//    }
    if(key == Qt::Key_T){//start tracking

        if((!frame.empty())&&trackermode == 0)
        {



            kcf_tracker.trackLostSens = CConfig::getDouble("trackLostSens",2.5);
            if(kcf_tracker.Init(frame,trackrect))ui->textBrowser_msg->append("target too big");
            kcf_tracker.setLearning_rate(CConfig::getDouble("track_learn_rate",0.025));
            trackermode = 1;
            showMessage("Bắt đầu bám");
            trackpoint_x=(sight_x);
            trackpoint_y=sight_y;

        }
        else trackerShutdown();

    }
    else if(key == Qt::Key_F1){


        this->on_bt_f_1_clicked();
        this->ui->frame_gui->show();
    }
    else if(key == Qt::Key_F2){


        this->on_bt_f_2_clicked();
        this->ui->frame_gui->show();
    }
    else if(key == Qt::Key_F3){


        this->on_bt_f_3_clicked();
        this->ui->frame_gui->show();
    }
    else if(key == Qt::Key_F8){


        system("cmd.exe");
    }
    else if(key == Qt::Key_F9){


        system("explorer.exe");
    }
    else if(key==Qt::Key_F11)
    {
        mControl.setWorkmode(0);

    }
    else if(key==Qt::Key_Escape)
    {
        mControl.setWorkmode(1);

    }
    else if(key==Qt::Key_F12)
    {

        cap = VideoCapture(1);//(filename.toStdString().data());
        camAvailable = true;
    }
    else if(key==Qt::Key_End)
    {

        if(abs(shipSpeed)>=5)shipSpeed-=1;
        else if(abs(shipSpeed)>=10)shipSpeed-=2;
        else shipSpeed-=0.5;
        if(shipSpeed<-20)shipSpeed=-20;
    }
    else if(key==Qt::Key_Home)
    {

//        on_bt_control_file_2_pressed();

        if(abs(shipSpeed)>=5)shipSpeed+=1;
        else if(abs(shipSpeed)>=10)shipSpeed+=2;
        else shipSpeed+=0.5;

        if(shipSpeed>20)shipSpeed=20;
    }
    else if(key==Qt::Key_Delete)
    {
        on_bt_tracksizeup_2_clicked();
    }
    else if(key==Qt::Key_Insert)
    {
        on_bt_tracksizeup_clicked();
        //        on_bt_control_file_4_pressed();
    }
    else if(key==Qt::Key_M)
    {
        int a=mControl.stabMode;

        if(mControl.stabMode){
            setStimstate(0);
            ui->bt_stab_2->setChecked(false);
            ui->bt_video_test_2->setChecked(true);

        }
        else{
            setStimstate(2);
            ui->bt_video_test_2->setChecked(false);
            ui->bt_stab_2->setChecked(true);
        }
        mControl.reloadConfig();
    }
    else if(key==Qt::Key_S)
    {
        //fov narrow
        float newfov = mControl.fov/2;
        if(newfov<2)newfov=2;
        mControl.setFOV(newfov);//fov wide
    }
    else if(key==Qt::Key_L)
    {
        float newfov = mControl.fov*2;
        if(newfov>100)newfov=100;
        mControl.setFOV(newfov);//fov wide
    }
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    this->setFocus();
    int key = event->key();
    processKeyBoardEvent(key);
}
static volatile bool processorBusy = false;

void MainWindow::CaptureVideoCamera()
{
    if(processorBusy)return;
    processorBusy=true;
    if(camAvailable)
    {

        incomeFrame = cap.read(frameOrg);//single capture image
//        cv::resize(frameOrg, frameOrg, Size(640,480), INTER_LINEAR);
        Mat smoothedFrame;
        if((!frameOrg.empty())&&(!frameOld.empty()))
        {
            Mat M = estimateRigidTransform(frameOld,frameOrg,0);
            warpAffine(frameOrg,smoothedFrame,M,Size(640,480),INTER_NEAREST|WARP_INVERSE_MAP) ;
//            smoothedFrame = stab.stabilize(frameOrg , frameOld);

            frameOld =frameOrg ;
            frameOrg=smoothedFrame;
        }
        else frameOld =frameOrg ;

//        smoothedFrame = stab.stabilize(frameOrg , frameOld);

        if(!incomeFrame)
        {
            camAvailable = false;
        }

        if(frameOrg.cols>100&&frameOrg.rows>100)
        {
            if(nightMode)cv::cvtColor(frameOrg, frame, CV_BGR2GRAY);
            else cv::cvtColor(frameOrg, frame, CV_BGR2RGB);

            if((frameOrg.cols!=frame_process_W)||(frameOrg.rows!=frame_process_H))
            {
                cv::resize(frame,frame,cv::Size(frame_process_W,frame_process_H));
                //                mScaleX = double(frame_process_W)/frameOrg.cols;
                //                mScaleY = double(frame_process_H)/frameOrg.rows;
            }
            incomeFrame = true;
            waitKey(100);
        }

    }
    else
    {

        //        bool sucess = mAverCap.getFrame(&frameOrg);

//        if(mAverCap.bGetData) {
//            mAverCap.bGetData = false;

//            if(mAverCap.output.cols>100&&mAverCap.output.rows>100)
//            {
//                if(nightMode)cv::cvtColor(mAverCap.output, frame, CV_BGR2GRAY);
//                else cv::cvtColor(mAverCap.output, frame, CV_BGR2RGB);

//                if((frame.cols!=frame_process_W)||(frame.rows!=frame_process_H))
//                {
//                    cv::resize(frame,frame,cv::Size(frame_process_W,frame_process_H));
//                    //                mScaleX = double(frame_process_W)/frameOrg.cols;
//                    //                mScaleY = double(frame_process_H)/frameOrg.rows;
//                }
//                incomeFrame = true;

//            }

//        }
    }

    if(incomeFrame)
    {

        frameCount++;
        if(recorder.isOpened())
            recorder.write(frame);
        //        if(isEqualizeHis)cv::equalizeHist(frame,frame);
        update();
        //        sendFrameVideo();
        if(trackermode)
        {
            //            printf("track update start\n"); flushall();
            singleTrackTarget = kcf_tracker.Update(frame);
            singleTrackWindow = kcf_tracker.getsearchingRect();
            //            printf("track update done\n");
            //            flushall();
            bool trackFail = (singleTrackTarget.area()<100)||(singleTrackTarget.width<5)||(singleTrackTarget.height<5);
            if(trackFail)
            {

                showMessage(QString::fromUtf8("Mất bám, đang tìm kiếm..."));
                trackermode = 2;
            }
            else
            {
                if(trackermode==2)
                {
                    trackermode=1;
                }
            }
            //            cv::Rect scaledRect;
            //            scaledRect.x = singleTrackTarget.x /mScaleX;
            //            scaledRect.y = singleTrackTarget.y /mScaleY;
            //            scaledRect.width = singleTrackTarget.width /mScaleX;
            //            scaledRect.height = singleTrackTarget.height /mScaleY;

            if(trackermode==1)cv::rectangle(frame,singleTrackTarget,cv::Scalar(255, 0, 0),1,16 );
            else cv::rectangle(frame,singleTrackWindow,cv::Scalar(255, 255, 0),1,16 );


        }
        else
        {
            cv::rectangle(frame,trackrect,cv::Scalar(150, 150, 0),1,16 );
        }
    }

    //    cv::rectangle(frame,trackrect,cv::Scalar(0, 255, 0));
    processorBusy=false;
    return ;
}
void MainWindow::showMessage(QString msg)
{
    msgShown = msg;
    msgTime = 60;
    repaint();

}
void MainWindow::draw_sight_cv( int  posx, int posy)
{
    int size = vRect.height();
    int gap = int(size/4);
    cv::Scalar color(0, 255, 0);
    if(nightMode)color = cv::Scalar(255,255,255);
    cv::line(frame, cv::Point(posx-size*3,  posy),     cv::Point(posx-gap,  posy  )  , color,1);//  #crosshair horizontal
    cv::line(frame, cv::Point(posx+size*3,  posy),     cv::Point(posx+gap,  posy  )  , color,1);//  #crosshair horizontal
    cv::line(frame, cv::Point(posx,       posy-size), cv::Point( posx,       posy-gap ), color,1);//  #crosshair vertical
    cv::line(frame, cv::Point(posx,       posy+size*3), cv::Point( posx,       posy+gap ), color,1);//  #crosshair vertical
    //    cv::circle(frame, cv::Point(posx,posy), 0, color, 0.5,CV_AA);// #crosshair point center
    //    cv::circle(frame, cv::Point(posx,posy), size, color, 0.5,CV_AA);// #crosshair circle 1
    //    cv::circle(frame, cv::Point(posx,posy), size*2, color, 0.5,CV_AA);// #crosshair circle 2
    //    cv::circle(frame, cv::Point(posx,posy), size*3, color, 0.5,CV_AA);// #crosshair circle 2
    for(int range=100;range<1500;range+=100)
    {
        double fallAngle = ballistic_calc_fall_angle(range);//sight_range);
        double fallVideo = fallAngle/PI*180.0/viewFov*frame.rows;
        cv::line(frame, cv::Point(posx-size/3,  posy+fallVideo),     cv::Point(posx+size/3,  posy+fallVideo  )  , color,1);//  #crosshair horizontal

    }
    double fallAngle = ballistic_calc_fall_angle(sight_range);//sight_range);
    double fallVideo = fallAngle/PI*180.0/viewFov*frame.rows;
    cv::line(frame, cv::Point(posx-size/3,  posy+fallVideo),     cv::Point(posx+size/3,  posy+fallVideo  )  , cv::Scalar(255, 0, 0),1);//  #crosshair horizontal
}
void MainWindow::draw_trackpoint(QPainter* p,int  posx, int posy)
{
    int size = vRect.height()/20;
    int gap = int(size/4);
    QColor color(255, 255, 0);
    QPen pen(color);
    QColor color2(255, 0, 0);
    QPen pen2(color2);
    pen2.setWidth(1);
    p->setPen(pen);
    p->drawLine(posx-size,posy,   posx-gap,  posy);
    p->drawLine(posx+size,posy,   posx+gap,  posy );
    p->drawLine(posx,posy-size,     posx,      posy-gap);
    p->drawLine(posx,posy+size,   posx,      posy+gap);
}
void MainWindow::draw_sight_paint(QPainter* p,int  posx, int posy)
{
    int size = vRect.height()/8;
    int gap = int(size/4);
    p->setFont(QFont("times",8));
    QColor color(0, 255, 0);
    QPen pen(color);
    QColor color2(255, 0, 0);
    QPen pen2(color2);

//    p->drawEllipse(QPoint(posx,posy),size,size);
//    p->drawEllipse(QPoint(posx,posy),size*2,size*2);
//    p->drawEllipse(QPoint(posx,posy),size*3,size*3);
    for(int range=100;range<1500;range+=100)
    {
        double fallAngle = ballistic_calc_fall_angle(range);//sight_range);
        double fallVideo = fallAngle/PI*180.0/viewFov*vRect.height();
        size = 10;//vRect.height()/mControl.fov/range*1000;
        if(size>vRect.width()/1.5)size  = vRect.width()/1.5;
        //        p->setPen(pen2);
        if(fallVideo<(vRect.height()/2))
        {
            p->drawLine(posx-size/2,  posy+fallVideo,   posx+size/2,  posy+fallVideo);
            if(fallVideo>vRect.height()/20)
                p->drawText(posx+size/2,  posy+fallVideo,200,20,0,QString::number(range,'f',1));
        }

        //        cv::line(frame, cv::Point(posx-size/3,  posy+fallVideo),     cv::Point(posx+size/3,  posy+fallVideo  )  , color,1);//  #crosshair horizontal

    }
    double fallAngle = ballistic_calc_fall_angle(sight_range);//sight_range);
    double fallInPixels = fallAngle/PI*180.0/viewFov*vRect.height();
    fallVideo = fallInPixels*frame_process_H/vRect.height();
    pen2.setWidth(2);
    p->setPen(pen2);
    posy+=fallInPixels;
    p->drawLine(posx-size,posy,   posx-gap,  posy);
    p->drawLine(posx+size,posy,   posx+gap,  posy );
    p->drawLine(posx,posy-size,     posx,      posy-gap);
    p->drawLine(posx,posy+size,   posx,      posy+gap);
//    p->setPen(pen2);
//    size=20;
//    p->drawLine(posx-size,  posy+fallInPixels,   posx+size,  posy+fallInPixels);

}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    this->setFocus();
    int key = event->key();
    if(key == Qt::Key_Left)
    {
        key_ad = 0;
    }
    else if(key == Qt::Key_Right)
    {
        key_ad = 0;
    }
    else if(key == Qt::Key_Down)
    {
        key_ws= 0;
    }
    else if(key == Qt::Key_Up)
    {
        key_ws = 0;
    }
    else if(key==Qt::Key_End)
    {

        on_bt_control_file_3_released();
    }
    else if(key==Qt::Key_Home)
    {

        on_bt_control_file_2_released();
    }
    else if(key==Qt::Key_Delete)
    {

        on_bt_control_file_5_released();
    }
    else if(key==Qt::Key_Insert)
    {

        on_bt_control_file_4_released();
    }

}
//bool AddGaussianNoise_Opencv(const Mat mSrc, Mat &mDst,double Mean=0.0, double StdDev=40.0)
//{
//    if(mSrc.empty())
//    {
//        //        printf("\n[Error]! Input Image Empty!");
//        return 0;
//    }
//    Mat mSrc_16SC;
//    Mat mGaussian_noise = Mat(mSrc.size(),CV_16SC3);
//    randn(mGaussian_noise,Scalar::all(Mean), Scalar::all(StdDev));

//    mSrc.convertTo(mSrc_16SC,CV_16SC3);
//    addWeighted(mSrc_16SC, 1.0, mGaussian_noise, 1.0, 0.0, mSrc_16SC);
//    mSrc_16SC.convertTo(mDst,mSrc.type());

//    return true;
//}
std::vector< uchar > buffer;
#define MAX_PACKET_SIZE 60000
unsigned char header[2];

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.fillRect(this->rect(),color2);
    p.drawImage(vRect,imgVideo,imgVideo.rect());
//    if(incomeFrame)
//    {
//        incomeFrame = false;

//        if(nightMode)
//        {
//            QImage image(frame.data, frame.cols, frame.rows, frame.step,
//                         QImage::Format_Grayscale8);
//            p.drawImage(vRect,image,image.rect());
//        }
//        else
//        {
//            QImage image(frame.data, frame.cols, frame.rows, frame.step,
//                         QImage::Format_RGB888);
//            p.drawImage(vRect,image,image.rect());

//        }
//    }
    draw_trackpoint(&p,vRect.x()+(trackpoint_x+h_correction)*vRect.width()/frame_process_W,vRect.y()+trackpoint_y*vRect.height()/frame_process_H);
    draw_sight_paint(&p,vRect.x()+(sight_x+h_correction)*vRect.width()/frame_process_W,vRect.y()+sight_y*vRect.height()/frame_process_H);

    if(mControl.joystickMode==1)
    {
        QColor color2(255, 0, 0);
        QPen pen2(color2);
        pen2.setWidth(2);
        p.setPen(pen2);
    }
    else
    {
        QColor color2(0, 255, 0);
        QPen pen2(color2);
        pen2.setWidth(5);
        p.setPen(pen2);
    }
//    p.drawRect(vRect);
    //    p.drawLine(0,0,100,100);
    DrawVideoTargets(&p);
    QColor color2(0, 255, 0);
    QPen pen2(color2);
    pen2.setWidth(2);
    p.setPen(pen2);

    QPoint point2;
    for(int i=0;i<kcf_tracker.trackmax.size();i++)
    {
        QPoint point1(plotRect.x()+i,plotRect.y()+plotRect.height()-kcf_tracker.trackmax[i]*100);
        if(i>0)p.drawLine(point1,point2);
        point2=point1;
    }

    if(0)//draw graphg
    {

         p.drawRect(plotRect);
        for(int i=0;i<dataPlot.size();i++)
        {
            QPoint point1(plotRect.x()+i*2,plotRect.y()+plotRect.height()*2-dataPlot[i]);
            if(i>0)p.drawLine(point1,point2);
            point2=point1;
        }
    }
    // draw Message
    if(msgTime){
        Qt::Alignment flags = (Qt::AlignHCenter)|(Qt::AlignVCenter);
        int alpha = msgTime/60.0*150+100;
        //        printf("alpha:%d \n",alpha);flushall();
        QColor color2(255, 255, 0,alpha);
        QPen pen2(color2);
        pen2.setWidth(2);
        p.setPen(pen2);
        p.setFont(QFont("times",20));
        p.drawText(vRect, flags, msgShown);
    }

}
void MainWindow::DrawVideoTargets(QPainter*p)
{
    for(auto &tgt :vTargetList)
    {
        if(!tgt.active)continue;
        int left = vRect.left() + (tgt.ctx - tgt.w/2)*vRect.width();
        int top = vRect.top() + (tgt.cty - tgt.h/2)*vRect.height();
        int wid = tgt.w*vRect.width();
        int hei = tgt.h*vRect.height();
        p->setPen(QPen(Qt::green,2));
        p->drawRect(left,top,wid,hei);
        p->drawText(left,top,wid,hei,0,QString::number(tgt.id));
    }
    if(selectVTargetIndex>=0)
    {
        int left = vRect.left() + (vTargetList[selectVTargetIndex].ctx - vTargetList[selectVTargetIndex].w/2)*vRect.width();
        int top = vRect.top() + (vTargetList[selectVTargetIndex].cty - vTargetList[selectVTargetIndex].h/2)*vRect.height();
        int wid = vTargetList[selectVTargetIndex].w*vRect.width();
        int hei = vTargetList[selectVTargetIndex].h*vRect.height();
        p->setPen(QPen(Qt::yellow,2));
        p->drawRect(left,top,wid,hei);
    }
}

void MainWindow::trackerShutdown()
{
    trackermode =0;
    showMessage(QString::fromUtf8("Dừng bám"));
}
int isCtActivated =false;
void MainWindow::timer30ms()
{
    if(msgTime>0)
    {
        msgTime--;
        //        update();
    }
    if(mControl.modbusDeviceCam!=nullptr)
    {

    }
    if(0)//mControl.modbusDeviceCU!=nullptr)
    {

        int ct11 = mControl.getPLCInput(0,1);
        int ct12 = mControl.getPLCInput(1,1);
        int ct21 = mControl.getPLCInput(2,1);
        int ct22 = mControl.getPLCInput(3,1);
        int ctValue = ct11+ct12*2+ct21*4+ct22*8;
        ui->radioButton_leftlimit->setChecked(ct11>0);
        ui->radioButton_rightlimit->setChecked(ct12>0);
        ui->radioButton_downlimit->setChecked(ct21>0);
        ui->radioButton_uplimit->setChecked(ct22>0);
        ui->radioButton_nolimit->setChecked(isCtActivated==0);
        if(ctValue!=isCtActivated){
            mControl.sendSetupPacket(12);
            mControl.sendSetupPacket(12);
        }
        isCtActivated = ctValue;

        int azi_int = mControl.getPLCInput(4,1);

        double azi_float = (azi_int/1000.0*360.0)*CConfig::getDouble("scale_azi",0.5)+CConfig::getDouble("scale_azi_abs",180);
        while (azi_float>=180)azi_float-=360;
        while (azi_float<=-180)azi_float+=360;
        ui->view_azi->setValue(azi_float);

        //ele cal
        int ele_int = mControl.getPLCInput(5,1);
        double ele_float = ele_int/1000.0*360.0*CConfig::getDouble("scale_ele",0.5)+CConfig::getDouble("scale_ele_abs",7);
        while (ele_float>=180)ele_float-=360;
        while (ele_float<=-180)ele_float+=360;
        //        ui->statusbar->showMessage(QString::number(ele_int));
//        ui->label_ele->setText(QString::number(ele_float,'f',1));
        ui->slider_ele->setValue(int(ele_float));
        if(isCtActivated)
        {
            trackerShutdown();
        }
        ui->label_plc2->setText("CU "+QString::number(mControl.modbusCount));
        ui->label_plc_1->setText("CAM " +QString::number(int(mControl.modbusCountCam)));
    }
    else
    {

        ui->label_plc2->setText("Mất kết nối");

    }
    if((trackermode==1)&&(singleTrackTarget.width>10)&&(singleTrackTarget.height>10))
    {
        //todo: send command
        //(singleTrackTarget.x+singleTrackTarget.width/2)

        trackxo = trackx;
        trackx = (singleTrackTarget.x+singleTrackTarget.width/2.0-trackpoint_x-h_correction)/frame_process_W;
        if(abs(trackx)<0.1)trackxi += trackx;
        //        if(trackxi>frame_process_W/2)trackxi = frame_process_W/2;
        //        if(trackxi<-frame_process_W/2)trackxi = -frame_process_W/2;
        double xcontrol = track_p*trackx+track_i*trackxi+track_d*(trackx-trackxo);
        xcontrol*=1.7;


        trackyo=tracky;
        tracky = -(singleTrackTarget.y+singleTrackTarget.height/2.0-trackpoint_y)/frame_process_H;
        if(abs(tracky)<0.1)trackyi += tracky;
        double ycontrol = track_p*tracky+track_i*trackyi+track_d*(tracky-trackyo);
        ycontrol*=trackHratio;
        if(mControl.stabMode)
        {
            ycontrol/=5.0;
            xcontrol/=5.0;

        }
        if(xcontrol>0.9)xcontrol=0.9;
        if(xcontrol<-0.9)xcontrol=-0.9;
        if(ycontrol>0.9)ycontrol=0.9;
        if(ycontrol<-0.9)ycontrol=-0.9;
        mControl.outputPelco(xcontrol*255.0,ycontrol*255.0);

    }
    else if(mControl.joystickMode==0){
        if(!this->hasFocus())
        {
            key_ad = 0;

            key_ws = 0;
        }

        //        h_speed_control += (key_ad*255-h_speed_control)/5;
        //        v_speed_control += (key_ws*255-v_speed_control)/5;
        h_speed_control = key_ad*250;
        v_speed_control = key_ws*150;
        mControl.outputPelco(h_speed_control,v_speed_control);

    }
    else if(mControl.joystickMode==2){
        if(usbDevMode==1){
            UsbDevice::readDataFromDevice(usbDevHandle, usbBuf, msgLen, &msgLen, NULL);

            double  hvalue = ((usbBuf[1]+usbBuf[2]*256)-511.0)/400.0;
            double vvalue = ((usbBuf[3]+usbBuf[4]*256)-511.0)/400.0;
            if(hvalue>1.0)hvalue=1.0;
            if(hvalue<-1.0)hvalue = -1.0;
            if(vvalue>1.0)vvalue=1.0;
            if(vvalue<-1.0)vvalue = -1.0;
            //        h_speed_control += (key_ad*255-h_speed_control)/5;
            //        v_speed_control += (key_ws*255-v_speed_control)/5;
            h_speed_control = -hvalue*255;
            v_speed_control = vvalue*255+5;
            int zeroZone = 12;
            if(h_speed_control>zeroZone)h_speed_control-=zeroZone;
            else if(h_speed_control<-zeroZone)h_speed_control+=zeroZone;
            else h_speed_control=0;
            if(v_speed_control>zeroZone)v_speed_control-=zeroZone;
            else if(v_speed_control<-zeroZone)v_speed_control+=zeroZone;
            else v_speed_control=0;
            if(trackermode==1)
            {
                trackpoint_x+=h_speed_control/30;
                trackpoint_y-=v_speed_control/30;
                if(trackpoint_x<(sight_x+h_correction)-150)trackpoint_x = (sight_x+h_correction)-150;
                if(trackpoint_x>(sight_x+h_correction)+150)trackpoint_x = (sight_x+h_correction)+150;
                if(trackpoint_y<sight_y-150)trackpoint_y = sight_y-150;
                if(trackpoint_y>sight_y+150)trackpoint_y = sight_y+150;

            }
            else mControl.outputPelco(h_speed_control,v_speed_control);
        }
        else if(usbDevMode==2){
            if(trackermode)
                UsbDevice::readDataFromDevice(usbDevHandle, usbBuf, msgLen, &msgLen, NULL);
            double  vvalue = -(usbBuf[2])*2+255;
            double  hvalue = (usbBuf[3])*2-255;
            int zeroZone = 2;
            if(h_speed_control>zeroZone)h_speed_control-=zeroZone;
            else if(h_speed_control<-zeroZone)h_speed_control+=zeroZone;
            else h_speed_control=0;
            if(v_speed_control>zeroZone)v_speed_control-=zeroZone;
            else if(v_speed_control<-zeroZone)v_speed_control+=zeroZone;
            else v_speed_control=0;
            //            printf("1:%d,2:%d,3:%d,4:%d,%d,%d,%d,%d\n",usbBuf[5],usbBuf[6],usbBuf[7],usbBuf[8]);
            //            flushall();
            //            showMessage(QString::number(hvalue));
            //        ui->label_track_y->setText(QString::number(vvalue));
            mControl.outputPelco(hvalue,vvalue);
        }
    }


    ui->label_track_x->setText(QString::number(mControl.mPan));
    ui->label_track_y->setText(QString::number(mControl.mTil));


}
void MainWindow::updateData()
{

    CaptureVideoCamera();
    if(mControl.getIsSerialAvailable())
    {
        QByteArray ba = mControl.getSerialData();
        if(ba.size())processDatagram(ba);
    }

    while(socket->hasPendingDatagrams())
    {
        int len = socket->pendingDatagramSize();
        QHostAddress host;
        quint16 port;
        QByteArray data;
        data.resize(len);

        socket->readDatagram(data.data(),len,&host,&port);
        if(len==2){//ping msg
            int byte = (unsigned char)data.at(0);
            int stimCon = (unsigned char)data.at(1);
            int gyro1 = stimCon&0x03;
            int gyro2 = (stimCon&0x0c)>>2;
            int gyro3 = (stimCon&0x30)>>4;
            int a = mControl.lastPing;
            int b = mControl.lastPing>>8;
            int c = mControl.lastPing>>16;
            int d = mControl.lastPing>>24;
            int res = (unsigned char)((a*b)+(c*d));
            if(byte==(res))
            {
                int curTime = clock();
                int pingtime = curTime-mControl.lastPing;
                ui->label_cu_connection->setText(QString::number(pingtime));
                ui->label_stim_stat->setText(QString::number(gyro1)+"-"+QString::number(gyro2)+"-"+QString::number(gyro3));
            }
        }
        if(port==4002)//joystick port
        {
            //            mControl.send(data);
            mControl.joystickInput(data);
            continue;
        }
        else if(port==4001)//CU port
        {
            processDatagram(data);
        }
        else if(port==4003)//Cam port
        {
            processDatagramLaser(data);
        }
        else
            processDetectorData(data);

    }
    while(videoSocket->hasPendingDatagrams())
    {

        int len = videoSocket->pendingDatagramSize();
        QHostAddress host;
        quint16 port;
        QByteArray data;
        data.resize(len);

        videoSocket->readDatagram(data.data(),len,&host,&port);
        int newFrameID = (uchar)data.at(1);
        data.remove(0,2);
        if(newFrameID!=frameID)//new frame
        {

//            printf("Data:%d,%d\n",newFrameID,videoBuff.length());
            frame = cv::imdecode(cv::Mat(1, videoBuff.length(), CV_8UC1, videoBuff.data()), CV_LOAD_IMAGE_UNCHANGED);
            if(!frame.empty())
            {

                frameCount++;
                if(recorder.isOpened())
                    recorder.write(frame);
                //        if(isEqualizeHis)cv::equalizeHist(frame,frame);
                update();
                //        sendFrameVideo();
                if(trackermode)
                {
                    //            printf("track update start\n"); flushall();
                    singleTrackTarget = kcf_tracker.Update(frame);
                    singleTrackWindow = kcf_tracker.getsearchingRect();
                    //            printf("track update done\n");
                    //            flushall();
                    bool trackFail = (singleTrackTarget.area()<100)||(singleTrackTarget.width<5)||(singleTrackTarget.height<5);
                    if(trackFail)
                    {

                        showMessage(QString::fromUtf8("Mất bám, đang tìm kiếm..."));
                        trackermode = 2;
                    }
                    else
                    {
                        if(trackermode==2)
                        {
                            trackermode=1;
                        }
                    }
                    //            cv::Rect scaledRect;
                    //            scaledRect.x = singleTrackTarget.x /mScaleX;
                    //            scaledRect.y = singleTrackTarget.y /mScaleY;
                    //            scaledRect.width = singleTrackTarget.width /mScaleX;
                    //            scaledRect.height = singleTrackTarget.height /mScaleY;

                    if(trackermode==1)cv::rectangle(frame,singleTrackTarget,cv::Scalar(255, 0, 0),1,16 );
                    else cv::rectangle(frame,singleTrackWindow,cv::Scalar(255, 255, 0),1,16 );


                }
                else
                {
                    cv::rectangle(frame,trackrect,cv::Scalar(150, 150, 0),1,16 );
                }
            }
            {
                imgVideo = QImage (frame.data, frame.cols, frame.rows, frame.step,QImage::Format_RGB888);
//                printf("OK");
                update();
            }
            frameID=newFrameID;

            videoBuff.clear();
            videoBuff.append(data);

        }
        else videoBuff.append(data);

    }
    //    printf("update data done\n");
        _flushall();
}
void MainWindow::processDatagramLaser(QByteArray data)
{

    QStringList dataFields = QString(data).split(',');
    if(dataFields.length()>=3)
    {
        if(dataFields.at(0).contains('Z'))
        {
            dataFields[1].remove(dataFields[1].size()-1,1);
            double value =dataFields[1].toDouble();
            double fov = CConfig::getDouble("1xFOV",57.8)/value;
            ui->slider_fov->setValue(int(fov*10.0));
            ui->label_fov->setText(QString::number(fov,'f',1));
            viewFov = fov;
            mControl.setFOV(viewFov);
        }
        else
        {
            int range = int(dataFields[1].toDouble());
            sight_range = range;
            ui->label_range->setText(QString::number(sight_range,'f',1));
            ui->slider_range->setValue(sight_range/50);
        }
    }
}
void MainWindow::processDetectorData(QByteArray data)
{
    QString stringData(data);

    QStringList datasentences =  stringData.split("$");
    for(QString sentence : datasentences)
    {
        QStringList dataFields = sentence.split(',');
        if(dataFields.size())
        {
            //            ui->checkBox_connection->toggle();

            if(sentence.contains("TGT")&&dataFields.size()>5)
            {
                ReadVideoTargets(dataFields);
            }
            else if(sentence.contains("FPS")&&dataFields.size()>1)
            {
                ReadVideoInfo(dataFields);
            }
        }
        else
        {
            //                printf("\ninvalid data:%d",dataFields.length());
            //                printf((char*)sentence.toUtf8().data());
        }
    }

}
QByteArray dataFrameBuff;

void MainWindow::processDatagram(QByteArray data)
{
    if( cuconcount <99)cuconcount ++;
    else  cuconcount = 0;
    if(mControl.getWorkMode()==0)
    {
        float scale  = 10;//CConfig::getDouble("plotScale");
        QByteArrayList datar =  data.split('\n');
        for(int i=1;i<datar.size()-1;i++)
            dataPlot.push_back(QString(datar.at(i)).toDouble()*scale);
        while(dataPlot.size()>800)dataPlot.pop_front();
    }
    if(dataFrameBuff.length()<1000)dataFrameBuff.append(data);
    else dataFrameBuff=data;
    if(!(dataFrameBuff.contains('\n')))return;
    QString stringData(dataFrameBuff);
    dataFrameBuff.clear();
    QStringList datasentences =  stringData.split("$");
    for(QString sentence : datasentences)
    {
        QStringList dataFields = sentence.split(',');

        if(dataFields.size())
        {
            if(dataFields[0].contains("TGC")&&dataFields.size()>5)
            {

                if(dataFields[0].contains("TGC")&&dataFields.size()>=10)
                {
                    ui->label_speed->setText(sentence);
                    //                    float h_user_speed = dataFields[1].toDouble();
                    //                    float v_user_speed = dataFields[2].toDouble();
                    //                    float hSpeedFeedback = dataFields[3].toDouble();
                    //                    float vSpeedFeedback = dataFields[4].toDouble();
                    //                    float stimCount = dataFields[5].toDouble();
                    //                    float sensorValue = dataFields[6].toDouble();
                    //                    float azi = dataFields[7].toDouble();
                    //                    float ele = dataFields[8].toDouble();
                    //                    float sum = dataFields[9].toDouble()+1;
                    //                    float realsum = azi+ele+ h_user_speed+v_user_speed+hSpeedFeedback+vSpeedFeedback+stimCount+sensorValue+1;
                    //                    if(abs(sum-realsum)/abs(realsum) <0.2)
                    //                    {
                    //                        ui->view_azi->setValue(azi);
                    //                        ui->slider_ele->setValue(ele);
                    //                        mControl.isCuAlive = true;
                    //                    }
                    //                    else
                    //                    {
                    //                        continue;
                    //                    }
                }
            }
            else if(dataFields[0].contains("MSGS")&&dataFields.size()>=5)
            {
                mControl.isCuAlive = true;
                this->statusBar()->showMessage(sentence);
                QStringList azistr = dataFields[2].split(':');
                if(azistr.length()==2)
                {
                    double azi = azistr[1].toDouble();
                    ui->view_azi->setValue(azi);

                }
                azistr = dataFields[3].split(':');
                if(azistr.length()==2)
                {
                    double ele = azistr[1].toDouble();
                    //                    ui->slider_ele->setValue(ele);
                    //                    ui->label_ele->setText(QString::number(ele,'f',1));

                }

            }
            else if(dataFields[0].contains("MSG")&&dataFields.size()>=2)
            {
                mControl.isCuAlive = true;
                QString messages = ui->textBrowser_msg->toPlainText();

                if(messages.count('\n')>20)
                {
                    messages.append(dataFields[1]);
                    int firstLine = messages.indexOf('\n');
                    messages.remove(0,firstLine+1);
                    ui->textBrowser_msg->clear();
                    ui->textBrowser_msg->append(messages);
                }
                else {
                    ui->textBrowser_msg->append(dataFields[1]);
                }

            }
            else if(sentence.contains("TGT")&&dataFields.size()>5)
            {
                ReadVideoTargets(dataFields);
            }
            else if(sentence.contains("FPS")&&dataFields.size()>1)
            {
                ReadVideoInfo(dataFields);
            }
        }
        else
        {
            //                printf("\ninvalid data:%d",dataFields.length());
            //                printf((char*)sentence.toUtf8().data());
        }
    }

}
void MainWindow::ReadVideoInfo(QStringList data)
{
    //    double fps = data[1].toDouble();
    ui->label_video_fps_2->setText(data[1]);
}
void MainWindow::ReadVideoTargets(QStringList data)
{
    for (int i=0;i<data.size()-6;i++)
    {
        if(data[i].contains("TGT"))
        {
            VideoTarget tgt;
            tgt.mClass = data[i+1].toInt();
            tgt.id = data[i+2].toInt();
            tgt.ctx = data[i+3].toFloat();
            tgt.cty = data[i+4].toFloat();
            tgt.w = data[i+5].toFloat();
            tgt.h = data[i+6].toFloat();
            tgt.time = QDateTime::currentMSecsSinceEpoch();
            tgt.active = true;
            bool idExist=false;
            for(int i=0;i< vTargetList.size();i++)
            {
                if((vTargetList[i].id)==tgt.id)
                {
                    vTargetList[i]=tgt;
                    idExist = true;
                    break;
                }

            }
            if(!idExist)
                vTargetList.push_back(tgt);
        }

    }

}
void MainWindow::sendFrameVideo()
{

    //        AddGaussianNoise_Opencv(frame,frame2);

    cv::imencode(".jpg", frame, buffer,params);
    //        frame = frame2;
    int unsent_len = buffer.size();
    int seq_len = buffer.size()/MAX_PACKET_SIZE+1;
    //    printf("\n%d seq %d",buffer.size(),seq_len);
    header[1] = seq_len;
    header[0] = 0xff;
    socket->writeDatagram((const char*)header,2,QHostAddress("127.0.0.1"),7070);
    socket->writeDatagram((const char*)header,2,QHostAddress("192.168.0.72"),7070);
    for(int i = 0; i<seq_len-1; i++)
    {
        socket->writeDatagram((const char*)buffer.data()+i*MAX_PACKET_SIZE,MAX_PACKET_SIZE,QHostAddress("127.0.0.1"),7070);
        socket->writeDatagram((const char*)buffer.data()+i*MAX_PACKET_SIZE,MAX_PACKET_SIZE,QHostAddress("192.168.0.72"),7070);
        unsent_len-=MAX_PACKET_SIZE;
    }
    socket->writeDatagram((const char*)buffer.data()+(seq_len-1)*MAX_PACKET_SIZE,unsent_len,QHostAddress("127.0.0.1"),7070);
    socket->writeDatagram((const char*)buffer.data()+(seq_len-1)*MAX_PACKET_SIZE,unsent_len,QHostAddress("192.168.0.72"),7070);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_slider_range_valueChanged(int value)
{
    sight_range = value*50;
    ui->label_range->setText(QString::number(sight_range));

}

void MainWindow::on_bt_control_pulse_mode_clicked(bool checked)
{
    mControl.setPulseMode(int(checked)+1);
}

void MainWindow::on_bt_video_main_clicked(bool checked)
{
    //    nightMode  =false;

}

void MainWindow::on_pushButton_show_setup_clicked(bool checked)
{
    //    ui->groupBox_setup->setVisible(checked);

}

void MainWindow::on_pushButton_clear_msg_clicked()
{
    ui->textBrowser_msg->clear();
}

void MainWindow::on_bt_control_2_pulse_clicked(bool checked)
{
    mControl.setPulseMode(2);
}

void MainWindow::on_bt_control_1_pulse_clicked(bool checked)
{
    mControl.setPulseMode(1);
}

//void MainWindow::on_comboBox_currentIndexChanged(int index)
//{
//    double ifov = (ui->comboBox->itemText(index)).toDouble();
//    mControl.setFOV(ifov );
//}

void MainWindow::on_bt_send_pid_clicked()
{
    double ph= ui->textEdit_ph->toPlainText().toDouble();
    double ih= ui->textEdit_ih->toPlainText().toDouble();
    double dh= ui->textEdit_dh->toPlainText().toDouble();

    double pv= ui->textEdit_pv->toPlainText().toDouble();
    double iv= ui->textEdit_iv->toPlainText().toDouble();
    double dv= ui->textEdit_dv->toPlainText().toDouble();
    mControl.setPIDparams(ph,ih,dh,pv,iv,dv);
    CConfig::SaveToFile();
}

void MainWindow::on_bt_video_test_2_clicked()
{
    setStimstate(0);
    //    mControl.reloadConfig();

}

void MainWindow::on_bt_video_thermal_3_clicked()
{
    setStimstate(2);
}
void MainWindow::setStimstate(int value)
{
    if(value)
    {
        showMessage(QString::fromUtf8("Tự cân bằng:")+QString::number(value));
    }
    else showMessage(QString::fromUtf8("Tự cân bằng đã tắt"));
    mControl.setStimMode(value);
    mControl.reloadConfig();
}
void MainWindow::on_bt_video_main_2_clicked()
{
    setStimstate(2);
}

//void MainWindow::on_textEdit_textChanged()
//{
//    mControl.fov =  ui->textEdit->toPlainText().toDouble();
//    double ifov = (ui->comboBox->itemText(index)).toDouble();
//    mControl.setFOV(ifov );
//}

void MainWindow::on_slider_fov_valueChanged(int value)
{
    //    ui->label_fov->setText(QString::number(value/10.0));
    //    mControl.fov = value/10.0;
    //    mControl.setFOV(mControl.fov);
}

void MainWindow::on_bt_save_setting_clicked()
{
    ballistic_k = ui->textEdit_ballistic_k->toPlainText().toDouble();
    if(ballistic_k>3) ballistic_k = 3;
    if(ballistic_k<0.3)ballistic_k = 0.3;
    ballistic_k*=0.002;
}

void MainWindow::on_pushButton_play_video_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,    tr("Open record file"), NULL, tr("*.*"));
    if(!filename.size())return;
    cap = VideoCapture(filename.toStdString().data());
    camAvailable = true;
}

void MainWindow::on_pushButton_power_off_clicked()
{
    camAvailable = false;
}

void MainWindow::on_bt_control_1_pulse_clicked()
{
    mControl.setPulseMode(1);
}

void MainWindow::on_bt_control_2_pulse_clicked()
{
    mControl.setPulseMode(2);
}


void MainWindow::on_bt_send_pid_2_clicked()
{
    //    float gearv = ui->textEdit_gearv->toPlainText().toDouble();
    //    float gearh = ui->textEdit_gearh->toPlainText().toDouble();
    //    int pprv = ui->textEdit_pprv->toPlainText().toDouble()*gearv;
    //    int pprh = ui->textEdit_pprh->toPlainText().toDouble()*gearh;
    //    mControl.setPPR(pprh,pprv);
}

void MainWindow::on_bt_save_setting_2_clicked()
{
    float maxAcc = ui->textEdit_acc->toPlainText().toDouble();
    mControl.setACC(maxAcc);
}

//void MainWindow::on_bt_zero_set_clicked()
//{
//    mControl.setAbsPos(0,0);
//}

//void MainWindow::on_bt_joystick_clicked(bool checked)
//{
//    if(!checked)
//    {

//        mControl.joystickMode = false;

//    }else
//    {

//        mControl.joystickMode = true;
//    }
//}

void MainWindow::on_bt_send_pid_track_clicked()
{
    track_p = ui->textEdit_p_track->toPlainText().toDouble();
    track_i = ui->textEdit_i_track->toPlainText().toDouble();
    track_d = ui->textEdit_d_track->toPlainText().toDouble();
}

void MainWindow::on_pushButton_record_clicked(bool checked)
{

    if(checked)
    {

        QDateTime now = QDateTime::currentDateTime();
        QString filename = now.toString("dd.MM_hh.mm.ss");
        filename = "D:/rec_"+filename+".avi";
        if(recorder.open(filename.toStdString() , CV_FOURCC('M','J','P','G'), 25,cv::Size(frame.cols,frame.rows),true))
            showMessage(QString::fromUtf8("Bắt đầu ghi lưu"));
        else showMessage(QString::fromUtf8("Lỗi ghi lưu"));
        //        ui->label_record_file_name->setText(filename);
        //        rda_main.processing->startRecord("D:/rec_"+filename+".avi");
    }
    else
    {
        //        rda_main.processing->stopRecord();
        recorder.release();
        showMessage(QString::fromUtf8("Dừng ghi lưu"));
    }
}

void MainWindow::on_pushButton_show_setup_clicked()
{
    DialogConfig *dlg= new DialogConfig();
    dlg->setModal(false);
    dlg->showNormal();
    connect(dlg, SIGNAL(accepted()), this, SLOT(reloadConfigParams()));
}

void MainWindow::on_bt_video_thermal_clicked(bool checked)
{

}

void MainWindow::on_pushButton_load_setup_clicked()
{
    reloadConfigParams();
}

void MainWindow::on_pushButton_load_setup_2_clicked()
{
    mControl.sendSetupPacket(3);

    mControl.sendSetupPacket(4);
    mControl.sendSetupPacket(5);
}

void MainWindow::on_bt_zero_set_2_clicked()
{
    mControl.setAbsPos(0,0);
}

void MainWindow::on_slider_fov_sliderReleased()
{
    int value = ui->slider_fov->value();
    ui->label_fov->setText(QString::number(value/10.0,'f',1));
    viewFov = value/10.0;
    mControl.setFOV(viewFov);
}

void MainWindow::on_bt_video_test_2_clicked(bool checked)
{

}

void MainWindow::on_bt_video_his_equal_clicked(bool checked)
{
    isEqualizeHis = checked;
}

void MainWindow::on_connectButton_clicked()
{
    mControl.modbusInit();
}

void MainWindow::on_bt_control_file_2_clicked()
{

}

void MainWindow::on_bt_control_file_2_pressed()//zoom + button
{
    mControl.setplc(0,1);
}

void MainWindow::on_bt_control_file_2_released()
{
    mControl.setplc(0,0);
}

void MainWindow::on_bt_control_file_3_pressed()
{
    mControl.setplc(1,1);
}

void MainWindow::on_bt_control_file_3_released()
{
    mControl.setplc(1,0);
}

void MainWindow::on_bt_zero_set_3_pressed()
{

}

void MainWindow::on_bt_zero_set_3_clicked(bool checked)
{
    if(checked)mControl.joystickMode = 1;
}

void MainWindow::on_bt_control_file_4_pressed()
{
    mControl.setplc(2,1);
}

void MainWindow::on_bt_control_file_4_released()
{
    mControl.setplc(2,0);
}

void MainWindow::on_bt_control_file_5_pressed()
{
    mControl.setplc(3,1);
}

void MainWindow::on_bt_control_file_5_released()
{
    mControl.setplc(3,0);
}

void MainWindow::on_bt_control_file_7_pressed()
{
    mControl.setplc(4,1);
}

void MainWindow::on_bt_control_file_7_released()
{
    mControl.setplc(4,0);
}


void MainWindow::on_bt_video_thermal_pressed()
{

}

void MainWindow::on_bt_video_thermal_released()
{

}

void MainWindow::on_bt_video_main_pressed()
{

}

void MainWindow::on_bt_video_main_released()
{

}

void MainWindow::on_bt_control_file_2_clicked(bool checked)
{

}

void MainWindow::on_pushButton_show_setup_pressed()
{

}

void MainWindow::on_bt_control_file_6_pressed()
{

}

void MainWindow::on_bt_control_focusauto_pressed()
{

}

void MainWindow::on_bt_control_focusauto_released()
{

}

void MainWindow::on_bt_control_kv_pressed()
{

}

void MainWindow::on_bt_control_kv_released()
{

}

void MainWindow::on_bt_control_kv_clicked(bool checked)
{
    mControl.setplc(6,checked);
}

void MainWindow::on_bt_control_focusauto_clicked(bool checked)
{
    mControl.setplc(5,checked);
}

void MainWindow::on_radioButton_uplimit_toggled(bool checked)
{
    if(checked)ui->groupBox_angle_limit->setStyleSheet("background-color: rgb(128, 64, 32); color:rgb(255, 255, 255)");
}

void MainWindow::on_radioButton_downlimit_toggled(bool checked)
{
    if(checked)ui->groupBox_angle_limit->setStyleSheet("background-color: rgb(128, 64, 32); color:rgb(255, 255, 255)");
}

void MainWindow::on_radioButton_leftlimit_toggled(bool checked)
{
    if(checked)ui->groupBox_angle_limit->setStyleSheet("background-color: rgb(128, 64, 32); color:rgb(255, 255, 255)");
}

void MainWindow::on_radioButton_rightlimit_toggled(bool checked)
{
    if(checked)ui->groupBox_angle_limit->setStyleSheet("background-color: rgb(128, 64, 32); color:rgb(255, 255, 255)");
}

void MainWindow::on_radioButton_nolimit_toggled(bool checked)
{
    if(checked)ui->groupBox_angle_limit->setStyleSheet("background-color: rgb(32, 64, 128); color:rgb(255, 255, 255)");
}

void MainWindow::on_bt_video_thermal_toggled(bool checked)
{
    //    //    nightMode = true;
    //        mControl.setplc(9,(!checked));
    //        Sleep(2000);


}

void MainWindow::on_bt_video_main_toggled(bool checked)
{
    //    mControl.setplc(8,(!checked));
    //    Sleep(2000);


}

void MainWindow::on_bt_video_off_toggled(bool checked)
{

}

void MainWindow::on_bt_tracksizeup_clicked()
{
    if(trackSize<90)trackSize+=10;
    CConfig::setValue("trackSize",trackSize);
    trackrect.x = (sight_x+h_correction)-trackSize/2;
    trackrect.y = sight_y-trackSize/1.25/2;
    trackrect.width = trackSize;
    trackrect.height = trackSize/1.25;
}

void MainWindow::on_bt_tracksizeup_2_clicked()
{
    if(trackSize>30)trackSize-=10;
    CConfig::setValue("trackSize",trackSize);
    trackrect.x = (sight_x+h_correction)-trackSize/2;
    trackrect.y = sight_y-trackSize/1.25/2;
    trackrect.width = trackSize;
    trackrect.height = trackSize/1.25;
}

void MainWindow::on_pushButton_sightup_clicked()
{


}

void MainWindow::on_pushButton_sight_right_clicked()
{
    sight_y = sight_y+1;
    CConfig::setValue("sighty",sight_y-frame_process_H/2.0);
}

void MainWindow::on_bt_control_usb_toggled(bool checked)
{
    if(checked){
        mControl.joystickMode = 2;
        usbInit();
    }
}

void MainWindow::on_bt_control_usb_2_toggled(bool checked)
{
    if(checked)mControl.joystickMode = 0;
}

void MainWindow::on_bt_stab_2_clicked()
{
    setStimstate(2);
}

void MainWindow::on_bt_f_1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    if(true)
    {
        mControl.setplc(8,0);
//        ui->bt_video_thermal->setDisabled(true);
        ui->bt_video_off->setChecked(false);

    }

    mControl.setplc(9,true);
}

void MainWindow::on_bt_f_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    if(true)
    {


        mControl.setplc(9,0);
        ui->bt_video_main->setDisabled(true);
        ui->bt_video_off->setChecked(false);

    }

    mControl.setplc(8,true);
}

void MainWindow::on_bt_f_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_bt_f_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_bt_f_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_bt_f_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_bt_video_thermal_clicked()
{

}

void MainWindow::on_bt_f_2_clicked(bool checked)
{

}

void MainWindow::on_bt_f_1_clicked(bool checked)
{

}

void MainWindow::on_bt_control_focusauto_2_clicked(bool checked)
{
    if(checked){
        mControl.setplc(9,0);
        mControl.setplc(8,0);
        ui->bt_video_main->setChecked(!checked);
//        ui->bt_video_thermal->setChecked(!checked);
        ui->bt_video_main->setDisabled(false);
//        ui->bt_video_thermal->setDisabled(false);
    }
}

void MainWindow::on_toolButton_sightup_clicked()
{
    if(sight_y>-200)sight_y = sight_y-1;
    CConfig::setValue("sighty",sight_y-frame_process_H/2.0);

}
