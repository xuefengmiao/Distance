#include "myframeprocessor.h"

MyFrameProcessor::MyFrameProcessor()
{
    new FrameProcessor();
}
void MyFrameProcessor::process(cv::Mat& input,cv::Mat& output){
    if(input.channels()==3){
        cv::cvtColor(input,output,CV_BGR2GRAY);
    }
    cv::Canny(output,output,100,200);
    cv::threshold(output,output,128,255,cv::THRESH_BINARY_INV);
    //cout<<"123"<<endl;
}
