#-------------------------------------------------
#
# Project created by QtCreator 2021-05-05T18:54:09
#
#-------------------------------------------------

QT       += core gui network serialport serialbus printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoGrab
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    compasscustom_widget.cpp \
    control_center_dialog.cpp \
        mainwindow.cpp \
    c_gimbal_control.cpp \
    c_config.cpp \
    kcf/gradientMex.cpp \
    kcf/kcf.cpp \
    dialogconfig.cpp \
    qcgaugewidget.cpp \
    c_lowpass.cpp \
    UsbDevice.cpp \
    qcustomslider.cpp \
    video_window.cpp \
    videostab.cpp \
    videothread.cpp

HEADERS  += \
    compasscustom_widget.h \
    control_center_dialog.h \
    mainwindow.h \
    c_gimbal_control.h \
    c_config.h \
    kcf/fhog.hpp \
    kcf/gradientMex.h \
    kcf/kcf.hpp \
    kcf/sse.hpp \
    kcf/wrappers.hpp \
    dialogconfig.h \
    qcgaugewidget.h \
    c_lowpass.h \
    UsbDevice.h \
    qcustomslider.h \
    video_window.h \
    videostab.h \
    videothread.h

FORMS    += mainwindow.ui \
    control_center_dialog.ui \
    dialogconfig.ui
INCLUDEPATH += "C:/opencv/opencv2413/build/include"
win32:CONFIG(debug, debug|release):LIBS += -L"C:/opencv/opencv2413/build/x64/vc12/lib/" -lopencv_core2413d
win32:CONFIG(debug, debug|release):LIBS += -L"C:/opencv/opencv2413/build/x64/vc12/lib/" -lopencv_highgui2413d
win32:CONFIG(debug, debug|release):LIBS += -L"C:/opencv/opencv2413/build/x64/vc12/lib/" -lopencv_imgproc2413d
win32:CONFIG(debug, debug|release):LIBS += -L"C:/opencv/opencv2413/build/x64/vc12/lib/" -lopencv_calib3d2413d
win32:CONFIG(debug, debug|release):LIBS += -L"C:/opencv/opencv2413/build/x64/vc12/lib/" -lopencv_core2413d
win32:CONFIG(debug, debug|release):LIBS += -L"C:/opencv/opencv2413/build/x64/vc12/lib/" -lopencv_features2d2413d
win32:CONFIG(debug, debug|release):LIBS += -L"C:/opencv/opencv2413/build/x64/vc12/lib/" -lopencv_flann2413d
win32:CONFIG(debug, debug|release):LIBS += -L"C:/opencv/opencv2413/build/x64/vc12/lib/" -lopencv_video2413d
win32:CONFIG(debug, debug|release):LIBS += -L"C:/opencv/opencv2413/build/x64/vc12/lib/" -lopencv_videostab2413d
#release:
win32:CONFIG(release, debug|release):LIBS += -L"C:/opencv/opencv2413/build/x64/vc12/lib/" -lopencv_core2413
win32:CONFIG(release, debug|release):LIBS += -L"C:/opencv/opencv2413/build/x64/vc12/lib/" -lopencv_highgui2413
win32:CONFIG(release, debug|release):LIBS += -L"C:/opencv/opencv2413/build/x64/vc12/lib/" -lopencv_imgproc2413
win32:CONFIG(release, debug|release):LIBS += -L"C:/opencv/opencv2413/build/x64/vc12/lib/" -lopencv_calib3d2413
win32:CONFIG(release, debug|release):LIBS += -L"C:/opencv/opencv2413/build/x64/vc12/lib/" -lopencv_core2413
win32:CONFIG(release, debug|release):LIBS += -L"C:/opencv/opencv2413/build/x64/vc12/lib/" -lopencv_features2d2413
win32:CONFIG(release, debug|release):LIBS += -L"C:/opencv/opencv2413/build/x64/vc12/lib/" -lopencv_flann2413
win32:CONFIG(release, debug|release):LIBS += -L"C:/opencv/opencv2413/build/x64/vc12/lib/" -lopencv_video2413
win32:CONFIG(release, debug|release):LIBS += -L"C:/opencv/opencv2413/build/x64/vc12/lib/" -lopencv_videostab2413

win32 {
DESTDIR = $$PWD/bin
QMAKE_POST_LINK =  "C:/Qt/Qt5.14.2/5.14.2/msvc2017/bin/windeployqt.exe" $$shell_path($$DESTDIR/$${TARGET}.exe)
}

DISTFILES += \
    dialogconfig_ui.py

RESOURCES += \
    CalibResourcesFile.qrc \
    FooterResourcesFile.qrc \
    HeaderResourcesFile.qrc \
    IrSight_ResourcesFile.qrc \
    RangingsResourcesFile.qrc \
    ResourceFile.qrc \
    SystemResourcesFile.qrc \
    WeaponResourcesFile.qrc
