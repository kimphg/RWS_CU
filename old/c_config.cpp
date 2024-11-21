
#include "c_config.h"
//CConfig         mGlobbalConfig;
#include <iostream>
#include <ctime>
using namespace std;
//double CConfig::shipHeadingDeg=5;
//double CConfig::shipCourseDeg = 0;
//double CConfig::shipSpeed=0;
//double CConfig::antennaAziDeg=0;
bool CConfig::isChanged = false;
QHash<QString, QString> CConfig::mHashData;
volatile long long int CConfig::time_now_ms = 0;
double  CConfig::mLat = DEFAULT_LAT,CConfig::mLon=DEFAULT_LONG;


void CConfig::setValue(QString key, double value)
{

    QString strValue = QString::number(value);
    mHashData.insert(key, strValue);
    isChanged = true;
    //SaveToFile();
}

void CConfig::setValue(QString key, QString value)
{
    mHashData.insert(key, value);
    isChanged = true;
    //SaveToFile();
}

double CConfig::getDouble(QString key,double defaultValue )
{
    if(mHashData.find(key)!=mHashData.end())
        return mHashData.value(key).toDouble();
    else
    {
        setValue(key,defaultValue);
        //SaveToFile();
        return defaultValue;
    }
}
int CConfig::getInt(QString key, int defaultValue )
{
    if(mHashData.find(key)!=mHashData.end())
        return mHashData.value(key).toInt();
    else
    {
        setValue(key,defaultValue);
        return defaultValue;
    }
}
QString CConfig::getString(QString key,QString defaultValue )
{
    if(mHashData.find(key)!=mHashData.end())
        return mHashData.value(key);
    else
    {
        setValue(key,defaultValue);
        isChanged = true;
        return defaultValue;
    }
}

CConfig::CConfig(void)
{
    //hashData.;
    //shipHeadingDeg = 0;
    readFile();
    CConfig::mLat = getDouble("mLat");
    CConfig::mLon = getDouble("mLon");
}

CConfig::~CConfig(void)
{
}
std::vector<std::pair<double,double>> locationHistory;
void CConfig::setGPSLocation(double lat, double lon)
{

    mLat=lat;
    mLon=lon;
    setValue("mLat",mLat);
    setValue("mLon",mLon);
    //save if distance>100m
    if(locationHistory.size())
    {
        if(abs(locationHistory.back().second-lat)>0.01&&
                abs(locationHistory.back().first- lon)>0.01)locationHistory.clear();
        else if(abs(locationHistory.back().second-lat)<0.001&&
                abs(locationHistory.back().first- lon)<0.001)return ;

    }
    locationHistory.push_back(std::make_pair(lon,lat));

}

std::vector<std::pair<double, double> > *CConfig::GetLocationHistory()
{
    return &locationHistory;
}
void CConfig::backup()
{
    if(QFile::exists(HR_CONFIG_FILE_BACKUP_1))
    {
        if (QFile::exists(HR_CONFIG_FILE_BACKUP_2))
        {
            QFile::remove(HR_CONFIG_FILE_BACKUP_2);

        }
        QFile::rename(HR_CONFIG_FILE_BACKUP_1,HR_CONFIG_FILE_BACKUP_2);
    }
    QFile::copy(HR_CONFIG_FILE,HR_CONFIG_FILE_BACKUP_1);
}
void CConfig::SaveToFile()
{
    if(isChanged)isChanged = false;else return;
    QHash<QString, QString>::const_iterator it = mHashData.constBegin();
    QXmlStreamAttributes attr;
    while (it != mHashData.constEnd()) {
        attr.append(it.key(),it.value());
        ++it;
    }
    QFile xmlFile(HR_CONFIG_FILE);
    QXmlStreamWriter writer;
    xmlFile.open(QIODevice::WriteOnly);
    writer.setDevice(&xmlFile);
    writer.writeEmptyElement(XML_ELEM_NAME);
    writer.writeAttributes(attr);
    writer.writeEndElement();
    xmlFile.close();

    //QFile xmlFile(HR_CONFIG_FILE_BACKUP_1);
    //xmlFile.copy(HR_CONFIG_FILE);
}

void CConfig::appendLog(const char* error)
{
    freopen(HR_ERROR_FILE, "a", stderr );
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S    ",timeinfo);
    cerr << buffer;
    cerr << error;
    cerr << endl;
}

//void CConfig::AddMessage(QString message)
//{
//    QDateTime now = QDateTime::fromMSecsSinceEpoch(time_now_ms);
//    WarningMessage warning;
//    warning.message = now.toString("hh:mm:ss:")+ message ;
//    warning.time = CConfig::time_now_ms;
//    mWarningList.push(warning);
//}

void CConfig::SaveAndSetConfigAsDefault()
{
    SaveToFile();
    if (QFile::exists(HR_CONFIG_FILE_DF))
    {
        QFile::remove(HR_CONFIG_FILE_DF);
    }
    QFile::copy( HR_CONFIG_FILE,HR_CONFIG_FILE_DF);

}
void CConfig::readFile(QString fileName)
{
    QFile xmlFile(fileName);
    bool isError = !(xmlFile.open(QIODevice::ReadOnly));

    QXmlStreamReader xml;
    xml.setDevice(&xmlFile);
    int nElement = 0;
//    QHash<QString, QString> hashData;
    while (xml.readNextStartElement())
    {

        if(xml.name()==XML_ELEM_NAME)
        {

            for (int i=0;i<xml.attributes().size();i++)
            {
                nElement++;
                QXmlStreamAttribute attr = xml.attributes().at(i);
                CConfig::mHashData.insert( attr.name().toString(),
                                 attr.value().toString());
            }
        }
        if (xml.tokenType() == QXmlStreamReader::Invalid)
            xml.readNext();
        // readNextStartElement() leaves the stream in
        // an invalid state at the end. A single readNext()
        // will advance us to EndDocument.
        if (xml.hasError()) {
            isError = true;
        }
    }
    if(isError||(CConfig::mHashData.size()<5))
    {
        if(fileName==HR_CONFIG_FILE)                return readFile(HR_CONFIG_FILE_BACKUP_1);
        else if(fileName==HR_CONFIG_FILE_BACKUP_1)  return readFile(HR_CONFIG_FILE_BACKUP_2);
        else if(fileName==HR_CONFIG_FILE_DF) {

            return ;
        }
        else
        {

            appendLog("Empty config, load default");
            return readFile(HR_CONFIG_FILE_DF);
        }
    }

    xmlFile.close();
//    CConfig::mHashData = hashData;
//    return hashData;
}
void CConfig::readFile() {

     readFile(HR_CONFIG_FILE);
}

//std::queue<WarningMessage>* CConfig::getWarningList()
//{
//    return &mWarningList;
//}

