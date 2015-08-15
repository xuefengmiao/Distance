#include "FeatureTrackerRect.h"

void FeatureTrackerRect::setPointAndHeight(int x_start, int y_start,int height_,int width_)
{
    origin=Point(x_start,y_start);
    selection=Point(height_,width_);
    //type=type_;
}

void FeatureTrackerRect::setStart(int x, int y)
{
  origin = Point(x,y);
}
void FeatureTrackerRect::setEnd(int x, int y)
{
   selection=Point(x,y);
}

//void FeatureTrackerRect::setType(int x)
//{
//    type=x;
//}

FeatureTrackerRect::FeatureTrackerRect():max_count(500),qlevel(0.01),minDist(10.0)
{
    //new FrameProcessor();
}

void FeatureTrackerRect::detectFeaturePoints(){
    cv::goodFeaturesToTrack(gray,features,max_count,qlevel,minDist);

}

bool FeatureTrackerRect::addNewPoints(){
    return points[0].size()<=10;

}

bool FeatureTrackerRect::acceptTrackedPoint(int i){

    return status[i]&&(abs(points[0][i].x-points[1][i].x)+abs(points[0][i].y-points[1][i].y)>2);

}

void FeatureTrackerRect::handleTrackedPoints(cv::Mat& frame,cv::Mat& output)
{
    int x=selection.x;
    int y=selection.y;
    int height=selection.x;
    int width=selection.y;

    //画矩形  当鼠标左键松开时，利于地点和终点得到矩形区域

    {
        cv::line(output,Point(x,y),Point(x+width,y),cv::Scalar(255,0,0),2,0);//
        cv::line(output,Point(x,y+height),Point(x+width,y+height),cv::Scalar(255,0,0),2,0);//
          cv::line(output,Point(x,y),Point(x,y+height),cv::Scalar(255,0,0),2,0);//
           cv::line(output,Point(x+width,y+height),Point(x+width,y),cv::Scalar(255,0,0),2,0);//
    }


    //判断运动物体是否在矩形区域中运动
    for(int i=0;i<points[1].size();i++)
    {
       // int x1=initial[i].x;//起点
        int x2=points[1][i].x;//终点
        //int y1=initial[i].y;
        int y2=points[1][i].y;
        float ex=x+width;
        float ey=y+height;
        /*
               float x=points[1][i].x;
               float y=points[1][i].y;
               float sx=rect.x;
               float sy=rect.y;
               float ex=sx+rect.width;
               float ey=sy+rect.height;

               if(x>sx&&x<ex&&y>sy&&y<ey){
                   drawRect(output,rect,cv::Scalar(0,0,255));
          */
        //cv::line(output,initial[i],points[1][i],cv::Scalar(255,255,0));
       // cv::circle(output,points[1][i],3,cv::Scalar(0,255,255),-1);

        //进去警戒区域内 报警
        if(x2>x&&x2<ex&&y2>y&&y2<ey){
            cv::line(output,Point(x,y),Point(x+width,y),cv::Scalar(0,0,255),2,0);//
            cv::line(output,Point(x,y+height),Point(x+width,y+height),cv::Scalar(0,0,255),2,0);//
              cv::line(output,Point(x,y),Point(x,y+height),cv::Scalar(0,0,255),2,0);//
               cv::line(output,Point(x+width,y+height),Point(x+width,y),cv::Scalar(0,0,255),2,0);//
        }
       // else

        /*
        if(x1>x3 && x2<x3)
        {
             cout<<"左边越界  Left is outing-----"<<endl;
            line(output,Point(2*output.cols/7,0),Point(2*output.cols/7,output.rows),CV_RGB(255,0,0),5,0);
         //line(output,Point(2*output.rows/5,0),Point(2*output.rows/5,output.cols),CV_RGB(255,0,0),5,0);
          // cv::line(output,initial[i],points[1][i],cv::Scalar(255,255,0));
         //cv::circle(output,points[1][i],3,cv::Scalar(0,255,255),-1);
         //line(output,Point(output.rows/2,output.cols/3),25,CV_RGB(255,0,0),1,0);
        }
        else if(x1<x4 && x2>x4)
        {
             cout<<"右边越界 Right is outing-----"<<endl;
          line(output,Point(5*output.cols/7,0),Point(5*output.cols/7,output.rows),CV_RGB(255,0,0),5,0);
        }
      else
      {
          line(output,Point(5*output.cols/7,0),Point(5*output.cols/7,output.rows),CV_RGB(0,0,0),5,0);
          line(output,Point(2*output.cols/7,0),Point(2*output.cols/7,output.rows),CV_RGB(0,0,0),5,0);
       }*/
    /*    int x1=initial[i].x;
        int x2=points[1][i].x;
        int x3=2*output.cols/7;
        int x4=5*output.cols/7;
       // cout<<"x1="<<x1<<"  x2="<<x2<<"   x3="<<x3<<endl;
        cv::line(output,initial[i],points[1][i],cv::Scalar(255,255,0));
        cv::circle(output,points[1][i],3,cv::Scalar(0,255,255),-1);

        if(x1>x3 && x2<x3)
        {
             cout<<"左边越界  Left is outing-----"<<endl;
            line(output,Point(2*output.cols/7,0),Point(2*output.cols/7,output.rows),CV_RGB(255,0,0),5,0);
         //line(output,Point(2*output.rows/5,0),Point(2*output.rows/5,output.cols),CV_RGB(255,0,0),5,0);
          // cv::line(output,initial[i],points[1][i],cv::Scalar(255,255,0));
         //cv::circle(output,points[1][i],3,cv::Scalar(0,255,255),-1);
         //line(output,Point(output.rows/2,output.cols/3),25,CV_RGB(255,0,0),1,0);
        }
        else if(x1<x4 && x2>x4)
        {
             cout<<"右边越界 Right is outing-----"<<endl;
          line(output,Point(5*output.cols/7,0),Point(5*output.cols/7,output.rows),CV_RGB(255,0,0),5,0);
        }
      else
      {
          line(output,Point(5*output.cols/7,0),Point(5*output.cols/7,output.rows),CV_RGB(0,0,0),5,0);
          line(output,Point(2*output.cols/7,0),Point(2*output.cols/7,output.rows),CV_RGB(0,0,0),5,0);
       }

    }
    */
    }
//    imshow("output frame",output);
//    waitKey(10);

}

