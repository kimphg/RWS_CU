#include "gimbal_controller.h"
#include "common.h"

void CGimbalController::setCalib(double hcalib, double vcalib)
{
  vSpeedCalib = vcalib;
  hSpeedCalib = hcalib;
  // stim_data.y_bias = vSpeedCalib;
  // stim_data.z_bias = hSpeedCalib;
}
int CGimbalController::getSensors() {
      return ct11 * 8 + ct12 * 4 + ct21 * 2 + ct22;
    }
void CGimbalController::setStimMode(int value)
{

  mStabMode = value;
  // stim_data.z_angle = 0;
  // stim_data.y_angle = 0;
  targetElevation = 0;
  userAzi = 0;
  hPulseBuff = 0;
  vPulseBuff = 0;
  hinteg = 0;
  vinteg = 0;
  h_control_old = 0;
  v_control_old = 0;
  interupt = STAB_TRANSFER_TIME;
  isSetupChanged = true;
  userAngleh = 0;
  userAnglev = 0;
  v_integrate = 0;

}
void CGimbalController::setWorkmode(int mode)
    {
      workMode = mode;

    }
void CGimbalController::setParam(String param,float value)
    {
      if(param.equals("vp"))
        {
          param_v_p = value;
        }
      else if(param.equals("vi"))
        {
          param_v_i = value;
        }
        else if(param.equals("vd"))
        {
          param_v_d = value;
        }
        else if(param.equals("hp"))
        {
          param_h_p = value;
        }
        else if(param.equals("hi"))
        {
          param_h_i = value;
        }
        else if(param.equals("hd"))
        {
          param_h_d = value;
        }
        else if(param.equals("vcalib"))
        {
          vSpeedCalib = value;
        }
        else if(param.equals("hcalib"))
        {
          hSpeedCalib = value;
        }
        else if(param.equals("vopl"))
        {
          vopl = value;
        }
        else if(param.equals("freq1"))
        {
          freq1 = value;
        }
        else if(param.equals("freq2"))
        {
          freq2 = value;
        }
        else if(param.equals("stab"))
        {
          mStabMode = value;
          
        }
        else if(param.equals("elev"))
        {
          targetElevation+=value;
          
        }
        else
        {
          reportDebug("Unknown param");
          
        }
        Serial.print("param set:");
        Serial.print(param);
        Serial.print("=");
        Serial.print(value);
        Serial.print('\n');
        isSetupChanged = true;
    }
String CGimbalController::reportStat()
{
  String report;
  if (getSensors())setStimMode(0);
  unsigned long int curTime=millis();
  int dt=(curTime-lastReportTime);
  
  if(dt<600)
  {
    return report;
  }
  else
  {
    lastReportTime = curTime;
    report = "MSR,";
    pelco_count = 0;
    // float gyro_fps = mGyroCount1*1000.0 / dt;
    // mGyroCount1 = 0;
    report.append("gyro1:");
    // report.append(String(sens1.getfps(1000)));
    report.append(",");
    report.append("gyro2:");
    report.append(String(sens2.getfps(1.0)));
    report.append(",");
    report.append("gyro3:");
    report.append(String(sens3.getfps(1.0)));
    report.append(",");
    report.append("gmotor:");
    report.append(String(1));
    report.append(",");
    report.append("cmotor:");
    report.append(String(1));
    report.append(",");
    report.append("res:");
    report.append(String(1));
    report.append(",");
    report.append("vlimit:");
    report.append(String(ct11+ct12*2));
    report.append(",");
    report.append("hlimit:");
    report.append(String(ct21+ct22*2));
    report.append(",");
    report.append("coil1:");
    report.append("OK");
    report.append(",");
    report.append("coil2:");
    report.append("OK");
    report.append(",");
    report.append("uptime:");
    report.append(String(curTime/1000.0));
    report.append(",");
  // Serial.println(report);
    return report;
  }
}
//   String CGimbalController::reportParam()
// {
//   String report;
  
//   {

