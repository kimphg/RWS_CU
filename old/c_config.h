//slogan provide glide echo pond family sibling romance coast misery identify path
#ifndef CONFIG_H
#define CONFIG_H

#define HR_DATA_REC_PATH  "D:\\RecordData/"
#define HR_CONFIG_FILE    "D:\\config.xml"
#define HR_CONFIG_FILE_BACKUP_1 "D:\\config_backup_1.xml"
#define HR_CONFIG_FILE_BACKUP_2 "D:\\config_backup_2.xml"
#define HR_CONFIG_FILE_DF "D:\\config_default.xml"
#define XML_ELEM_NAME     "topgun_config"
#define HR_ERROR_FILE "errorLog.txt"

#include <math.h>
#define DEFAULT_LAT		20.707
#define DEFAULT_LONG	106.78
#include <QFile>
#include <QHash>
#include <QXmlStreamReader>
#include <time.h>
#include <QDateTime>
#include <queue>

inline QString demicalDegToDegMin(double demicalDeg)
{
    return QString::number( (short)demicalDeg) +
            QString::fromLocal8Bit("\260")+
            QString::number((demicalDeg-(short)demicalDeg)*60.0,'f',2);
}
class CConfig
{
public:
    CConfig(void);
    ~CConfig(void);
    static inline void ConvWGSToKm(double* x, double *y, double m_Long,double m_Lat)
    {
        double refLat = (mLat + (m_Lat))*0.00872664625997;//pi/360
        *x	= (((m_Long) - mLon) * 111.31949079327357)*cos(refLat);// 3.14159265358979324/180.0*6378.137);//deg*pi/180*rEarth
        *y	= ((m_Lat- mLat ) * 111.132954);
        //tinh toa do xy KM so voi diem center khi biet lat-lon
    }
    static inline void ConvKmToWGS(double x, double y, double *m_Long, double *m_Lat)
    {
        *m_Lat  = CConfig::mLat +  (y)/(111.132954);
        double refLat = (CConfig::mLat +(*m_Lat))*0.00872664625997;//3.14159265358979324/180.0/2;
        *m_Long = (x)/(111.31949079327357*cos(refLat))+ CConfig::mLon;
        //tinh toa do lat-lon khi biet xy km (truong hop coi trai dat hinh cau)
    }
    static void setGPSLocation(double lat,double lon);
    static double  mLat,mLon;
    static std::vector<std::pair<double,double> >* GetLocationHistory();
//    static double shipHeadingDeg;
//    static double shipCourseDeg;
//    static double shipSpeed;
//    static double antennaAziDeg;
    static volatile qint64 time_now_ms;
    static QHash<QString, QString> mHashData;

    static void    setValue(QString key, double value);
    static void    setValue(QString key,QString value);
    static double  getDouble(QString key, double defaultValue=0);
    static QString getString(QString key, QString defaultValue="0");
    static int     getInt(QString key, int defaultValue=0);
    static void    SaveAndSetConfigAsDefault();
    static void    SaveToFile();
    static void     appendLog(const char *error);
//    static void     AddMessage(QString warning);
    //static QXmlStreamReader xml;
    static void readFile();
    static bool    isChanged;
    static void backup();
private:
    static void readFile(QString fileName);
};

#endif
