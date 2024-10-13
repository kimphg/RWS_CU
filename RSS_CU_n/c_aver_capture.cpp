#include "c_aver_capture.h"
#include "opencv2/opencv.hpp"
static cv::Mat frameAver;

void ErrorMsg(DWORD ErrorCode)
{
    printf("ErrorCode = %d\n", ErrorCode);
    if (ErrorCode == CAP_EC_SUCCESS)
    {
        printf("CAP_EC_SUCCESS\n");
    }
    if (ErrorCode == CAP_EC_INIT_DEVICE_FAILED)
    {
        printf("CAP_EC_INIT_DEVICE_FAILED\n");
    }
    if (ErrorCode == CAP_EC_DEVICE_IN_USE)
    {
        printf("CAP_EC_DEVICE_IN_USE\n");
    }
    if (ErrorCode == CAP_EC_NOT_SUPPORTED)
    {
        printf("CAP_EC_NOT_SUPPORTED\n");
    }
    if (ErrorCode == CAP_EC_INVALID_PARAM)
    {
        printf("CAP_EC_INVALID_PARAM\n");
    }
    if (ErrorCode == CAP_EC_TIMEOUT)
    {
        printf("CAP_EC_TIMEOUT\n");
    }
    if (ErrorCode == CAP_EC_NOT_ENOUGH_MEMORY)
    {
        printf("CAP_EC_NOT_ENOUGH_MEMORY\n");
    }
    if (ErrorCode == CAP_EC_UNKNOWN_ERROR)
    {
        printf("CAP_EC_UNKNOWN_ERROR\n");
    }
    if (ErrorCode == CAP_EC_ERROR_STATE)
    {
        printf("CAP_EC_ERROR_STATE\n");
    }
    if (ErrorCode == CAP_EC_HDCP_PROTECTED_CONTENT)
    {
        printf("CAP_EC_HDCP_PROTECTED_CONTENT\n");
    }
}
static bool frameBusy = false;
c_aver_capture* thiscapture = nullptr;
BOOL WINAPI CaptureVideoAnalog(VIDEO_SAMPLE_INFO VideoInfo, BYTE *pbData, LONG lLength, __int64 tRefTime, LONG lUserData)
{
    frameBusy = true;
    frameAver = cv::Mat(VideoInfo.dwHeight, VideoInfo.dwWidth, CV_8UC3, (uchar*)pbData).clone();//single capture image
    //ans2 = Mat(VideoInfo.dwHeight, VideoInfo.dwWidth, CV_8UC3, (uchar*)pbData); //sequence capture image
    if(thiscapture!=nullptr){
    frameAver.copyTo(thiscapture->output);
    thiscapture->bGetData=true;
    }
//    bGetData = true;
    return TRUE;
}

c_aver_capture::c_aver_capture()
{
    init();
}
void c_aver_capture::init()
{
    thiscapture = this;
    LONG lRetVal;
    DWORD dwDeviceNum;
    DWORD dwDeviceIndex = 0;
    HANDLE hAverCapturedevice[10];
    //Device Control
    //1. Get Device Number
    lRetVal = AVerGetDeviceNum(&dwDeviceNum);

    if (lRetVal != CAP_EC_SUCCESS) {
        printf("\nAVerGetDeviceNum Fail");
        ErrorMsg(lRetVal);
//        system("pause");
    }
    if (dwDeviceNum == 0) {
        printf("NO device found\n");
//        system("pause");
    }
    else {
        printf("Device Number = %lu\n", dwDeviceNum);
    }

    //2. Create device representative object handle
    for (DWORD dwDeviceIndex = 0; dwDeviceIndex < dwDeviceNum; dwDeviceIndex++) {
        lRetVal = AVerCreateCaptureObjectEx(dwDeviceIndex, DEVICETYPE_ALL, NULL, &hAverCapturedevice[dwDeviceIndex]);
        if (lRetVal != CAP_EC_SUCCESS) {
            printf("\nAVerCreateCaptureObjectEx Fail\n");
            ErrorMsg(lRetVal);
            system("pause");
        }
        else
            printf("\nAVerCreateCaptureObjectEx Success\n");
    }
    //3. Start Streaming//

    //3.1 set video source
    //lRetVal = AVerSetVideoSource(hAverCapturedevice[0], 3);
    lRetVal = AVerSetVideoSource(hAverCapturedevice[0], 3);

    //3.2 set Video Resolution & FrameRate
    VIDEO_RESOLUTION VideoResolution = { 0 };
    INPUT_VIDEO_INFO InputVideoInfo;
    ZeroMemory(&InputVideoInfo, sizeof(InputVideoInfo));
    InputVideoInfo.dwVersion = 2;
    Sleep(500);
    lRetVal = AVerGetVideoInfo(hAverCapturedevice[0], &InputVideoInfo);
    VideoResolution.dwVersion = 1;
    VideoResolution.dwVideoResolution = VIDEORESOLUTION_720X576;

    lRetVal = AVerSetVideoResolutionEx(hAverCapturedevice[0], &VideoResolution);
    lRetVal = AVerSetVideoInputFrameRate(hAverCapturedevice[0], 6000);


    //3.3 Start Streaming
    lRetVal = AVerStartStreaming(hAverCapturedevice[0]);
    if (lRetVal != CAP_EC_SUCCESS) {
        printf("\AVerStartStreaming Fail\n");
        ErrorMsg(lRetVal);
        //system("pause");
    }
    else
    {
        printf("\AVerStartStreaming Success\n");
        //system("pause");
    }
    //video capture
    VIDEO_CAPTURE_INFO VideoCaptureInfo;
    ZeroMemory(&VideoCaptureInfo, sizeof(VIDEO_CAPTURE_INFO));
    VideoCaptureInfo.bOverlayMix = FALSE;
    VideoCaptureInfo.dwCaptureType = CT_SEQUENCE_FRAME;
    VideoCaptureInfo.dwSaveType = ST_CALLBACK_RGB24;
    VideoCaptureInfo.lpCallback = CaptureVideoAnalog;
    VideoCaptureInfo.lCallbackUserData = NULL;
    lRetVal = AVerCaptureVideoSequenceStart(hAverCapturedevice[0], VideoCaptureInfo);
    if (FAILED(lRetVal))
    {
        return ;
    }
}
void c_aver_capture::run()
{

    while(1)
    {

    }
}