//     report = "MSR,";
//     pelco_count = 0;
//     float gyro_fps = mGyroCount1*1000.0 / dt;
//     mGyroCount1 = 0;
//     report.append("p:");
//     report.append(String(gyro_fps));
//     report.append(",");
//     gyro_fps = mGyroCount2*1000.0 / dt;
//     mGyroCount2 = 0;
//     report.append("gyro2:");
//     report.append(String(gyro_fps));
//     report.append(",");
//     gyro_fps = mGyroCount3*1000.0 / dt;
//     mGyroCount3 = 0;
//     report.append("gyro3:");
//     report.append(String(gyro_fps));
//     report.append(",");
//     report.append("gmotor:");
//     report.append(String(1));
//     report.append(",");
//     report.append("cmotor:");
//     report.append(String(1));
//     report.append(",");
//     report.append("res:");
//     report.append(String(1));
//     report.append(",");
//     report.append("vlimit:");
//     report.append(String(ct11+ct12*2));
//     report.append(",");
//     report.append("hlimit:");
//     report.append(String(ct21+ct22*2));
//     report.append(",");
//     report.append("coil1:");
//     report.append("OK");
//     report.append(",");
//     report.append("coil2:");
//     report.append("OK");
//     report.append(",");
//     report.append("uptime:");
//     report.append(String(curTime/1000.0));
//     report.append(",");
//   // Serial.println(report);
//     return report;
//   }

//   //        controlerReport();
// }

void CGimbalController::initGimbal()
{
  // Serial2.setRX(25);
  // Serial2.setTX(24);
      
    sens1.IMU_init();
    sens1.resetYaw(0);
  isSetupChanged = true;
  maxAccH = 0.1;
  maxAccV = 0.1;
  mUserMaxspdH = 80.0; //DPS
  mUserMaxSpdV = 60.0 ; //DPS
  isStimConnected = false;
  fov = 60;
  mStabMode = 0;
  pulseMode = 1;
  h_abs_pos = 0;
  v_abs_pos = 0;
  userAlive = 1;
  param_h_p = 1.2;
  param_h_i = 2.0;
  param_h_d = -0.15;
  param_v_p = 2.0;
  param_v_i = 2.2;
  param_v_d = -0.2;
  pinMode(CT1, INPUT);
  pinMode(CT2, INPUT);
  pinMode(CT3, INPUT);
  pinMode(CT4, INPUT);

  pinMode(PD1, OUTPUT);
  pinMode(PS1, OUTPUT);
  pinMode(PD2, OUTPUT);
  pinMode(PS2, OUTPUT);
  Serial.println("Testing IO");
  // digitalWrite(PD1, HIGH);
  // delay(200);
  // digitalWrite(PS1, HIGH);
  // delay(200);
  // digitalWrite(PD2, HIGH);
  // delay(200);
  // digitalWrite(PS2, HIGH);
  // delay(500);
  // digitalWrite(PD1, LOW);
  // delay(200);
  // digitalWrite(PS1, LOW);
  // delay(200);
  // digitalWrite(PD2, LOW);
  // delay(200);
  // digitalWrite(PS2, LOW);
  // delay(200);

  Serial.println("IO test done");
  //    modbusSetup();
  workMode = 1;
  reportDebug("Firmware version: 1.23");
  h_user_speed = 0;
  v_user_speed = 0;
  setPPR(PPR1 * GEAR1, PPR2 * GEAR2);
  setMaxAcc(1, 1);
  control_oldID = 0;
  h_pulse_clock_counter = 0;
  v_pulse_clock_counter = 0;
  // resetStimState(&stim_data);
}
void CGimbalController::setAbsPos (float hpos, float vpos)
    {
      h_abs_pos = hpos / 360.0 * h_ppr;
      v_abs_pos = vpos / 360.0 * v_ppr;
    }
void CGimbalController::setMaxAcc(float hvalue, float vvalue)
    {
      maxAccH = hvalue;
      maxAccV = vvalue;
      isSetupChanged = true;
      //        reportDebug("acc",maxAccH);
    }
void CGimbalController::setPPR(unsigned int hppr, unsigned int vppr)
{
  h_ppr = hppr;
  v_ppr = vppr;
  minPulsePeriodh = 3;//MOTOR_PULSE_CLOCK/(h_ppr);
  minPulsePeriodv = 3;//MOTOR_PULSE_CLOCK/(v_ppr);

  isSetupChanged = true;
}
double eh, ev;
int timeSec = 0;
void CGimbalController::controlerReport()
{

}

