#ifndef MYFRAMEPROCESSOR_H
#define MYFRAMEPROCESSOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <features.h>
#include <cv.h>
#include <iostream>
#include "frameprocessor.h"

using namespace cv;
using namespace std;


class MyFrameProcessor : public FrameProcessor
{
public:
    MyFrameProcessor();
    void process(cv::Mat& input,cv::Mat& output);

};

#endif // MYFRAMEPROCESSOR_H
