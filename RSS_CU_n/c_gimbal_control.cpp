#include "c_gimbal_control.h"
#include <QtSerialPort/QSerialPort>
#include <QModbusTcpClient>
#include <QUrl>
#include <math.h>
#include "c_lowpass.h"
static unsigned long pelcoLastTime = 0;
static unsigned char serial_input_buff[20];
static int serial_input_id=0;
static unsigned char pelco_input_buff[7];
static QSerialPort *serial ;
//static int old_bt_red=1,old_bt_white=1;
static int plcReg[PLC_REG_SIZE];
static int plcInput[PLC_REG_SIZE];
static int plcInputCam[PLC_REG_SIZE];
static int plcout[PLC_REG_SIZE];
static c_lowpass *filterPan;//(CConfig::getDouble("control_LPF",2),0.03);
static c_lowpass *filterTilt;//(CConfig::getDouble("control_LPF",2),0.03);
bool c_gimbal_control::getPLCReg(int id)
{
    return plcReg[id];
}
int c_gimbal_control::getPLCInput(int id,int plcid)
{
    if(plcid==0)return plcInputCam[id];
    return plcInput[id];
}
bool c_gimbal_control::processPelco(){
    if(pelco_input_buff[1]==40)
    {
    }
    else
    {
        unsigned char command1 = pelco_input_buff[2];
        unsigned char command2 = pelco_input_buff[3];
        int panSpeed = (unsigned char)pelco_input_buff[4];
        if(panSpeed<5)panSpeed=0;
        else panSpeed-=5;
        int tiltSpeed = (unsigned char)pelco_input_buff[5];
        if(tiltSpeed<5)tiltSpeed=0;
        else tiltSpeed-=5;
        if((command2&0x01)==0x00&&(pelco_input_buff[1]==0x01))//standart pelco
        {
            float panDir = 1, tiltDir = 1;
            if( (command2&0x02) && (!(command2&0x04)) )//right
            {
                panDir = 1;
                //                    Serial.print("+");
            }
            else if ((command2&0x04) && (!(command2&0x02)) )//left
            {
                panDir = -1;
                //                    Serial.print("-");
            }
            if( (command2&0x08) && (!(command2&0x10)) )//up
            {
                tiltDir = 1;
                //                    Serial.print("*");
            }
            else if ((command2&0x10) && (!(command2&0x08)) )
            {
                tiltDir = -1;
                //                    Serial.print("/");
            }
            //                Serial.print(".");
            if(joystickMode==1)outputPelco(panSpeed*panDir,tiltSpeed*tiltDir);
            //        gimbal.setControlSpeed(panSpeed*panDir/255.0,tiltSpeed*tiltDir/255.0);
            //                digitalWrite(20,HIGH);
            //                S_CONTROL.print("$MSG,std Pelco,");
            //                S_CONTROL.print(panSpeed*panDir);
            //                S_CONTROL.print(",");
            //                S_CONTROL.println(tiltSpeed*tiltDir);
        }
    }
    //    else if(pelco_input_buff[1]==0x02) //control setup
    //    {
    //        gimbal.setFov( ( ( ((unsigned char)pelco_input_buff[2])<<8) + (unsigned char)pelco_input_buff[3])/65535.0*100.0);
    //        gimbal.setPulseMode(  pelco_input_buff[4]);
    //        gimbal.setStimMode(  pelco_input_buff[5]);
    //        reportDebug("FovPS set");
    //    }
    //    else if(pelco_input_buff[1]==0x03) //P setup
    //    {
    //        float ph = ( ( ((unsigned char)pelco_input_buff[2])<<8) + (unsigned char)pelco_input_buff[3])/65535.0*4.0-2.0;
    //        float pv = ( ( ((unsigned char)pelco_input_buff[4])<<8) + (unsigned char)pelco_input_buff[5])/65535.0*4.0-2.0;
    //        gimbal.setPARAM_P(ph,pv);
    //        reportDebug("P set");
    //    }
    //    else if(pelco_input_buff[1]==0x04) //I setup
    //    {
    //        float ph = ( ( ((unsigned char)pelco_input_buff[2])<<8) + (unsigned char)pelco_input_buff[3])/65535.0*4.0-2.0;
    //        float pv = ( ( ((unsigned char)pelco_input_buff[4])<<8) + (unsigned char)pelco_input_buff[5])/65535.0*4.0-2.0;
    //        gimbal.setPARAM_I(ph,pv);
    //        reportDebug("I set");
    //    }
    //    else if(pelco_input_buff[1]==0x05) //D setup
    //    {
    //        float ph = ( ( ((unsigned char)pelco_input_buff[2])<<8) + (unsigned char)pelco_input_buff[3])/65535.0*4.0-2.0;
    //        float pv = ( ( ((unsigned char)pelco_input_buff[4])<<8) + (unsigned char)pelco_input_buff[5])/65535.0*4.0-2.0;
    //        gimbal.setPARAM_D(ph,pv);
    //        reportDebug("D set");
    //    }
    //    else if(pelco_input_buff[1]==0x06) //PPR setup
    //    {
    //        unsigned int hppr = ( ( ((unsigned char)pelco_input_buff[2])<<8) + (unsigned char)pelco_input_buff[3])*100;
    //        unsigned int vppr = ( ( ((unsigned char)pelco_input_buff[4])<<8) + (unsigned char)pelco_input_buff[5])*100;
    //        gimbal.setPPR(hppr,vppr);
    //        reportDebug("PPR set");
    //    }
    //    else if(pelco_input_buff[1]==0x07) //max acceleration set
    //    {
    //        float hacc = ( ( ((unsigned char)pelco_input_buff[2])<<8) + (unsigned char)pelco_input_buff[3])*0.001;
    //        float vacc = ( ( ((unsigned char)pelco_input_buff[4])<<8) + (unsigned char)pelco_input_buff[5])*0.001;
    //        gimbal.setMaxAcc(hacc,vacc);
    //        reportDebug("acc set");
    //    }
    //    else {
    //        reportDebug("msge");
    //        return false;
    //    }
    return true;
}
bool c_gimbal_control::readPelco(unsigned char databyte)
{
    serial_input_id++;if(serial_input_id>=20)serial_input_id=0;
    serial_input_buff[serial_input_id] = databyte;
    int id = serial_input_id-6;
    if(id<0)id+=20;
    if(serial_input_buff[id]==0xff)
    {
        unsigned char checkSum =0;
        for(int k = 1;k<6;k++)
        {
            int id = serial_input_id-k;
            if(id<0)id+=20;
            checkSum+=(unsigned char)( serial_input_buff[id]);
        }
        if(checkSum==databyte)
        {

            //packet confirmed
            //copy data to buff
            for(int k = 1;k<7;k++)
            {
                id = serial_input_id-k;
                if(id<0)id+=20;
                pelco_input_buff[6-k] =  serial_input_buff[id];

            }
            return processPelco();
            //            reportDebug("1");
        }
        //        else reportDebug("0");
    }
    return false;
}
static unsigned char com2[]        ={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static unsigned char packet[]      ={0xFF,0x01,0x00,0x00,0x00,0x00,0x00};
static unsigned char packet2[]     ={0xFF,0x02,0x00,0x00,0x00,0x00,0x00};
QHostAddress dstAddr1 =  QHostAddress("192.168.0.254");
QHostAddress dstAddr2 =  QHostAddress("192.168.0.7");
int remotePort = 4001;
int c_gimbal_control::getBTZoom()
{
    return mBTZoom;
}

int c_gimbal_control::getBTRed()
{
    if(mBTRed)
    {
        mBTRed = 0;
        return 1;
    }
    else return 0;
}

int c_gimbal_control::getBTWhite()
{
    if(mBTWhite)
    {
        mBTWhite = 0;
        return 1;
    }
    else return 0;
}

int c_gimbal_control::getBTDM()
{
    return mBTDM;
}

c_gimbal_control::c_gimbal_control()
{
    filterPan = new c_lowpass(CConfig::getDouble("control_LPF",2),0.03);
    filterTilt= new c_lowpass(CConfig::getDouble("control_LPF",2),0.03);
    param_hp = CConfig::getDouble("param_hp",1);
    param_hi = CConfig::getDouble("param_hi",0);
    param_hd = CConfig::getDouble("param_hd",0);
    param_vp = CConfig::getDouble("param_vp",1);
    param_vi = CConfig::getDouble("param_vi",0);
    param_vd = CConfig::getDouble("param_vd",0);
    fov = 100;
    pulseMode = 1;
    stabMode = 0;
    openSerialPort();
//    startTimer(50);
    for (int i=0;i<PLC_REG_SIZE;i++)
    {
        plcReg[i] = 0;
        plcInput[i] = 0;
        plcout[i]=0;
    }
    modbusInit();

}
int requestCount=0;
void c_gimbal_control::timerEvent(QTimerEvent *event)
{

        modbusReadRequest();
        requestCount++;
        if((requestCount%5==0))modbusReadRequestCam();
    if(plcValueChanged)
    {
        plcValueChanged = false;

    }
}

void  c_gimbal_control::modbusInit()
{

    if (modbusDeviceCam) {
        modbusDeviceCam->disconnectDevice();
        delete modbusDeviceCam;
        modbusDeviceCam = nullptr;
    }
    modbusDeviceCam = new QModbusTcpClient(this);//

    if (!modbusDeviceCam)
        return ;


    if (modbusDeviceCam->state() != QModbusDevice::ConnectedState) {
        const QUrl url = QUrl::fromUserInput(CConfig::getString("plc_cam","192.168.0.5:502"));
        modbusDeviceCam->setConnectionParameter(QModbusDevice::NetworkPortParameter, url.port());
        modbusDeviceCam->setConnectionParameter(QModbusDevice::NetworkAddressParameter, url.host());

        modbusDeviceCam->setTimeout(200);
        modbusDeviceCam->setNumberOfRetries(3);
        if (!modbusDeviceCam->connectDevice()) {
            //            CConfig::appendLog("Modbus connect failed");
        }
    }else{
        modbusDeviceCam->disconnectDevice();
    }
    if (modbusDeviceCU) {
        modbusDeviceCU->disconnectDevice();
        delete modbusDeviceCU;
        modbusDeviceCU = nullptr;
    }
    modbusDeviceCU = new QModbusTcpClient(this);//

    if (!modbusDeviceCU)
        return ;


    if (modbusDeviceCU->state() != QModbusDevice::ConnectedState) {
        const QUrl url = QUrl::fromUserInput(CConfig::getString("plc_cu","192.168.0.2:502"));
        modbusDeviceCU->setConnectionParameter(QModbusDevice::NetworkPortParameter, url.port());
        modbusDeviceCU->setConnectionParameter(QModbusDevice::NetworkAddressParameter, url.host());

        modbusDeviceCU->setTimeout(200);
        modbusDeviceCU->setNumberOfRetries(3);
        if (!modbusDeviceCU->connectDevice()) {
            //            CConfig::appendLog("Modbus connect failed");
        }
    }else{
        modbusDeviceCU->disconnectDevice();
    }
    return ;
}
void c_gimbal_control::modbusReadRequest()
{
    if (modbusDeviceCU)
    {
        modbusCount = 0;
        QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters,0,32);
        if (auto *reply = modbusDeviceCU->sendReadRequest(readUnit, 2)) {
            if (!reply->isFinished())
                connect(reply, &QModbusReply::finished, this, &c_gimbal_control::modbusInputReadCU);
            else
                delete reply; // broadcast replies return immediately
        } else {
            //        CConfig::appendLog("Request modbus error: " + modbusDevice->errorString());
            //        printf("Request modbus error: ");
            modbusDeviceCU->disconnect();
        }
    }

    return ;
}
void c_gimbal_control::modbusReadRequestCam()
{
    if (modbusDeviceCam)
    {
        modbusCountCam = 0;
        QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters,0,32);
        if (auto *reply = modbusDeviceCam->sendReadRequest(readUnit, 2)) {
            if (!reply->isFinished())
                connect(reply, &QModbusReply::finished, this, &c_gimbal_control::modbusInputReadCam);
            else
                delete reply; // broadcast replies return immediately
        } else {
            //        CConfig::appendLog("Request modbus error: " + modbusDevice->errorString());
            //        printf("Request modbus error: ");
            modbusDeviceCam->disconnect();
        }
    }
}
void c_gimbal_control::onStateChanged(int state)
{

}

