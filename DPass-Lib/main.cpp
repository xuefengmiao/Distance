//随机产生一条线，实现双向，单向检测
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <features.h>
#include <opencv2/video/video.hpp>
#include <cv.h>
#include <iostream>
#include "VideoProcessorRect.h"
#include "myframeprocessor.h"
#include "frameprocessor.h"
#include "FeatureTrackerRect.h"




using namespace cv;
using namespace std;



int main(){
 VideoCapture cap("rtsp://admin:admin@192.168.1.211:554/channel1");
    Mat image;
    VideoProcessorRect vp;
    vp.setDelay(5);
    vp.displayOutput("Output Frame");
    FeatureTrackerRect tracker;
    tracker.setPointAndHeight(122,244,145,256);  //矩形框的顶点  高度 和宽度


    while(1)
    {
        cap>>image;
        vp.setInput(image);
        vp.setFrameProcessor(&tracker);
        vp.run();
    }

    //     VideoProcessorRect vp;
    //     Mat image=imread("/home/xuefengmiao/blue.jpg");
    //     vp.setInput(image);
    //     vp.displayOutput("Output Frame");
    //     FeatureTrackerRect tracker;
    //     tracker.setStart(12,32);
    //     tracker.setEnd(323,287);
    //     vp.setFrameProcessor(&tracker);
    //     vp.run();
    //     return 1;
    //    VideoProcessorRect vp;
    //    vp.displayOutput("Output Frame");
    //    Mat  frame;
    //    QString qstr;
    //    std::string str="/home/xuefengmiao/111/";
    //    qstr = QString::fromStdString(str);
    //        QFileInfoList list=GetFileList(qstr);
    //    //--读取特定路径下的图片
    //         for (int i = 0; i < list.size(); ++i)
    //         {
    //             QFileInfo fileInfo = list.at(i);
    //             std::string addr="";
    //             std::string fileName=fileInfo.fileName().toStdString();
    //             std::ostringstream oss1;
    //             oss1<<str<<fileName;
    //             addr+=oss1.str();
    //             cout<<addr<<endl;
    //              frame=imread(addr);
    //                   vp.setInput(frame);
    //                   vp.setDelay(10);
    //                   FeatureTrackerRect tracker;
    //                   tracker.setStart(12,32);
    //                   tracker.setEnd(323,287);
    //                   vp.setFrameProcessor(&tracker);
    //                   vp.run();
    //         }

   // vp.displayInput("Current Frame");


   // vp.setDelay(10);
    //vp.setDelay(1000.0/vp.getFrameRate());

    //vp.setOutput("../xyzhang_02.avi",0,0.0,true);
    //vp.setOutput("../video/小苹果tracker.avi",0,0.0,true);
    //vp.setOutput("videowrite",".png");

    //vp.setFrameProcessor(canny);

    //FrameProcessor* fp=new MyFrameProcessor();
    //vp.setFrameProcessor(fp);


}








































