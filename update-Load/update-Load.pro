#-------------------------------------------------
#
# Project created by QtCreator 2014-10-20T09:34:15
#
#-------------------------------------------------

QT       += core

QT       -= gui

QT +=sql

TARGET = update-Load
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp


INCLUDEPATH += /usr/local/include/opencv
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
