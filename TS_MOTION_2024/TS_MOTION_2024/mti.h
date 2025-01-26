#include <stdint.h>
#ifndef MTI_H
#define MTI_H
#define BUF_SIZE_IMU 100
// #include "common.h"
#include "Arduino.h"


class IMU_driver {
public:
  float bytesToFloat(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3);
  float yawShift;
  float roll=0, pitch=0, yaw=0;
  float gyroX,gyroY,gyroZ;
  float accX,accY,accZ;
  int yawCalcMode ;
  int failCount = 0;
  IMU_driver();
  void IMU_init() ;
  void resetYaw(float newyaw);
  bool Connect() ;
  bool gotoMeasurement();
  inline bool isConnected() {
     return conected;
  }
  bool gotoConfig() ;
  bool updateData(uint8_t bytein) ;
  
  // inline IMUData getMeasurement() {
  //   return measurement;
  // }
  // bool isUpdated;
  int noMotionCount=0;
  float gyroZBiasCompensation;
private:
  // void sendControlPacket();
  float gyroZBias=0;
  int gyroZBiasCount;
  unsigned char databuf[BUF_SIZE_IMU];
  int buffIndex=0;
  unsigned char lastbyte;
  // IMUData measurement;
  bool conected;
  bool isMeasurement;
};
#endif