#ifndef KMEANS_H
#define KMEANS_H

#endif // KMEANS_H


#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include<stdlib.h>
#include"util.h"
//#define k 2
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;



////存放元组的属性信息
//struct Tuple{
//    float attr1;
//    float attr2;
//};




class Kmeans{
     public:

    float getDistXY(Tuple t1, Tuple t2);
    int clusterOfTuple(Tuple means[],Tuple tuple,int k);
    float getVar(vector<Tuple> clusters[],Tuple means[],int k);
    Tuple getMeans(vector<Tuple> cluster);
    void KMeans(vector<Tuple> tuples,int k,vector<Tuple> clusters[]);
    //void KMeans(vector<Tuple> tuples,int k);

    void Show_Point(vector<Tuple> clusters[],int k);

    /*
      *用于计算类簇的直径
      *tp:传入某类的集合
      *返回值：类簇内任意两点之间的最大距离
      */
    double D_max(vector<Tuple> tp);
};
