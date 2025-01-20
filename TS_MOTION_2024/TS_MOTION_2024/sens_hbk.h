#include <cstdint>
#ifndef sens_HBK_h
#define sens_HBK_h
#define MAX_HISTORY_SIZE 500
class SensHBK
{
private:
    unsigned char lastdatabyte=0;
    unsigned char inputBuff[100];
    int inputID=0;
    
    bool calibMode = false;
    int calibCount=0;
    float biasGyroX=0;
    int msgLen=0;
    int packetCounter=0;
    float sumGyroCalib=0;
    float gyroValueHistory[MAX_HISTORY_SIZE];
    int curHistoryindex=0;
public:
  int getfps(float period){
    if((period<0.01))return 0;
    float fps = packetCounter/period;
    packetCounter=0;
    return fps;
  }
  float gyroValue=0;
    SensHBK()
    {

    }
    float getDelayedValue(int milisec)
    {
        if(milisec>=MAX_HISTORY_SIZE)return 0;
        int hisID = curHistoryindex-milisec;
        if(hisID<0)hisID+=MAX_HISTORY_SIZE;
        return gyroValueHistory[hisID];
    }
    void add2History(float value)
    {
        gyroValueHistory[curHistoryindex]=value;
        curHistoryindex++;
        if(curHistoryindex>=MAX_HISTORY_SIZE)curHistoryindex=0;
    }
    float bytesToFloat(unsigned char  b0, unsigned char  b1, unsigned char b2, unsigned char  b3)
    {
        float output;

        *((unsigned char*)(&output) + 3) = b0;
        *((unsigned char*)(&output) + 2) = b1;
        *((unsigned char*)(&output) + 1) = b2;
        *((unsigned char*)(&output) + 0) = b3;

        return output;
    }
    uint16_t fletcher_checksum(const uint8_t* packet, int packet_length)
    {
        // Checksum covers from the first header byte to the last payload byte.
        // This should be equal to the payload length plus the 4 header bytes.
        const int checksum_length = packet_length - 2;
        
        uint8_t checksum_MSB = 0;
        uint8_t checksum_LSB = 0;
        
        // Iterate over the packet to compute the checksum.
        for(int i=0; i<checksum_length; i++)
        {
            // Serial.print(packet[i],HEX);
            checksum_MSB += packet[i];
            checksum_LSB += checksum_MSB;
        }
        // Serial.print((checksum_MSB),HEX);
            // Serial.print(checksum_LSB,HEX);
        return ((uint16_t)checksum_MSB << 8) | (uint16_t)checksum_LSB;
    }
    bool input (unsigned char databyte )
    {
      bool packetOK=false;
        // Serial.print(databyte,HEX);
        // Serial.print(" ");
        if (databyte == 0x65)
        {
        if (lastdatabyte == 0x75)
        {
            inputID = 1;
            inputBuff[0] = 0x75;
            msgLen =0;
        }
        }
        // inputBuff[inputID] = databyte;
        
        
        if (inputID < 100)
        {
            inputBuff[inputID] = databyte;
            if (inputID == 3)msgLen = databyte;
        }
        else inputID=0;
        if ((inputID == 19)&&(msgLen==14)&&(inputBuff[2]==0x80))// packet len and type ok 
        {
            unsigned int cs=fletcher_checksum(inputBuff,20);//calc checksum
            unsigned int packetcs = (inputBuff[18]<<8)|inputBuff[19];//compare checksum
            if (packetcs == cs)//checksum ok
            {
                packetOK=true;
                float vs = bytesToFloat(inputBuff[6], inputBuff[7], inputBuff[8], inputBuff[9]);
                
                gyroValue = vs/3.1415926535*180.0;//convert to deg per sec
                packetCounter++;
                
                if(calibMode)
                {
                    if((gyroValue*gyroValue)<0.25)
                    {
                        sumGyroCalib += gyroValue;
                        calibCount++;
                    }
                    if (calibCount >= 20000)
                    {
                        biasGyroX =(sumGyroCalib / calibCount - biasGyroX);
                        calibCount = 0;
                        sumGyroCalib = 0;
                    }
                }
                gyroValue -= biasGyroX;

            }
        }
        inputID++;
        lastdatabyte = databyte;
        return packetOK;
    }
    
};
#endif