void c_gimbal_control::setplc(int addr, int value,int plci)
{
    if(plci==0){
        if(addr<16)plcout[addr] = value;
        QModbusDataUnit writeUnit(QModbusDataUnit::Coils,0,32);
        for(int i = 0;i<16;i++)
        {
            writeUnit.setValue(i,plcout[i]);
        }

        modbusDeviceCam->sendWriteRequest(writeUnit,2);
    }
    else {
        if(addr<16)plcout[addr] = value;
        QModbusDataUnit writeUnit(QModbusDataUnit::Coils,0,32);
        for(int i = 16;i<32;i++)
        {
            writeUnit.setValue(i,plcout[i-16]);
        }

        modbusDeviceCU->sendWriteRequest(writeUnit,2);
    }

}
void c_gimbal_control::modbusInputReadCam()
{
    QString msg;

    auto reply = qobject_cast<QModbusReply *>(sender());//
    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();
        plcValueChanged =true;
        for (uint i = 0; i < unit.valueCount(); i++) {
            if(i<PLC_REG_SIZE)
            {
                plcInputCam[i] = unit.value(i);
                //                if(plcInput[i])sendSetupPacket(12);
                modbusCountCam++;
            }


        }
        //        dataPlot.push_back((plcInput[20]-18000)/5.0);
        //        while(dataPlot.size()>=500)dataPlot.pop_front();
    } else if (reply->error() == QModbusDevice::ProtocolError) {
        msg =  QString("Read response error: %1 (Mobus exception: 0x%2)").
                arg(reply->errorString()).
                arg(reply->rawResult().exceptionCode(), -1, 16);
    } else {
        msg =  QString("Read response error: %1 (code: 0x%2)").
                arg(reply->errorString()).
                arg(reply->error(), -1, 16);
    }

    reply->deleteLater();
}

