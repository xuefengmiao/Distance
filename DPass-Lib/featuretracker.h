#ifndef FeatureTrackerRect_H
#define FeatureTrackerRect_H

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

class FeatureTrackerRect : public FrameProcessor
{
private:
    cv::Mat gray;
    cv::Mat gray_prev;
    std::vector<cv::Point2f> points[2];
    std::vector<cv::Point2f> initial;
    std::vector<cv::Point2f> features;
    int max_count;
    double qlevel;
    double minDist;
    std::vector<uchar> status;
    std::vector<float> err;

    Point origin;//用于保存鼠标选择第一次单击时点的位置
    Point selection;//用于保存鼠标选择的矩形框

   // int type; //设置类型    0表示双向穿越都报警  1表示从左往右穿越报警  2表示从右往穿越报警  默认选择方式是0

public:
    FeatureTrackerRect();
    void detectFeaturePoints();
    bool addNewPoints();
    bool acceptTrackedPoint(int i);
    void handleTrackedPoints(cv::Mat& frame,cv::Mat& output);
    void process(cv::Mat& frame,cv::Mat& output);

    void setStart(int x,int y);
    void setEnd(int x,int y);
    void setType(int x);
    void setPointAndHeight(int x_start,int y_start,int height_,int width_);
   // void setPointAndType(int x_start,int y_start,int x_end,int y_end,int type_);

};

#endif // FeatureTrackerRect_H
