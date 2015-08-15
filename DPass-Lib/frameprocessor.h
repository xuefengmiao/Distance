#ifndef FRAMEPROCESSOR_H
#define FRAMEPROCESSOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <features.h>
#include <cv.h>
#include <iostream>

using namespace cv;
using namespace std;


class FrameProcessor
{
public:
    FrameProcessor();
    virtual void process(cv::Mat& input,cv::Mat& output);
};

#endif // FRAMEPROCESSOR_H
