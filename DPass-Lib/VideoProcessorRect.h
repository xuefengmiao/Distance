#ifndef VideoProcessorRect_H
#define VideoProcessorRect_H

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

class VideoProcessorRect
{
private:
    cv::VideoCapture capture;
    void (*process)(cv::Mat&,cv::Mat&);
    bool callIt;
    std::string windowNameIuput;
    std::string windowNameOutput;
    int delay;
    long fnumber;
    long frameToStop;
    bool stop;

    //process images
    //std::vector<std::string> images;
    Mat  itImg;
    FrameProcessor* frameProcessor;
    Mat images;

    //video write
    cv::VideoWriter writer;
    std::string outputFile;
    int currentIndex;
    int digits;
    std::string extention;


public:
    VideoProcessorRect();
    void setFrameProcessor(void (*frameProcessingCallback)(cv::Mat&,cv::Mat&));
    bool setInput(Mat &img);
    void displayInput(std::string wn);
    void displayOutput(std::string wn);
    void dontDisplay();
    void stopIt();
    bool isStopped();
    bool isOpened();
    void setDelay(int d);
    bool readNextFrame(cv::Mat& frame);
    void callProcess();
    void dontCallProcess();
    void stopAtFrameNo(long frame);
    long getFrameNumber();
    double getFrameRate();
    void run();
    //void canny(cv::Mat& img,cv::Mat& out);

    bool setInput(const std::vector<std::string>&imgs);
    void setFrameProcessor(FrameProcessor* frameProcessorPtr);

    //video write
    bool setOutput(const std::string& filename,int codec=0,double framerate=0.0,bool isColor=true);
    bool setOutput(const std::string& filename,const std::string& ext,int numberOfDigits=3,int startIndex=0);
    int getCodec(char codec[4]);
    cv::Size getFrameSize();
    void writeNextFrame(cv::Mat& frame);
};

#endif // VideoProcessorRect_H