int stimconcount = 0;
void c_gimbal_control::modbusInputReadCU()
{
    QString msg;

    auto reply = qobject_cast<QModbusReply *>(sender());//
    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();
        plcValueChanged =true;
        for (uint i = 0; i < unit.valueCount(); i++) {
            if(i<PLC_REG_SIZE)
            {
                plcInput[i] = unit.value(i);
                //                if(plcInput[i])sendSetupPacket(12);
                modbusCount++;
            }


        }
        //        dataPlot.push_back((plcInput[20]-18000)/5.0);
        //        while(dataPlot.size()>=500)dataPlot.pop_front();
    } else if (reply->error() == QModbusDevice::ProtocolError) {
        msg =  QString("Read response error: %1 (Mobus exception: 0x%2)").
                arg(reply->errorString()).
                arg(reply->rawResult().exceptionCode(), -1, 16);
    } else {
        msg =  QString("Read response error: %1 (code: 0x%2)").
                arg(reply->errorString()).
                arg(reply->error(), -1, 16);
    }

    isCuAlive = plcInput[23];
    isStimAlive =  plcInput[24];
    reply->deleteLater();
}
void c_gimbal_control::openSerialPort()
{
    serial = new QSerialPort(this);
    serial->setPortName("COM13");
    serial->setBaudRate(115200);
    //    serial->setDataBits(p.dataBits);
    //    serial->setParity(p.parity);
    //    serial->setStopBits(p.stopBits);
    //    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
        isSerialAvailable = true;
        printf("Serial online");
    } else {
        isSerialAvailable = false;
        printf("Serial offline");
    }
}
void c_gimbal_control::joystickInput(QByteArray data)
{
    for(int i=0;i<data.size();i++)
    {
        readPelco((unsigned char)(*(data.data()+i)));
    }
}
void c_gimbal_control::send(QByteArray data)
{
    socket->writeDatagram(data,dstAddr1,remotePort);
    socket->writeDatagram(data,dstAddr2,remotePort);
    if(isSerialAvailable)serial->write(data);

}

