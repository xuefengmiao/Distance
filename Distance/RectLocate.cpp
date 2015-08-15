

#include"RectLocate.h"


int CircleLocate::circleLocate(Mat src)
{

    //src=imread("/home/xuefengmiao/jpg/pic_2015-07-06100034.jpg");
    //Mat src=imread("/home/xuefengmiao/jpg/pic_2015-07-06095316.jpg");
    //resize(src,src,Size(1024,768));
    //高斯模糊
//    int RATE_AREA=0.65;
//   int MIN_AREA=500;
//    int THRESHOLD=0;
    src.copyTo(after_image);

    for(int MIN_AREA=500;MIN_AREA<10000;)
    {
        MIN_AREA=MIN_AREA+100;
    for(int THRESHOLD=31;THRESHOLD<150;)
    {
        THRESHOLD=THRESHOLD+10;
        for(double RATE_AREA=0.9;RATE_AREA>0.5;)
        {
            RATE_AREA=RATE_AREA-0.05;


            {
                if(TOTAL_CIRCLES==points.size())
                    return 1;

                //THRESHOLD=THRESHOLD+10;
                points.clear();
                areas.clear();
                radiuss.clear();

                Mat src_blur;
                GaussianBlur( src, src_blur, Size(m_GaussianBlurSize, m_GaussianBlurSize),
                              0, 0, BORDER_DEFAULT );

                //灰度化图片
                Mat src_gray;
                cvtColor( src_blur, src_gray, CV_RGB2GRAY );

//                //直方图均衡化
//                Mat equist = Mat::zeros( src_gray.rows, src_gray.cols, src_gray.type() );
//                equalizeHist( src_gray, equist );

                //二值化
                Mat img_threshold;
                threshold(src_gray, img_threshold, THRESHOLD, 255, THRESH_BINARY);

                //形态学操作
                Mat element = getStructuringElement( MORPH_ELLIPSE, Size(3, 3) );
                morphologyEx(img_threshold, img_threshold, MORPH_CLOSE, element);


                //翻转图像 黑变白  白换黑
                for(int i=0;i<img_threshold.rows;i++)
                    for(int j=0;j<img_threshold.cols;j++)
                        img_threshold.at<uchar>(i,j)=255-img_threshold.at<uchar>(i,j);

                //Find 轮廓 of possibles circles
                vector< vector< Point> > contours;
                findContours(img_threshold,
                             contours, // a vector of contours
                             CV_RETR_EXTERNAL, // 提取外部轮廓
                             CV_CHAIN_APPROX_SIMPLE); // all pixels of each contours

                cv::Mat result(img_threshold.size(),CV_8U,cv::Scalar(0));
                //// Draw blue contours on a white image
                drawContours(result, contours,
                             -1, // draw all contours
                             Scalar(255), // in white
                             1); // with a thickness of 1
//                imshow("result",result);
//                waitKey(0);

                std::vector<std::vector<cv::Point> >::iterator itc = contours.begin();
                //cout<<"contours.size="<<contours.size()<<endl;
                while (itc != contours.end())
                {
                    //cout<<"here"<<endl;
                    double area = cv::contourArea(*itc);//轮廓的面积（包含的像素的个数）
                    //std::cout<<"contours area:"<<area<<std::endl;
                    //cv::Rect rect = cv::boundingRect(*itContours);
                    //double rate=(double)(max(rect.height,rect.width))/(min(rect.height,rect.width));   //the rect's rate of width&&height
                    //最小包围圆
                    float radius;
                    Point2f center;
                    minEnclosingCircle(*itc,center,radius);
                    double lunkuo_area=3.1415*radius*radius;
                    //if(area >15000 && area<50000 && rate<1.2)//面积较小的直接屏蔽，不要
                    //如果包围圆的面积和轮廓的面积（包含的像素的个数）的比值大于80%就认为是圆形
                    if(lunkuo_area>0 && (area/lunkuo_area)>RATE_AREA && area>MIN_AREA)
                    {
                        //std::cout<<"contours area:"<<area<<std::endl;
                        //cout<<"here"<<endl;
                        //ci2rcle(src,(center),static_cast<int>(radius),Scalar(0,0,255),2);
                        points.push_back(center);
                        areas.push_back(area);
                        radiuss.push_back(static_cast<int>(radius));
                    }
                    itc++;
                }
                verifyCircles();
                //验证这个六个圆的大小差不多
//                if(verifyCircles())
//                {
//                    cout<<"verifyCircle ing"<<endl;
//                }
//                else cout<<"verifyCircle Failure"<<endl;

            }

        }
    }
    }

return -1;
//    cout<<"here  running ---"<<endl;

//    if(TOTAL_CIRCLES==points.size())
//    {
//      return 1;
//    }
//    else
//        return 0;
}



void CircleLocate::showImage(int time)
{
    vector<Point2f>::iterator rf=points.begin();
    vector<int>::iterator ra=radiuss.begin();
    int number=0;
    while(rf!=points.end())
    {
        Point2f point=*rf;
        int radius=*ra;
        circle(after_image,point,radius,Scalar(0,0,255),2);
        rf++;
        ra++;
        number++;
        stringstream text;
        text<<number;

    putText( after_image, text.str(),
             point,CV_FONT_HERSHEY_COMPLEX, 2, Scalar(255, 255, 0) );
    }
    //resize(after_image,after_image,Size(1024,768));
    imshow("after_image",after_image);
    waitKey(time*1000);
}
int  CircleLocate::getPoints(vector<Point2f>& p)
{
    vector<Point2f>::iterator it;//声明迭代器
    for(it = points.begin();it!=points.end();++it){//遍历v2,赋值给v1
        p.push_back(*it);
    }
    if(6==p.size())
        return 2;
    else
        return -2;
}

int  CircleLocate::verifyCircles()
{
    if(areas.size())
    {
    double before=areas[0];
    double after=0;
    double last=areas[areas.size()-1];
    int i=1;
    for(;i<areas.size()-1;i++)
    {
        after=areas[i];
        if(before>0 && ((after/before)>0.75) && ((after/before)<1.25))
        {
            before=after;
            continue;
        }
        areas.erase(areas.begin()+i-1);
    }
    if(after>0 && (last/after)<0.95 || (last/after)>1.05)
        areas.erase(areas.begin()+i-1);
    return 1;
    }

    return 0;

}
