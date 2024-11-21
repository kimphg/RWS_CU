#ifndef C_GIMBAL_CONTROL_H
#define C_GIMBAL_CONTROL_H
#define PLC_REG_SIZE 32
#define PLC_BT0  0
#define PLC_BT1  1
#define PLC_BT2  2
#define PLC_BT3  3
#define PLC_BT4  4
#define PLC_BT5  5
#define PLC_BT6  6
#define PLC_BT7  7
#define PLC_BT8  8
#define PLC_BT9  9
#define PLC_BT10 10
#define PLC_BT11 11
#define PLC_BT12 12
#define PLC_BT13 13
#define PLC_BT14 14
#define PLC_BT15 15
#define PLC_BT16 16
#define PLC_BT17 17
#define PLC_BT18 18
#define PLC_BT19 19
#define PLC_BT20 20
#define PLC_SW1  21
#define PLC_SW2  22
#define PLC_SW3  23
#define PLC_SW4  24
#define PLC_SW5  25
#define PLC_SW6  26
#define PLC_SW7  27
#define PLC_SW8  28
#define PLC_SW9  29
#define PLC_SW10 30
#define PLC_SW11 31
#define PLC_SW12 32
#define PLC_SW13 33
#define PLC_SW14 34
#define PLC_SW15 35
#define PLC_SW16 36
#define PLC_SW17 37
#define PLC_SW18 38
#define PLC_SW19 39
#define PLC_SW20 40
#include <QUdpSocket>
#include <c_config.h>
#include <QModbusClient>
#include <QQueue>

class c_gimbal_control: public QObject
{
    Q_OBJECT
public:
//    QQueue<double> dataPlot;
    QModbusClient *modbusDeviceCam=nullptr;
    QModbusClient *modbusDeviceCU = nullptr;
    double fov;
    int mPan,mTil;
    int pulseMode;
    int stabMode;
    int lastPing;
    int joystickMode    = 0;
    int isCuAlive      = 0;
    int isStimAlive    = 0;
    int modbusCount = 0;
    int modbusCountCam = 0;
    bool plcValueChanged = false;
    QUdpSocket *socket;
    c_gimbal_control();
    void outputPelco(int panValue, int tiltValue);
    void setFOV(double ifov);
    void setPulseMode(int ipulseMode);
    void setSocket(QUdpSocket *psocket);
    void setPIDparams(double ph, double ih, double dh,double pv, double iv, double dv);
    void setStimMode(int value);
    void send(QByteArray data);
//    void setPPR(float pprh, float pprv);
    void setACC(float maxAcc);
    QByteArray getSerialData();
    bool getIsSerialAvailable() const;
    void reloadConfig();
    void setAbsPos(double azi, double ele);
    void joystickInput(QByteArray data);
    void sendSetupPacket(int index);
    int getBTZoom() ;

    int getBTRed() ;

    int getBTWhite() ;

    int getBTDM() ;
    void modbusInit();
    void modbusReadRequest();
    bool getPLCReg(int id);
    void setplc(int addr, int value, int plci=0);
    int getPLCInput(int id, int plcid=0);
    int mBTDM =0;
    int mBTZoom =0;
    int mBTRed =0;
    int mBTWhite =0;
    void setWorkmode(int mode);
    int getWorkMode() const;

private:

    int workMode = 1;
    QByteArray serialData;
    bool isSerialAvailable;
    double abs_pos_h,abs_pos_v;
    double hCalib,vCalib;
    double param_hp ,param_hi ,param_hd ;
    double param_pprh,param_pprv;
    double param_gear_h,param_gear_v;
    double param_vp ,param_vi ,param_vd ;
    double param_acc;

    void openSerialPort();
    bool processPelco();
    bool readPelco(unsigned char databyte);


    void modbusReadRequestCam();
private slots:
    void onStateChanged(int state);
    void modbusInputReadCU();
    void modbusInputReadCam();
    void timerEvent(QTimerEvent *event);
};

#endif // C_GIMBAL_CONTROL_H