//void c_gimbal_control::setPPR(float pprh,float pprv)
//{
//    CConfig::setValue("pprh",pprh);
//    CConfig::setValue("pprv",pprv);
//    param_pprh = pprh;
//    param_pprv = pprv;
//    sendSetupPacket(6);
//}
void c_gimbal_control::setPIDparams(double ph, double ih, double dh,double pv, double iv, double dv)
{

    param_hp = ph;//CConfig::getDouble("param_hp",1);
    param_hi = ih;//CConfig::getDouble("param_hi",0);
    param_hd = dh;//CConfig::getDouble("param_hd",0);
    param_vp = pv;//CConfig::getDouble("param_vp",1);
    param_vi = iv;//CConfig::getDouble("param_vi",0);
    param_vd = dv;//CConfig::getDouble("param_vd",0);
    CConfig::setValue("param_hp",param_hp);
    CConfig::setValue("param_hi",param_hi);
    CConfig::setValue("param_hd",param_hd);
    CConfig::setValue("param_vp",param_vp);
    CConfig::setValue("param_vi",param_vi);
    CConfig::setValue("param_vd",param_vd);
    sendSetupPacket(3);
    sendSetupPacket(4);
    sendSetupPacket(5);
}
void c_gimbal_control::setAbsPos(double azi,double ele)
{
    abs_pos_h = azi;
    abs_pos_v = ele;
    sendSetupPacket(8);
}
void c_gimbal_control::setStimMode( int value)
{
    stabMode = value;
    sendSetupPacket(2);
}
void c_gimbal_control::setSocket(QUdpSocket *psocket)
{
    socket = psocket;
}
void c_gimbal_control::setFOV(double ifov )
{
    fov = ifov;
    if(fov<0.5)fov=0.5;
    if(fov>100)fov=100;
    CConfig::setValue("fov",fov);
    sendSetupPacket(2);
}
void c_gimbal_control::sendSetupPacket(int index)
{
    isCuAlive = false;
    packet2[1] = index;
    if(index==2)
    {
        packet2[2] = int(fov/100.0*65535)>>8;
        packet2[3] = int(fov/100.0*65535)&0xff;
        packet2[4] = int(pulseMode);
        packet2[5] = stabMode;
        packet2[6] = (unsigned char) (packet2[1]+packet2[2]+packet2[3]+packet2[4]+packet2[5]);
    }
    else if(index==3)//p
    {
        packet2[2] = int((param_hp+10.0)/20.0*65535)>>8;
        packet2[3] = int((param_hp+10.0)/20.0*65535)&0xff;
        packet2[4] = int((param_vp+10.0)/20.0*65535)>>8;
        packet2[5] = int((param_vp+10.0)/20.0*65535)&0xff;
        packet2[6] = (unsigned char) (packet2[1]+packet2[2]+packet2[3]+packet2[4]+packet2[5]);

    }
    else if(index==4)//i
    {
        packet2[2] = int((param_hi+10.0)/20.0*65535)>>8;
        packet2[3] = int((param_hi+10.0)/20.0*65535)&0xff;
        packet2[4] = int((param_vi+10.0)/20.0*65535)>>8;
        packet2[5] = int((param_vi+10.0)/20.0*65535)&0xff;
        packet2[6] = (unsigned char) (packet2[1]+packet2[2]+packet2[3]+packet2[4]+packet2[5]);

    }
    else if(index==5)//d
    {
        packet2[2] = int((param_hd+10.0)/20.0*65535)>>8;
        packet2[3] = int((param_hd+10.0)/20.0*65535)&0xff;
        packet2[4] = int((param_vd+10.0)/20.0*65535)>>8;
        packet2[5] = int((param_vd+5.0)/4.0*65535)&0xff;
        packet2[6] = (unsigned char) (packet2[1]+packet2[2]+packet2[3]+packet2[4]+packet2[5]);

    }
    else if(index==6)//ppr
    {
        packet2[2] = int(param_pprh/100)>>8;
        packet2[3] = int(param_pprh/100)&0xff;
        packet2[4] = int(param_pprv/100)>>8;
        packet2[5] = int(param_pprv/100)&0xff;
        packet2[6] = (unsigned char) (packet2[1]+packet2[2]+packet2[3]+packet2[4]+packet2[5]);

    }
    else if(index==7)//acc
    {
        packet2[2] = int(param_acc*1000)>>8;
        packet2[3] = int(param_acc*1000)&0xff;
        packet2[4] = int(param_acc*1000)>>8;
        packet2[5] = int(param_acc*1000)&0xff;
        packet2[6] = (unsigned char) (packet2[1]+packet2[2]+packet2[3]+packet2[4]+packet2[5]);

    }
    else if(index==8)//absPos
    {
        packet2[2] = int((abs_pos_h+180)/360.0*65535)>>8;
        packet2[3] = int((abs_pos_h+180)/360.0*65535)&0xff;
        packet2[4] = int((abs_pos_v+180)/360.0*65535)>>8;
        packet2[5] = int((abs_pos_v+180)/360.0*65535)&0xff;
        packet2[6] = (unsigned char) (packet2[1]+packet2[2]+packet2[3]+packet2[4]+packet2[5]);

    }
    else if(index==9)//calib
    {
        packet2[2] = int((hCalib+5.0)/10.0*65535)>>8;
        packet2[3] = int((hCalib+5.0)/10.0*65535)&0xff;
        packet2[4] = int((vCalib+5.0)/10.0*65535)>>8;
        packet2[5] = int((vCalib+5.0)/10.0*65535)&0xff;
        packet2[6] = (unsigned char) (packet2[1]+packet2[2]+packet2[3]+packet2[4]+packet2[5]);

    }
    else if(index==12)//cong tac hanh trinh
    {

        //        int data = getPLCInput(0);
        //        data = data>>12;
        packet2[2] =  getPLCInput(0,1);//data&0x01;
        packet2[3] =  getPLCInput(1,1);//data&0x02;
        packet2[4] =  getPLCInput(2,1);//data&0x04;
        packet2[5] =  getPLCInput(3,1);//data&0x08;
        packet2[6] = (unsigned char) (packet2[1]+packet2[2]+packet2[3]+packet2[4]+packet2[5]);

    }
    else if(index==13)//workmode
    {

        int data = getPLCInput(0,1);
        data = data>>12;
        packet2[2] = workMode;
        packet2[3] = 0;
        packet2[4] = 0;
        packet2[5] = 0;
        packet2[6] = (unsigned char) (packet2[1]+packet2[2]+packet2[3]+packet2[4]+packet2[5]);

    }
    else if(index==14)//ping
    {

        lastPing = clock();
        packet2[2] = lastPing;
        packet2[3] = lastPing>>8;
        packet2[4] = lastPing>>16;
        packet2[5] = lastPing>>24;
        packet2[6] = (unsigned char) (packet2[1]+packet2[2]+packet2[3]+packet2[4]+packet2[5]);

    }
    QByteArray ba((char*)&packet2[0],7);
    send(ba);
    send(ba);
    CConfig::appendLog("sendSetupPacket");
}
void c_gimbal_control::setACC(float maxAcc)
{
    param_acc = maxAcc;
    CConfig::setValue("param_acc",param_acc);
    sendSetupPacket(7);
}

