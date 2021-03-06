#include "videoprocessor.h"

VideoProcessor::VideoProcessor():callIt(true),delay(0),fnumber(0),stop(false),frameToStop(-1)
{
}

void VideoProcessor::setFrameProcessor( void (*frameProcessingCallback)(cv::Mat&,cv::Mat&)){

    frameProcessor=0;
    process=frameProcessingCallback;
    callProcess();
}

bool VideoProcessor::setInput(std::string filename){
    fnumber=0;
    capture.release();
    //images.clear();
    return capture.open(filename);

}

void VideoProcessor::displayInput(std::string wn){
    windowNameIuput=wn;
    cv::namedWindow(windowNameIuput);

}

void VideoProcessor::displayOutput(std::string wn){
    windowNameOutput=wn;
    cv::namedWindow(windowNameOutput);

}

void VideoProcessor::dontDisplay(){
    cv::destroyWindow(windowNameIuput);
    cv::destroyWindow(windowNameOutput);
    windowNameIuput.clear();
    windowNameOutput.clear();

}

void VideoProcessor::stopIt(){
    stop=true;
}

bool VideoProcessor::isStopped(){
    return stop;
}

bool VideoProcessor::isOpened(){
    //return capture.isOpened();
    return capture.isOpened()||!images.empty();
}

void VideoProcessor::setDelay(int d){
    delay=d;
}

bool VideoProcessor::readNextFrame(cv::Mat& frame){
    //return capture.read(frame);
    if(images.size()==0){
        return capture.read(frame);
    }else{
        if(itImg!=images.end()){
            frame=cv::imread(*itImg);
            itImg++;
            return frame.data!=0;
        }else{
            return false;
        }
    }
}

void VideoProcessor::callProcess(){
    callIt=true;
}

void VideoProcessor::dontCallProcess(){
    callIt=false;
}

void VideoProcessor::stopAtFrameNo(long frame){
    frameToStop=frame;
}

long VideoProcessor::getFrameNumber(){
    long fnumber=static_cast<long>(capture.get(CV_CAP_PROP_POS_FRAMES));
    return fnumber;
}

double VideoProcessor::getFrameRate(){
    return capture.get(CV_CAP_PROP_FPS);
}

void VideoProcessor::run(){
    cv::Mat frame;
    cv::Mat output;
    if(!isOpened())
        return;
    stop=false;

    while(!isStopped()){
        if(!readNextFrame(frame))
            break;
        //if(windowNameIuput.length()!=0)
          //  cv::imshow(windowNameIuput,frame);
        if(callIt){
            //process(frame,output);
            if(process){
                process(frame,output);
            }else if(frameProcessor){
                frameProcessor->process(frame,output);
            }
            fnumber++;
        }else{
            output=frame;
        }

        //output frame
        if(outputFile.length()!=0)
            writeNextFrame(output);

        if(windowNameOutput.length()!=0)
          {
           //line(output,Point(4*output.rows/5,0),Point(4*output.rows/5,output.cols),CV_RGB(0,0,0),5,0);
            cv::imshow(windowNameOutput,output);
        }

        if(delay>=0&&cv::waitKey(delay)>=0){
            stopIt();
        }

        if(frameToStop>=0&&getFrameNumber()==frameToStop)
            stopIt();

        cout<<"CV_CAP_PROP_POS_FRAMES= "<<getFrameNumber()<<endl;
    }
}

//picture from forder process

bool VideoProcessor::setInput(const std::vector<std::string>&imgs){
    fnumber=0;
    capture.release();
    images=imgs;
    itImg=images.begin();
    return true;
}

void VideoProcessor::setFrameProcessor(FrameProcessor* frameProcessorPtr){
    process=0;
    frameProcessor=frameProcessorPtr;
    callProcess();
}



//vedio write

int VideoProcessor::getCodec(char codec[4]){
    if(images.size()!=0)
        return -1;
    union{
        int value;
        char code[4];
    }returned;

    returned.value=static_cast<int>(capture.get(CV_CAP_PROP_FOURCC));
    codec[0]=returned.code[0];
    codec[1]=returned.code[1];
    codec[2]=returned.code[2];
    codec[3]=returned.code[3];
    //capture.get(CV_CAP_PROP_FRMAE_SIZE);
    std::cout<<"vaule: "<<returned.value<<" ,  "<<"codec:"<<codec[0]<<codec[1]<<codec[2]<<codec[3]<<endl;

    if(returned.value==0){
        return 1145656920;
    }else{
        return returned.value;
    }

}

cv::Size VideoProcessor::getFrameSize(){
    cv::Size frameSize = cv::Size((int)capture.get(CV_CAP_PROP_FRAME_WIDTH),
                                  (int)capture.get(CV_CAP_PROP_FRAME_HEIGHT)) ;
    return frameSize;
}

bool VideoProcessor::setOutput(const std::string& filename,int codec,double framerate,bool isColor){
    outputFile=filename;
    extention.clear();
    if(framerate==0.0){
        framerate=getFrameRate();
    }
    char c[4];

    if(codec==0){
        codec=getCodec(c);
    }

    return writer.open(outputFile,codec,framerate,getFrameSize(),isColor);
}

bool VideoProcessor::setOutput(const std::string& filename,const std::string& ext,int numberOfDigits,int startIndex){
    if(numberOfDigits<0)
        return false;
    outputFile=filename;
    //if(ext==".jpg")
    extention=ext;

    digits=numberOfDigits;
    currentIndex=startIndex;
    return true;
}

void VideoProcessor::writeNextFrame(cv::Mat& frame){
    if(extention.length()){
        std::stringstream ss;
        ss<<outputFile<<std::setfill('0')<<std::setw(digits)<<currentIndex++<<extention;
        cv::imwrite(ss.str(),frame);

    }else{

        writer.write(frame);

    }
}




















































