include(../../../NEUVision.pri)

VERSION       = $$Z3D_VERSION
TEMPLATE      = lib
# CONFIG       += plugin
QT           += widgets concurrent
TARGET        = $$qtLibraryTarget(zcameracalibration)
DESTDIR       = $$Z3D_BUILD_DIR
DEFINES      += Z3D_CAMERACALIBRATION_LIBRARY

DEFINES      += PINHOLE_CALIB_NAME=\"'\\"Pinhole\\"'\"
DEFINES      += PINHOLE_CALIB_VERSION=\"$${Z3D_VERSION_STR}\"

HEADERS      += \
    zcameracalibration.h \
    zcameracalibration_global.h \
    zcameracalibrationplugininterface.h \
    zcameracalibrationprovider.h \
    zcameracalibrator.h \
    zmulticameracalibration.h \
    zmulticameracalibrator.h \
    zpinhole/zopencvcustomstereomulticameracalibrator.h \
    zpinhole/zopencvstereocameracalibration.h \
    zpinhole/zopencvstereomulticameracalibrator.h \
    zpinhole/zopencvstereomulticameracalibratorconfigwidget.h \
    zpinhole/zpinholecameracalibration.h \
    zpinhole/zpinholecameracalibrationplugin.h \
    zpinhole/zpinholecameracalibrator.h \
    zpinhole/zpinholecameracalibratorconfigwidget.h

SOURCES      += \
    zcameracalibration.cpp \
    zcameracalibrationplugininterface.cpp \
    zcameracalibrationprovider.cpp \
    zmulticameracalibration.cpp \
    zpinhole/zopencvcustomstereomulticameracalibrator.cpp \
    zpinhole/zopencvstereocameracalibration.cpp \
    zpinhole/zopencvstereomulticameracalibrator.cpp \
    zpinhole/zopencvstereomulticameracalibratorconfigwidget.cpp \
    zpinhole/zpinholecameracalibration.cpp \
    zpinhole/zpinholecameracalibrationplugin.cpp \
    zpinhole/zpinholecameracalibrator.cpp \
    zpinhole/zpinholecameracalibratorconfigwidget.cpp

FORMS += \
    zpinhole/zopencvstereomulticameracalibratorconfigwidget.ui \
    zpinhole/zpinholecameracalibratorconfigwidget.ui

###############################################################################
# OpenCV
include($$PWD/../../../3rdparty/opencv.pri)

###############################################################################
# Core
include($$PWD/../../zcore/zcore.pri)
