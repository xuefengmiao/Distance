#-------------------------------------------------
#
# Project created by QtCreator 2015-07-06T16:17:08
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = version3
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    RectLocate.cpp \
    kmeans.cpp
LIBS += /usr/local/lib/libopencv_core.so \
/usr/local/lib/libopencv_flann.so \
/usr/local/lib/libopencv_gpu.so \
/usr/local/lib/libopencv_highgui.so \
/usr/local/lib/libopencv_video.so \
/usr/local/lib/libopencv_photo.so \
/usr/local/lib/libopencv_superres.so \
/usr/local/lib/libopencv_stitching.so \
/usr/local/lib/libopencv_imgproc.so \
/usr/local/lib/libopencv_calib3d.so \
/usr/local/lib/libopencv_features2d.so \
/usr/local/lib/libopencv_contrib.so \
/usr/local/lib/libopencv_videostab.so \
/usr/local/lib/libopencv_nonfree.so \
/usr/local/lib/libopencv_ml.so \
/usr/local/lib/libopencv_legacy.so \
/usr/local/lib/libopencv_ocl.so \
/usr/local/lib/libopencv_objdetect.so

HEADERS += \
    RectLocate.h \
    def.h \
    kmeans.h
