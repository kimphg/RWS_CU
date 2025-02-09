#ifndef GIMBAL_CONTROLLER_H
#define GIMBAL_CONTROLLER_H
#include "kalmano.h"
#include "sens_hbk.h"
#include "sens_motus.h"
#include "mti.h"

// Kalman kalmanGyroV(0.3, 0.6, 100, 0);
//float resultArray[2000];
//int resultArrayId=0;
#define CTRL_DATA_BUF_LEN 50
#define CONTROL_DELAY_FILTER
#define MOTOR_PULSE_CLOCK 1000000
#define PD1 9
#define PS1 10
#define PD2 11
#define PS2 12
#define CT1 5
#define HISTORY_LENGTH 100
// float stim_z_history[HISTORY_LENGTH];
// int stim_z_history_index = 0;
// void addZhistory(float input)
// {
//   if(stim_z_history_index>=HISTORY_LENGTH)stim_z_history_index=0;
//       stim_z_history[stim_z_history_index] = input;
//       stim_z_history_index++;
// }
// float getZhistory(int delay)
// {
//   int index = stim_z_history_index-delay;
//   if(index<0)index = HISTORY_LENGTH+index;
//   return stim_z_history[index];

// }

#define CT2 4
#define CT3 3
#define CT4 2
// pps of kinco motor should be set to 10000
#define PPR1 10000
#define GEAR1 200
#define PPR2 10000
#define GEAR2 150
#define STAB_TRANSFER_TIME 2000.0
#define CONTROL_TIME_STAMP 0.002

// float MAX_ACC = 5;
// float MAX_ACC_H = 1;
// #include "stim.h"
//#include "ModbusRtu.h"
//#define MODBUS_PORT Serial1
//Modbus mbMaster(0,MODBUS_PORT,0);
//modbus_t telegram[2];
// int modbus_idle_t = 100;
// unsigned long u32wait;
//uint16_t au16data[16];
//uint16_t output16data[16];
// uint8_t u8state = 0; //!< machine state
// uint8_t u8query = 0; //!< pointer to message query



//void modbusSetup()
//{
//    // telegram 0: read registers
//    telegram[0].u8id = 1; // slave address
//    telegram[0].u8fct = MB_FC_READ_REGISTERS; // function code (this one is registers read)
//    telegram[0].u16RegAdd = 0; // start address in slave
//    telegram[0].u16CoilsNo = 16; // number of elements (coils or registers) to read
//    telegram[0].au16reg = au16data; // pointer to a memory array in the Arduino
//    // telegram 1: write a single register
//    telegram[1].u8id = 1; // slave address
//    telegram[1].u8fct = MB_FC_WRITE_MULTIPLE_REGISTERS; // function code (this one is write a single register)
//    telegram[1].u16RegAdd = 16; // start address in slave
//    telegram[1].u16CoilsNo = 16; // number of elements (coils or registers) to write
//    telegram[1].au16reg = output16data; // pointer to a memory array in the Arduino
//    MODBUS_PORT.begin( 38400 ); // baud-rate
//    mbMaster.start();
//    mbMaster.setTimeOut( 50 ); // if there is no answer in 50 ms, roll over
//    u32wait = millis() + 50;
//    u8state = u8query = 0;
//}



class CGimbalController {
public:
  CGimbalController() {

  }
  float param_h_p, param_v_p;
  float param_h_i, param_v_i;
  float param_h_d, param_v_d;
  float vSpeedCalib = 0, hSpeedCalib = 0;

private:
  double userAngleh = 0;
  double userAnglev = 0;
  int mStimMsgCount = 0;
  SensHBK sens2, sens3;
  IMU_driver sens1;
  //  imu;
  // IMUData imu_data;
  int mStabMode;
  int freq1 = 25, freq2 = 75;
  float vopl = 0.55;
  int h_abs_pos, v_abs_pos;
  int userAlive;
  double h_user_speed;
  double v_user_speed;
  int h_ppr, v_ppr;
  int pelco_count;
  float controlDtime = 0;
  long int lastControlTime = 0;
  //     float h_speed_pps,v_speed_pps;
  float vSpeedFeedback;
  double hSpeedFeedback;
  double oldSpeeddpsH = 0, oldSpeeddpsV = 0;
  int control_oldID;
  // int    stimCount=0,stimFailCount=0;
  // unsigned long lastStimByteTime;
  int pulseMode = 1;
  float fov;
  // int    mGyroCount1=0,mGyroCount2=0,mGyroCount3=0;// fps count for gyros

  float mUserMaxspdH;  //DPS
  float mUserMaxSpdV;  //DPS
  float maxAccH, maxAccV;
  bool isSetupChanged;  //flag important changes

  //    double sumEv=0,sumEh=0;
  int workMode = 0;
  double h_control = 0, v_control = 0;
  double targetElevation = 0, userAzi = 0;
  double currentElevation = 0;
  float v_integrate = 0;
public:
  // int stimCon = 0;
  void setCalib(double hcalib, double vcalib);
  void setParam(String param, float value);
  void setCT(int c11, int c12, int c21, int c22);
  bool isStimConnected;
  int ct11, ct12, ct21, ct22;
  String reportStat();
  String reportParam();
  void setMaxAcc(float hvalue, float vvalue);
  void setWorkmode(int mode);
  void initGimbal();
  void setPPR(unsigned int hppr, unsigned int vppr);
  // void setKalmanZ(double pn, double sn)
  // {
  //   // initKalmanZ(pn, sn);
  // }
  int getSensors();
  void controlerReport();
  void setControlSpeed(float hspeed, float vspeed);
  bool ps1, ps2;
  void motorUpdate();
  double hinteg = 0;
  double vinteg = 0;
  double h_control_old = 0;
  double v_control_old = 0;
  void UserUpdate();
  void setAbsPos(float hpos, float vpos);
  void modbusLoop();
  void readSensorData();
  void setPulseMode(int value);
  int interupt = 0;
  void setStimMode(int value);
  void setFov(float value);
private:

  double hPulseBuff;
  double vPulseBuff;
  int h_pulse_clock_counter;
  int v_pulse_clock_counter;
  int h_freq_devider = 100;
  int v_freq_devider = 100;
  int minPulsePeriodh, minPulsePeriodv;
  void outputSpeedH(double speeddps);
  void outputSpeedV(double speeddps);
  unsigned long int lastReportTime = 0;
};


#endif  // GIMBAL_CONTROLLER_H
