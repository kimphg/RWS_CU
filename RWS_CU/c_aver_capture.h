#ifndef C_AVER_CAPTURE_H
#define C_AVER_CAPTURE_H

#include "Windows.h"

#include "AVerCapAPI_Pro.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <QThread>
class c_aver_capture: public QThread
{
public:
    c_aver_capture();
    void run();
    cv::Mat output;
    bool bGetData ;
private:
    void init();
};

#endif // C_AVER_CAPTURE_H
