#include "featuretracker.h"



 static bool selectObject=false;

 static Point origin;//用于保存鼠标选择第一次单击时点的位置
 static Rect selection;//用于保存鼠标选择的矩形框
//bool selectObject;//代表是否在选要跟踪的初始目标，true表示正在用鼠标选择


//setMouseCallback( "Output Frame", onMouse, 0 );//消息响应机制

static  bool flag=true;
int trackObject = 0; //代表跟踪目标数目


void onMouse( int event, int x, int y, int, void* )
{
    cout<<"the mouse is working==============================================="<<selectObject<<endl;

    if( selectObject )//只有当鼠标左键按下去时才有效，然后通过if里面代码就可以确定所选择的矩形区域selection了
    {
        selection.x = MIN(x, origin.x);//矩形左上角顶点坐标
        selection.y = MIN(y, origin.y);
        selection.width = std::abs(x - origin.x);//矩形宽
        selection.height = std::abs(y - origin.y);//矩形高
        cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
        //selection &= Rect(0, 0, image.cols, image.rows);//用于确保所选的矩形区域在图片范围内
    }

    switch( event )
    {
    case CV_EVENT_LBUTTONDOWN:
        origin = Point(x,y);
        selection = Rect(x,y,0,0);//鼠标刚按下去时初始化了一个矩形区域
        selectObject = true;
        cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$44"<<endl;
        break;
    case CV_EVENT_LBUTTONUP:
        cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%5"<<endl;
        cout<<"!!!!!!!!!!!!!!!!!!!!!"<<selection.width<<"  "<<selection.height<<endl;
        if( selection.width > 0 && selection.height > 0 )
        {
            trackObject =1;
            selectObject = false;
        }
        break;
    }
    cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;
}

FeatureTracker::FeatureTracker():max_count(500),qlevel(0.01),minDist(10.0)
{
    //new FrameProcessor();
}

void FeatureTracker::detectFeaturePoints(){
    cv::goodFeaturesToTrack(gray,features,max_count,qlevel,minDist);

}

bool FeatureTracker::addNewPoints(){
    return points[0].size()<=10;

}

bool FeatureTracker::acceptTrackedPoint(int i){

    return status[i]&&(abs(points[0][i].x-points[1][i].x)+abs(points[0][i].y-points[1][i].y)>2);

}

void FeatureTracker::handleTrackedPoints(cv::Mat& frame,cv::Mat& output)
{
    int x=selection.x;
    int y=selection.y;
    int height=selection.height;
    int width=selection.width;

    //画矩形  当鼠标左键松开时，利于地点和终点得到矩形区域
    if(1==trackObject)
    {
        cv::line(output,Point(x,y),Point(x+width,y),cv::Scalar(255,0,0),2,0);//
        cv::line(output,Point(x,y+height),Point(x+width,y+height),cv::Scalar(255,0,0),2,0);//
          cv::line(output,Point(x,y),Point(x,y+height),cv::Scalar(255,0,0),2,0);//
           cv::line(output,Point(x+width,y+height),Point(x+width,y),cv::Scalar(255,0,0),2,0);//
    }
    if(flag)
    {
        cout<<"flag==========================================="<<flag<<endl;
        setMouseCallback( "Output Frame", onMouse, 0 );//消息响应机制
        flag=false;
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

}

void FeatureTracker::process(cv::Mat& frame,cv::Mat& output){
    cv::cvtColor(frame,gray,CV_BGR2GRAY);
    frame.copyTo(output);

    if(addNewPoints()){
        detectFeaturePoints();
        points[0].insert(points[0].end(),features.begin(),features.end());
        initial.insert(initial.end(),features.begin(),features.end());

    }

    if(gray_prev.empty()){
        gray.copyTo(gray_prev);
    }

    cv::calcOpticalFlowPyrLK(gray_prev,gray,points[0],points[1],status,err);

    int k=0;
    for(int i=0;i<points[1].size();i++){
        if(acceptTrackedPoint(i)){
            initial[k]=initial[i];
            points[1][k++]=points[1][i];
        }
    }

    points[1].resize(k);
    initial.resize(k);

    handleTrackedPoints(frame,output);

    std::swap(points[1],points[0]);
    cv::swap(gray_prev,gray);
}







