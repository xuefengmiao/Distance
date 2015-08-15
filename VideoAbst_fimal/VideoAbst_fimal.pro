#-------------------------------------------------
#
# Project created by QtCreator 2015-06-05T10:20:07
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = VideoAbst_fimal
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    vibeBackgroundOwn.cpp \
    vibe.cpp \
    myfgdetector.cpp \
    image_loc.cpp \
    handle_param.cpp \
    cluster.cpp \
    bs_post_processing.cpp \
    util.cpp \
    seamlessclone.cpp \
    read_xml.cpp \
    kmeans.cpp \
    blob_run.cpp
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
/usr/local/lib/libopencv_videostab.so \
/usr/local/lib/libopencv_nonfree.so \
/usr/local/lib/libopencv_ml.so \
/usr/local/lib/libopencv_legacy.so \
/usr/local/lib/libopencv_ocl.so \
/usr/local/lib/libopencv_objdetect.so

OTHER_FILES += \
    VideoAbst_fimal.pro.user

HEADERS += \
    vibeBackgroundOwn.h \
    vibe.h \
    myfgdetector.h \
    list.h \
    image_loc.h \
    handle_param.h \
    cluster.h \
    bs_post_processing.h \
    util.h \
    seamlessclone.h \
    read_xml.h \
    kmeans.h \
    blob_run.h
