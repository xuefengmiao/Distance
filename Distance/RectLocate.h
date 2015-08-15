#ifndef RECTLOCATE_H
#define RECTLOCATE_H
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define m_GaussianBlurSize 3
#define TOTAL_CIRCLES 6



class CircleLocate{
private:
    vector<Point2f> points;   //圆形的质心
    Mat after_image;          //保存添加辅助线之后的图
    vector<double> areas;     //所有圆形的面积
    vector<int> radiuss;      //所有圆形的半径
public:
    /*
      定位所有的圆形
      src:输入原始图片
      */
    int circleLocate(Mat src);

    /*
      显示添加完辅助线之后的图片
      */
    void showImage(int time);

    /*获取所有圆形的质心
    参数：vector容器
   */
    int  getPoints(vector<Point2f>& p);
    /*
      验证所有的圆形 保证他们的大小在一个合理的范围之内
      */
    int verifyCircles();
};



#endif // RECTLOCATE_H
