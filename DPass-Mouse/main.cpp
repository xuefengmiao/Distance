#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <features.h>
#include <opencv2/video/video.hpp>
#include <cv.h>
#include <iostream>
#include "videoprocessor.h"
#include "myframeprocessor.h"
#include "frameprocessor.h"
#include "featuretracker.h"

using namespace cv;
using namespace std;

void canny(cv::Mat& img,cv::Mat& out);


/*
extern FeatureTracker tracker;
bool selectObject;
void onMouse( int event, int x, int y, int, void* )
{

    cout<<"the mouse is working---------------------------------------"<<tracker.getSelectionObject()<<endl;

    if( tracker.getSelectionObject())//只有当鼠标左键按下去时才有效，然后通过if里面代码就可以确定所选择的矩形区域selection了
    {
//        selection.x = MIN(x, origin.x);//矩形左上角顶点坐标
//        selection.y = MIN(y, origin.y);
//        selection.width = std::abs(x - origin.x);//矩形宽
//        selection.height = std::abs(y - origin.y);//矩形高

//         tracker.getSelection().x=MIN(x, tracker.getOrigin().x);
//         tracker.getSelection().y=MIN(y, tracker.getOrigin().x);
//         tracker.getSelection().width=std::abs(x-tracker.getOrigin().x);
//         tracker.getSelection().height=std::abs(y-tracker.getOrigin().y);

        //selection &= Rect(0, 0, image.cols, image.rows);//用于确保所选的矩形区域在图片范围内
    }

    switch( event )
    {
    case CV_EVENT_LBUTTONDOWN:
        tracker.setOrigin(Point(x,y));
        tracker.setSelection(Rect(x,y,0,0));//鼠标刚按下去时初始化了一个矩形区域
        tracker.setSelectionObject(true);
        break;
    case CV_EVENT_LBUTTONUP:
       tracker.setSelectionObject(false);
//        if( selection.width > 0 && selection.height > 0 )
//            trackObject = -1;
        break;
    }
}
*/
int main(){
    //selectObject=false;

    VideoProcessor vp;


   //vp.setInput("rtsp://admin:admin@192.168.1.96:554/1-1");
   vp.setInput("rtsp://admin:admin@192.168.1.213:554/channel1");

    //rtsp://admin:admin@192.168.1.211:554/channel1
    //vp.displayInput("Current Frame");
    vp.displayOutput("Output Frame");
   //setMouseCallback( "Output Frame", onMouse, 0 );//消息响应机制
    vp.setDelay(10);
    //vp.setDelay(1000.0/vp.getFrameRate());

   vp.setOutput("/home/xuefengmiao/test2.avi",0,0.0,true);
    //vp.setOutput("../video/小苹果tracker.avi",0,0.0,true);
    //vp.setOutput("videowrite",".png");

    //vp.setFrameProcessor(canny);

    //FrameProcessor* fp=new MyFrameProcessor();
    //vp.setFrameProcessor(fp);

     FeatureTracker tracker;
    vp.setFrameProcessor(&tracker);

    vp.run();

    return 1;
}


void canny(cv::Mat& img,cv::Mat& out){
    if(img.channels()==3){
        cv::cvtColor(img,out,CV_BGR2GRAY);
    }
    cv::Canny(out,out,100,200);
    cv::threshold(out,out,128,255,cv::THRESH_BINARY_INV);
}
