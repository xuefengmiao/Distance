#ifndef FEATURETRACKER_H
#define FEATURETRACKER_H

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

class FeatureTracker : public FrameProcessor
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
   // Point origin;//用于保存鼠标选择第一次单击时点的位置
   // Rect selection;//用于保存鼠标选择的矩形框
    //bool selectObject;//代表是否在选要跟踪的初始目标，true表示正在用鼠标选择

public:
    FeatureTracker();
    void detectFeaturePoints();
    bool addNewPoints();
    bool acceptTrackedPoint(int i);
    void handleTrackedPoints(cv::Mat& frame,cv::Mat& output);
    void process(cv::Mat& frame,cv::Mat& output);

   // void onMouse( int event, int x, int y, int, void* );
//    void setOrigin(Point p);
//    Point getOrigin();
//    void setSelection(Rect r);
//    Rect getSelection();
//    void setSelectionObject(bool b);
//    bool getSelectionObject();
    //Point origin;//用于保存鼠标选择第一次单击时点的位置
    //Rect selection;//用于保存鼠标选择的矩形框
    //bool selectObject;//代表是否在选要跟踪的初始目标，true表示正在用鼠标选择
   /* void setOrigin(Point p)
    {
         origin=p;
    }

    Point getOrigin(){
        return origin;
    }

    void setSelection(Rect r)
    {
        selection=r;
    }

    Rect getSelection(){
        return selection;
    }

    void setSelectionObject(bool b){
        selectObject=b;
    }

    bool getSelectionObject(){
        return selectObject;
    }
    */

};

#endif // FEATURETRACKER_H