void CGimbalController::setControlSpeed(float hspeed, float vspeed)
{
  pelco_count++;

  h_user_speed += 0.2 * (hspeed * mUserMaxspdH - h_user_speed);
  v_user_speed += 0.2 * (vspeed * mUserMaxSpdV - v_user_speed);

  userAlive = 0.3 / CONTROL_TIME_STAMP;
  
  
}

void CGimbalController::motorUpdate()
{
  h_pulse_clock_counter++;
  v_pulse_clock_counter++;

  if (abs(hPulseBuff) >= 1)
  {
    if (h_pulse_clock_counter > h_freq_devider)
    {
      h_pulse_clock_counter = 0;
      if (pulseMode == 1)
      {
        ps1 = !ps1;
        digitalWriteFast(PS1, ps1);
        
      }
      else if (pulseMode == 2)
      {
        if (hPulseBuff < 0) {
          if (int(hPulseBuff) % 2)digitalWriteFast(PS1, HIGH);
          else digitalWriteFast(PS1, LOW);
          digitalWriteFast(PD1, HIGH);
        }
        else {
          if (int(hPulseBuff) % 2)digitalWriteFast(PD1, HIGH);
          else digitalWriteFast(PD1, LOW);
          digitalWriteFast(PS1, HIGH);
        }
      }

    }
  }
  //vPulse;
  if (abs(vPulseBuff) >= 1)
  {
    if (v_pulse_clock_counter > v_freq_devider)
    {
      v_pulse_clock_counter = 0;
      if(vPulseBuff<0)currentElevation-=360.0/v_ppr;
      else currentElevation+=360.0/v_ppr;
      if (pulseMode == 1)
      {
        //                    if(vPulseBuff%2)digitalWrite(PS2,HIGH);
        //                    else digitalWrite(PS2,LOW);
        ps2 = !ps2;
        digitalWriteFast(PS2, ps2);
        
      }
      else if (pulseMode == 2)
      {
        if (vPulseBuff < 0) {
          if (int(vPulseBuff) % 2)digitalWriteFast(PS2, HIGH);
          else digitalWriteFast(PS2, LOW);
          digitalWriteFast(PD2, HIGH);
          
        }
        else {
          if (int(vPulseBuff) % 2)digitalWriteFast(PD2, HIGH);
          else digitalWriteFast(PD2, LOW);
          digitalWriteFast(PS2, HIGH);
        }
      }
    }
  }
}

float signof(float x)
{
  if(x>0)return 1;
  else return -1;
}
void CGimbalController::UserUpdate()//
{

  if (userAlive > 0)
  {
    userAlive--;
  }
  else
  {
    h_user_speed *= 0.6;
    v_user_speed *= 0.6;
  }

  if (interupt > 0)interupt--;
  if (mStabMode == 0)
  {
    float v_control_angle = (targetElevation -currentElevation)  * 60 ;
    float outputv = v_control_angle*param_v_p;
    // horizontal control value
    outputSpeedH(h_user_speed);
    // vertical control value
    // Serial.println(outputv );
    outputSpeedV(outputv);
  
  }
  else if (mStabMode == 1)
  {

    // h_control = 0 - sens3.gyroValue * param_h_p + (h_user_speed + sens1.gyroH* param_h_d) ;
    // h_control*=1.5;
    userAzi += h_user_speed * CONTROL_TIME_STAMP / 12.0;
    double h_control_i = 0;// (userAzi + sens1.angleH /3.0) * param_h_i* 60 ;
    outputSpeedH(h_control + h_control_i);
    //v control calculation    22
    //  Serial.print(' ');
    //  Serial.print(stim_data.z_rate);
    //  Serial.print(' ');
    //  Serial.println(stim_data.y_rate);
    // float zrate = sens2.gyroValue;//+getZhistory(freq1)*0.7+getZhistory(freq2)*0.3;
    // float v_control_d = (v_user_speed+zrate)*param_v_d ;
    // if(v_control_d>0.1)v_control_d=0.1;
    // if(v_control_d<-0.1)v_control_d=-0.1;
    // targetElevation += (v_user_speed) * CONTROL_TIME_STAMP / 12.0;
    //sens1
    float v_control_angle = (targetElevation-currentElevation- sens2.rollAngle   )  * 60 ;
    v_integrate += v_control_angle/60.0;
    // float outputv = 0 - sens2.gyroValue * vopl +v_control_angle*param_v_p + v_integrate*param_v_i+ v_control_d ;
    float outputv = v_control_angle*param_v_p ;
    Serial.print(sens2.rollAngle );
    Serial.print(" " );
    Serial.print(v_control_angle);
    Serial.print(" " );
    Serial.println(outputv );
    outputSpeedV(outputv);

// Serial.print(stim_data.z_rate );
//        Serial.print(',');
//      Serial.print(zrate );
//        Serial.print(',');
//        Serial.print(v_control_angle*param_v_p);
//        Serial.print(',');
//        Serial.print(v_integrate*param_v_i);
//        Serial.print(',');
//        Serial.print(v_control_d);
//        Serial.print(',');
//        Serial.print( outputv );
//        Serial.print(',');
//        Serial.println(stim_data.z_angle  );

  }
  //    modbusLoop();



}