QByteArray c_gimbal_control::getSerialData()
{
    QByteArray ba(serialData);
    serialData.clear();
    return ba;
}

bool c_gimbal_control::getIsSerialAvailable() const
{
    return isSerialAvailable;
}
void c_gimbal_control::setWorkmode(int mode)
{
    workMode = mode;
    sendSetupPacket(13);
}

int c_gimbal_control::getWorkMode() const
{
    return workMode;
}
void c_gimbal_control::reloadConfig()
{
    pulseMode = CConfig::getInt("pulseMode",1);
    fov = CConfig::getDouble("fov",60);
    sendSetupPacket(2);

    param_hp = CConfig::getDouble("param_hp");
    param_hi = CConfig::getDouble("param_hi");
    param_hd = CConfig::getDouble("param_hd");
    param_vp = CConfig::getDouble("param_vp");
    param_vi = CConfig::getDouble("param_vi");
    param_vd = CConfig::getDouble("param_vd");
    sendSetupPacket(3);
    sendSetupPacket(4);
    sendSetupPacket(5);
    param_gear_h = CConfig::getDouble("param_gear_h");
    param_pprh = param_gear_h*1000;
    param_gear_v = CConfig::getDouble("param_gear_v");
    param_pprv = param_gear_v*1000;
    sendSetupPacket(6);
    param_acc = CConfig::getDouble("param_acc");
    sendSetupPacket(7);
    hCalib = CConfig::getDouble("hCalib",-0.16);
    vCalib = CConfig::getDouble("vCalib",0.115);
    sendSetupPacket(9);


}


