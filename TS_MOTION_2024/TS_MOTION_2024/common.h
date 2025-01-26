
#ifndef COMMON
#define COMMON
#define S_STIM Serial3
#define S_MT_V Serial4
#define S_MT_H Serial5
#include "Arduino.h"

void sendUDP(String msg);
float bytesToFloat(unsigned char  b0, unsigned char  b1, unsigned char b2, unsigned char  b3);
void reportDebug(const char* msg);

std::vector<String> splitString(String input,char sep);

void readSerialdata() ;
void reportDebug(const char* msg,float value);
void reportDebug(int value,int value2);
void mPrint(const char* msg);
void mPrint(float msg);
void mPrint(int msg);
void mPrint(double msg);;
void initEthernet();
int UDPAvailable();
void readUDP(char* dataBuffer, int packetSize);
#endif
