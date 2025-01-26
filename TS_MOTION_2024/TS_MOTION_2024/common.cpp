#include "common.h"
#include <NativeEthernet.h>
#include <NativeEthernetUdp.h>
EthernetUDP udpsocket;  //eth
  IPAddress remote1(192, 168, 0, 77);
IPAddress remote2(192, 168, 0, 192);
void sendUDP(String msg)
{
  int len = msg.length();
  char buf[len];
  msg.toCharArray(buf, len);
  // Serial.print(buf);
  udpsocket.beginPacket(remote1, 4000);
  udpsocket.write(buf, len);
  udpsocket.endPacket();
  udpsocket.beginPacket( remote2, 4000);
  udpsocket.write(buf, len);
  udpsocket.endPacket();
}
void initEthernet()
{
  Serial.println("initEthernet");

  IPAddress ip(192, 168, 0, 7);
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
  Ethernet.begin(mac,ip);  //eth
  Serial.println("Check Ethernet");
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    //    while (true) {
    //      delay(1); // do nothing, no point running without Ethernet hardware
    //    }
  }
  
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }
  else {
    Serial.println("Ethernet is connected.");
  }
  udpsocket.begin(4001);
}
int UDPAvailable()
{
    int packetSize = udpsocket.parsePacket();
    if (packetSize >= UDP_TX_PACKET_MAX_SIZE) packetSize = UDP_TX_PACKET_MAX_SIZE;
    return packetSize;
}
void readUDP( char* dataBuffer, int packetSize) {
    udpsocket.read(dataBuffer, packetSize);
    
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
void reportDebug(const char* msg)
{
//  //S_CONTROL.print("$MSG,");
//  //S_CONTROL.println(msg);
//  E_CONTROL.print("$MSG,");
//  E_CONTROL.println(msg);

  // int i=5;
  // EthReply[0]='$';
  // EthReply[1]='M';
  // EthReply[2]='S';
  // EthReply[3]='G';
  // EthReply[4]=',';
  // while(msg[i-5]!=0)
  // {
  //   EthReply[i]=msg[i-5];
  //   i++;
  // }
  // EthReply[i]='\n';
  // EthReply[i+1]=0;
  // EthReplyLen = i+1;
  
  Serial.print("$MSG,");
  Serial.println(msg);
  // int len=strlen(msg);
  // udpsocket.beginPacket(ipRemote1, 4000);
  // udpsocket.write(msg, len);
  // udpsocket.endPacket();
  // udpsocket.beginPacket(ipRemote2, 4000);
  // udpsocket.write(msg, len);
  // udpsocket.endPacket();
  // sendUDP(String(msg));
}

std::vector<String> splitString(String input,char sep)
{
  std::vector<String> tokens;
  if(input.length()<1)return tokens;
  
  int last_sep_pos=0;
  while(1)
  {
    int sep_pos = input.indexOf(sep,last_sep_pos);
    if(sep_pos<0){
      if(((int)input.length())>last_sep_pos)
      {
        String token = input.substring(last_sep_pos,input.length());
        tokens.push_back(token);
      }
      break;
    }
    String token = input.substring(last_sep_pos,sep_pos);
    last_sep_pos = sep_pos+1;
    tokens.push_back(token);
  }
  // DPRINTLN(tokens.size());
  // for(unsigned int i=0;i<tokens.size();i++)
  // {
  //   DPRINTLN(tokens[i]);
  // }
  return tokens;
}

// bool isPrintable(uint8_t ch)
// {
//     if(ch>=0x21&&ch<=0x7e)return true;
//     if(ch==0x0d||ch==0x0a)return true;
//     return false;
// }
// bool charToString(char S[], String &D)
// {
 
//  String rc(S);
//  D = rc;
 
// }
void reportDebug(const char* msg,float value)
{
//  E_CONTROL.print("$MSG,");
//  E_CONTROL.print(msg);
//  E_CONTROL.print(":");
//  E_CONTROL.println(value);
  Serial.print("$MSG,");
  Serial.print(msg);
  Serial.print(":");
  Serial.println(value);
  // int len=strlen(msg);
  // udpsocket.beginPacket(ipRemote1, 4000);
  // udpsocket.write(msg, len);
  // udpsocket.endPacket();
  // udpsocket.beginPacket(ipRemote2, 4000);
  // udpsocket.write(msg, len);
  // udpsocket.endPacket();
  // sendUDP(String(msg));
  //  int i=5;
  // EthReply[0]='$';
  // EthReply[1]='M';
  // EthReply[2]='S';
  // EthReply[3]='G';
  // EthReply[4]=',';
  // while(msg[i-5]!=0)
  // {
  //   EthReply[i]=msg[i-5];
  //   i++;
  // }
  // EthReply[i]=':';
  //   i++;
  // int num = sprintf(EthReply+i,"%f",value);
  // EthReply[i+num]='\n';
  // EthReply[i+num+1]=0;
  // EthReplyLen = i+num+1;
}
void reportDebug(int value,int value2)
{

//	E_CONTROL.write(value);
//  E_CONTROL.write(value2);
//	Serial.write(value);
//	S_CONTROL.write(value);
}
void mPrint(const char* msg)
{
  //S_CONTROL.print(msg);
//  if(com_mode==3)E_CONTROL.print(msg);
//  Serial.print(msg);
}
void mPrint(float msg)
{
  //S_CONTROL.print(msg);
//  if(com_mode==3)E_CONTROL.print(msg);
//  Serial.print(msg);
}
void mPrint(int msg)
{
  //S_CONTROL.print(msg);
//  if(com_mode==3)E_CONTROL.print(msg);
//  Serial.print(msg);
}
void mPrint(double msg)
{
  //S_CONTROL.print(msg);
//  if(com_mode==3)E_CONTROL.print(msg);
//  Serial.print(msg);
}

