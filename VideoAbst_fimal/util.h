
#ifndef UTIL_H
#define UTIL_H

#endif // UTIL_H
#include<iostream>
#include<vector>
#include <stdio.h>
#include <stdlib.h>
#include<opencv2/opencv.hpp>
#include"seamlessclone.h"

using namespace customCV;
using namespace cv;
using namespace std;

//存放元组的属性信息  也即起点坐标(attr1,attr2)
struct Tuple{
    float attr1;
    float attr2;
};


//存放元组的属性信息
struct FPoint{
    int frame;  //起始帧
    float x;//起点x坐标
    float y;//起点y坐标
};


class Util{
public:

    /*把所有的物体的信息细化为起点集合 为聚类算法做准备
      *frames:所有运动物体的信息
      *返回值：所有的起点信息
      */
   vector<FPoint> convert_frames_points(vector<vector<string> > frame);

   /*
     *把上面得到的信息转化为起点坐标 作为聚类算法的参数使用
     *fp:vector<FPoint>类型对象
     *返回值：vector<Tuple>
     */
   vector<Tuple>  convert_FPoint_tuple(vector<FPoint> fps);

   /*
     *确定聚类算法的类的个数   K=类簇的半径是指类簇内所有点到类簇中心距离的最大值。
     */


   //显示vector<FPoint>结果
   void Show_FPoint(vector<FPoint> fp);


   //show result of vector<Tuple>
   void Show_Tuple(vector<Tuple> tps);

   /*
    *对各个K值求得的距离值做处理，然后返回最终的K对应的数据
   *dis:距离数组
   *k0:起始坐标
   *length:数组的长度
   *返回值:最终的K值
   */
   int k_real(double dis[],int k0,int length);


   /*
*根据得到的分类还原到FPoint中  这样通过帧号和起点坐标唯一确定目标
     *把tuple类型转化为fpoint
     *clusters：原始簇分类
     *k：簇的个数
     *返回值：fpoint类型
     */
   void convert_tuple_fpoint(vector<Tuple> clusters[],int k,vector<FPoint> fps,vector<FPoint> fp[]);

   /*
     *显示重新分类过后的簇的情况
     *fps:结构体
     */
   void Show_after_FPoints(vector<FPoint> fps[],int kk);

   /*
     *把对应位置的图片存到相应的vector中  然后就可以贴在前景物体上面
     *frames:所有坐标的信息
     *vm:待保存的坐标
     *k:个数
     *after_fp:
     */
      void convert_fpoint_vector(vector<vector<string> > frames,vector<vector<string> > vm[],int k,vector<FPoint> after_fp[]);


      /*
        * 显示分簇过后的所有的坐标信息
        *
        *
        */
      void Show_convert_fpoint_vector(vector<vector<string> > vm[],int k);


      /*
        *把对应的轨迹坐标转化为图片和中点坐标
        *vm:聚类之后的数据
        *points:每帧的中点坐标
        *mats:图片
        *path:视频路径
        */
     void convert_zuobiao_rect(vector<vector<string> > vm[],vector<vector<Point> >  &points,vector<vector<Mat> > &mats,string path,int k);



       /*运用泊松融合粘前景和背景
         *video_path:要摘要的视频源
         *video_out__path:摘要后的视频
         *points:质点集合
         *mats:roi集合
         *k:聚类的数目
         */
     void  possion_edit_output(string video_path,string video_out__path,vector<vector<Point> >  points,vector<vector<Mat> > mats,int k);
};