//void CGimbalController::modbusLoop() {
//    switch( u8state ) {
//    case 0:
//        if (millis() > u32wait) u8state++; // wait state
//        break;
//    case 1:
//        if(u8query==1)//send status over modbus
//        {
//            output16data[ 0] = fov*100;
//            output16data[ 1] = abs(hPulseBuff*100);
//            output16data[ 2] = abs(vPulseBuff*100);
//            output16data[ 3] = abs(stim_data.y_angle*100+18000);
//            output16data[ 4] = abs(stim_data.y_rate*100+18000);
//            output16data[13] = abs(getSensors()*100);
//            output16data[14] = controlDtime*100;
//        }
////        mbMaster.query( telegram[u8query] ); // send query (only once)
//        u8state++;
//        u8query++;
//        if (u8query >= 2) u8query = 0;
//        break;
//    default:
//        mbMaster.poll(); // check incoming messages
//        if (mbMaster.getState() == COM_IDLE) {
//            u8state = 0;
//            u32wait = millis() + modbus_idle_t;
//            //update data after modbus communication done
//            //gimbal.setCT(au16data[0],au16data[1],au16data[2],au16data[3]);
//        }
//        break;
//    }
//
//    //analogRead( 0 );
//
//}


void CGimbalController::readSensorData()//200 microseconds
{
  //      controlerReport();
  // while (S_STIM.available() > 0) {
  //   // unsigned long timeMicros = micros();
  //   // unsigned char databyte = S_STIM.read();
  //   // if (readStim(databyte, (timeMicros - lastStimByteTime), &stim_data)) // one packet per millisencond
  //   // {
  //   //   mStimMsgCount++;
  //   //   mGyroCount1++;
  //   //   addZhistory(stim_data.z_rate);
  //   //   // Serial.println(stim_data.z_rate);
  //   // }
  //   // lastStimByteTime = timeMicros;
  // }

  while (S_MT_V.available() > 0) {//FA FF 36 0F 80 40 0C 3B 8B BC 00 BB E2 4F 00 3B 4E 4A 00 AF
    sens2.input(S_MT_V.read());
  }
  while (S_MT_H.available() > 0) {//FA FF 36 0F 80 40 0C 3B 8B BC 00 BB E2 4F 00 3B 4E 4A 00 AF
    sens3.input(S_MT_H.read());
  }
  while (S_STIM.available() > 0) {//FA FF 36 0F 80 40 0C 3B 8B BC 00 BB E2 4F 00 3B 4E 4A 00 AF
    sens1.updateData(S_STIM.read());
  }
  // if(imu.updateData())
  // {
  //   imu_data = imu.getMeasurement();
  // reportDebug("imu_data",imu_data.gyroZ);
  // }

}
void CGimbalController::outputSpeedH(double speeddps)//speed in degrees per sec
{
  //if(interupt)
  {
    oldSpeeddpsH += (STAB_TRANSFER_TIME - interupt) / STAB_TRANSFER_TIME * (speeddps - oldSpeeddpsH);
    speeddps = oldSpeeddpsH;
  }
  if (ct11 > 0) {
    hPulseBuff = h_ppr / 120.0 * CONTROL_TIME_STAMP;
  }
  else if (ct12 > 0) {
    hPulseBuff = -h_ppr / 120.0 * CONTROL_TIME_STAMP;
  }
  else {
    double h_speed_pps = speeddps / 360.0 * h_ppr;
    hPulseBuff = (h_speed_pps * CONTROL_TIME_STAMP * 2.0); //
    int maxBuf = h_ppr / 4;
    if (hPulseBuff > maxBuf )hPulseBuff = maxBuf;
    if (hPulseBuff < -maxBuf)hPulseBuff = -maxBuf;
  }
  if (hPulseBuff == 0)h_freq_devider = h_ppr * 1000;
  else
  {
    h_freq_devider = CONTROL_TIME_STAMP * (float)MOTOR_PULSE_CLOCK / abs(hPulseBuff);
    if (h_freq_devider < minPulsePeriodh)h_freq_devider = minPulsePeriodh;

  }
  if (pulseMode == 1)
  {
    int dir = LOW;
    if (hPulseBuff > 0)
    {
      dir = LOW;
    }
    else
    {
      dir = HIGH;
    }

    digitalWriteFast(PD1, dir);
  }
}
void CGimbalController::outputSpeedV(double speeddps)//speed in degrees per sec
{
  //oldSpeeddpsV += 0.3*(speeddps-oldSpeeddpsV);
  //  speeddps = oldSpeeddpsV;
  //if(interupt)
  {
    oldSpeeddpsV += (STAB_TRANSFER_TIME - interupt) / STAB_TRANSFER_TIME * (speeddps - oldSpeeddpsV);
    speeddps = oldSpeeddpsV;
  }
  if (ct21 > 0) {
    vPulseBuff = v_ppr / 120.0 * CONTROL_TIME_STAMP;
  }
  else if (ct22 > 0) {
    vPulseBuff = -v_ppr / 120.0 * CONTROL_TIME_STAMP;
  }
  else {
    double speed_pps = speeddps / 360.0 * v_ppr;
    vPulseBuff = (speed_pps * CONTROL_TIME_STAMP * 2.0); //
    int maxBuf = v_ppr / 4;
    if (vPulseBuff > maxBuf )vPulseBuff = maxBuf;
    if (vPulseBuff < -maxBuf)vPulseBuff = -maxBuf;
  }
  if (vPulseBuff == 0)v_freq_devider = v_ppr * 1000;
  else
  {
    v_freq_devider = CONTROL_TIME_STAMP * (float)MOTOR_PULSE_CLOCK / abs(vPulseBuff);
    if (v_freq_devider < minPulsePeriodv)v_freq_devider = minPulsePeriodv;
  }
  if (pulseMode == 1)
  {
    int dir = LOW;
    if (vPulseBuff > 0)
    {
      dir = LOW;
    }
    else
    {
      dir = HIGH;
    }
    digitalWriteFast(PD2, dir);
  }

}

void CGimbalController::setFov(float value)
{
  if (value > 0.1 && value <= 60.0)
  {
    fov = value;
    mUserMaxspdH = fov*1.8;
    mUserMaxSpdV = fov*1.4;
    //        reportDebug("fov changed");
    //        reportDebug(fov);
    //        isSetupChanged =true;
  }
  else
  {
    //        reportDebug("fov invalid");
  }

}
void CGimbalController::setCT(int c11, int c12, int c21, int c22)
{
  ct11 = c11;
  ct12 = c12;
  ct21 = c21;
  ct22 = c22;

}


void CGimbalController::setPulseMode(int value)
{
  if (value > 0 && value < 3)
  {
    pulseMode = value;
    reportDebug("pulse mode changed");
    isSetupChanged = true;
  }
  else
  {
    reportDebug("pulse mode invalid");
  }
}


