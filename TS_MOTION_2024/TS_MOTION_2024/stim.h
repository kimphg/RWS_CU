#include "common.h"
#include "kalmano.h"
#define STIM_DG_SIZE_MAX 22
#define STIM_DG_BUFF 100
unsigned char mLastStimByte = 0;
int mStimByteIndex = 0;
unsigned char stim_input_buff[STIM_DG_BUFF];
Kalman kalmanZ(0.3,2.8,100,0); // Create the Kalman instances
void initKalmanZ(double pn,double sn)
{
  kalmanZ.initParams(pn,sn,100,0);
  }
Kalman kalmanY(0.3,1.5,100,0); // Create the Kalman instances
void initKalmanY(double pn,double sn)
{
  kalmanY.initParams(pn,sn,100,0);
  }

//Kalman kalmanY;
struct StimData{
  float x_acc,y_acc,z_acc;
  float x_rate,y_rate,z_rate;
  float x_angle,y_angle,z_angle;
  float x_kangle,y_kangle,z_kangle;
  float x_temp,y_temp,z_temp;
  float x_bias,y_bias,z_bias;
  unsigned long msgCount;
  bool alive;
} ;
int crc_fail = 0;
void resetBuf()
{
    mStimByteIndex = 0;
    return;
}
void resetStimState(StimData *stim_data)
{
stim_data->x_angle = 0;
stim_data->y_angle = 0;
stim_data->z_angle = 0;
stim_data->x_rate = 0;
stim_data->y_rate = 0;
stim_data->z_rate = 0;
stim_data->x_bias = 0.03;
stim_data->y_bias = 0.03;
stim_data->z_bias = 0.03;
//stim_data->x_anglei = 0;
//stim_data->y_anglei = 0;
//stim_data->x_anglei = 0;
stim_data->alive = false;
stim_data->msgCount = 0;
  }
uint8_t gencrc(uint8_t *data, size_t len)
{
    uint8_t crc = 0xff;
    size_t i, j;
    for (i = 0; i < len; i++) {
        crc ^= data[i];
        for (j = 0; j < 8; j++) {
            if ((crc & 0x80) != 0)
                crc = (uint8_t)((crc << 1) ^ 0x07);
            else
                crc <<= 1;
        }
    }
    return crc;
}
//unsigned long lastDGMillis = 0;
bool readStim(unsigned char databyte ,unsigned long lastDGMillis , StimData *stim_data)
{
    if(lastDGMillis>400)
    {
      mStimByteIndex = 0;
    }
    else {
      mStimByteIndex++;
      if(mStimByteIndex>=STIM_DG_BUFF)mStimByteIndex=0;
    }
    stim_input_buff[mStimByteIndex]=databyte;
    if(mStimByteIndex>=11)//possible new standart datagram
    {
      if( stim_input_buff[0]==0x90)
      {
        //check if this is a valid standart datagram
        unsigned char crc = gencrc(&(stim_input_buff[0]),11);
        unsigned char truecrc = stim_input_buff[11];
        if(crc==truecrc)//valid msg found
        {

            //read angle rate
            double x_rate1 = ( (stim_input_buff[1]<<16)+(stim_input_buff[2]<<8)+(stim_input_buff[3]) );
            if(x_rate1>0x7fffff)x_rate1-=0xFFFFFF;
            double y_rate1 = ( (stim_input_buff[4]<<16)+(stim_input_buff[5]<<8)+(stim_input_buff[6]) );
            if(y_rate1>0x7fffff)y_rate1-=0xFFFFFF;
            double z_rate1 = ( (stim_input_buff[7]<<16)+(stim_input_buff[8]<<8)+(stim_input_buff[9]) );
            if(z_rate1>0x7fffff)z_rate1-=0xFFFFFF;
            //conversion to degrees
            x_rate1/=16384.0;
            y_rate1/=16384.0;
            z_rate1/=16384.0;
//            if(abs(x_rate1)>=400||abs(z_rate1)>=400||
//              abs(y_rate1)>=400)
//              {
////                resetStimState(stim_data);
//                reportDebug("SVE",y_rate1);
//                return false;
//              }
//            Serial.println(z_rate1);
//            stim_data->x_acc = x_rate1 - stim_data->x_rate;
            
            
//            stim_data->x_anglei+=stim_data->x_angle;
            
//            double acc = (y_rate1 - stim_data->y_rate)*1000;
//            if(abs(acc)>1000)return false;
//            acc = (z_rate1 - stim_data->z_rate)*1000;
//            if(abs(acc)>1000)return false;

            if(abs(x_rate1)<500){
            stim_data->x_rate = x_rate1;
            stim_data->x_angle += (stim_data->x_rate/1000.0);
            }
            else
            {
              reportDebug("SVEx",x_rate1);
              }
//            float newval = -stim_data->y_bias;
//			      stim_data->y_acc = newval - stim_data->y_rate;
            if(abs(y_rate1)<400){
              // Serial.print(y_rate1);
              // Serial.print(',');
            			       stim_data->y_rate = kalmanY.getFilteredValue(y_rate1-stim_data->y_bias);//newval;
                        stim_data->y_angle += (stim_data->y_rate/1000.0);
//                        Serial.print(stim_data->y_rate); 
//                        Serial.print(' '); 
//                        Serial.print(1); 
//                        Serial.print(' '); 
//                        Serial.print(-1); 
//                        Serial.print('\n'); 
            }
            else
            {
              reportDebug("SVEy",y_rate1);
              }  
            if(abs(z_rate1)<500){
             
            float z_rate_old = stim_data->z_rate;
            // stim_data->z_rate = z_rate1-stim_data->z_bias;
            stim_data->z_rate = kalmanZ.getFilteredValue(z_rate1-stim_data->z_bias);
            stim_data->z_acc = stim_data->z_rate-z_rate_old;
            
            stim_data->z_angle += (stim_data->z_rate/1000.0);
            }
            else
            {
              reportDebug("SVEz",z_rate1);
              }  
//            Serial.print(60); 
//            Serial.print(' '); 
//            Serial.print(-60); 
//            Serial.print(' '); 
//            Serial.print(stim_data->z_angle); 
//            Serial.print(' '); 
//            Serial.println(stim_data->y_rate);
//            Serial.print(' ');
//            Serial.println(kalmanY.getSensorNoise());
           
            
            stim_data->msgCount++;
          if(crc_fail>0)crc_fail--;
            mStimByteIndex = 0;
            return true;
        }
        else{

          Serial.print("crc failed. ");
          Serial.print("Data:");

          for (int i=0;i<=mStimByteIndex;i++)
          {
              Serial.print(stim_input_buff[i]);
              Serial.print("\t");
          }
          Serial.print("crc:");
          Serial.println(crc);
          Serial.print(" fail count:");
          Serial.print(crc_fail);
          Serial.print(" truecrc:");
          Serial.print(truecrc);
          mStimByteIndex = 0;
          Serial.print("\n");
          if(crc_fail<=100)crc_fail++;
          if (crc_fail>20)
          {
            digitalWrite(13, HIGH);
            Serial.println("stim reset as failed msg>20");
            resetStimState(stim_data);
          }
          else
          {
            stim_data->alive = true;
            }
        }
      }
      else//first byte is not correct
      {

//          Serial.println("wrong first byte");
      }
      mStimByteIndex = 0;
    }

    return false;
}