void FeatureTrackerRect::process(cv::Mat& frame,cv::Mat& output){
   // cout<<"sss"<<endl;
    cv::cvtColor(frame,gray,CV_BGR2GRAY);

    frame.copyTo(output);

    if(addNewPoints()){
        detectFeaturePoints();
        points[0].insert(points[0].end(),features.begin(),features.end());
        initial.insert(initial.end(),features.begin(),features.end());

    }

    //cout<<"before   points[0].size==="<<points[0].size()<<endl;

    if(gray_prev.empty()){
//        cout<<"************************!!!!!!!!!!!!!!!!!!!!!******************"<<endl;
        gray.copyTo(gray_prev);
    }

    cv::calcOpticalFlowPyrLK(gray_prev,gray,points[0],points[1],status,err);   
//    void calcOpticalFlowPyrLK( InputArray prevImg, InputArray nextImg,
//                               InputArray prevPts, CV_OUT InputOutputArray nextPts,
//                               OutputArray status, OutputArray err,
//                               Size winSize=Size(21,21), int maxLevel=3,
//                               TermCriteria criteria=TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 30, 0.01),
//                               int flags=0, double minEigThreshold=1e-4);
//    cout<<"ing  points[0].size==="<<points[0].size()<<endl;
//    cout<<"ing  points[1].size==="<<points[1].size()<<endl;

    int k=0;
    for(int i=0;i<points[1].size();i++){
        if(acceptTrackedPoint(i)){
            initial[k]=initial[i];
            points[1][k++]=points[1][i];
        }
    }

    points[1].resize(k);
    initial.resize(k);

//    cout<<"points[0].size==="<<points[0].size()<<endl;
//    cout<<"points[1].size==="<<points[1].size()<<endl;

    handleTrackedPoints(frame,output);

    std::swap(points[1],points[0]);
    cv::swap(gray_prev,gray);
   // cout<<"@@@@@"<<endl;
}