void c_gimbal_control::setPulseMode(int ipulseMode)
{
    pulseMode = ipulseMode;
    CConfig::setValue("pulseMode",pulseMode);
    sendSetupPacket(2);

}

void c_gimbal_control::outputPelco(int panValue, int tiltValue)
{
    mPan = filterPan->update(panValue);
    mTil = filterTilt->update(tiltValue);
    // generate command
    if(mTil>0) { com2[3]=1;    com2[4]=0;  }
    else       { com2[3]=0;    com2[4]=1;  }
    if(mPan>0) { com2[1]=1;    com2[2]=0;  }
    else       { com2[1]=0;    com2[2]=1;  }
    com2[5]=0;
    com2[6]=0;
    packet[3]=0;
    for (int i =0; i<8;i++)
    {
        packet[3]+= ((com2[i])<<i);
    }
    packet[2]=0;
    //generate data
    packet[4]=(unsigned char)(abs(mPan));
    packet[5]=(unsigned char)(abs(mTil));
    //generate checksum
    //   packet[6] = 0;
    packet[6] = (unsigned char) (packet[1]+packet[2]+packet[3]+packet[4]+packet[5]);
    QByteArray ba((char*)&packet[0],7);
    send(ba);
    if(serial->bytesAvailable())
    {
        serialData.append(serial->readAll());

    }
    //   for (int i=0;i<7;i++)
    //   {
    //       readPelco(packet[i]);
    //   }
}
