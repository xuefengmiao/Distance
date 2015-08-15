#include"RectLocate.h"
#include"def.h"
#include<time.h>
#include<stdio.h>
#include"kmeans.h"
using namespace std;
using namespace cv;



int main()
{
    /*
//    for(int i=72;i<=82;i++)
//    {
//        stringstream path;
//        path<<"/home/xuefengmiao/jpg/test";
//        path<<i;
//        path<<".jpg";
//        cout<<path.str()<<endl;
//        Mat src=imread(path.str());
//        if(src.data)
//            cout<<"image read right"<<endl;
//        //对象初始化
//        CircleLocate cl;
//        //定位圆形中心
//        int return_locate=cl.circleLocate(src);
//        if(return_locate)
//            cout<<"CIRCLELOCATE_SUCCESS"<<endl;
//        else
//            cout<<"CIRCLELOCATE_FAILURE"<<endl;
//        cl.showImage();
//        //获取质心
//        vector<Point2f> points;
//        cl.getPoints(points);
//        if(points.size())
//            cout<<"GET_POINTS_SUCCESS"<<endl;
//        else
//            cout<<"GET_POINTS_FAILURE"<<endl;
//    }

*/

    Mat src=imread("/home/xuefengmiao/jpg/test34.jpg");
    CircleLocate cl;
    //定位圆形中心
    int return_locate=cl.circleLocate(src);
    if(return_locate)
        cout<<"CIRCLELOCATE_SUCCESS"<<endl;
    else
        cout<<"CIRCLELOCATE_FAILURE"<<endl;

    //显示图片  参数为显示的时间  单位是秒
    cl.showImage(1);
    //获取质心
    vector<Point2f> points;
    cl.getPoints(points);
    if(points.size())
        cout<<"GET_POINTS_SUCCESS"<<endl;
    else
        cout<<"GET_POINTS_FAILURE"<<endl;


    /*
      tuples是kmeans算法得到的六个质心的集合
      point1 point2 point3 point4 point5 point6用来存储上面的6个质心
      tuple1 tuple2 tuple3 tuple4 tuple5 tuple6用来保存6个检测到的质心  转换为kmean算法需要的数据结构
      */
    vector<Tuple> tuples;
    Tuple tuple1;
    Tuple tuple2;
    Tuple tuple3;
    Tuple tuple4;
    Tuple tuple5;
    Tuple tuple6;
    Point point1=points[0];
    Point point2=points[1];
    Point point3=points[2];
    Point point4=points[3];
    Point point5=points[4];
    Point point6=points[5];


    tuple1.attr1=point1.x;
    tuple1.attr2=point1.y;
    tuples.push_back(tuple1);
    tuple2.attr1=point2.x;
    tuple2.attr2=point2.y;
    tuples.push_back(tuple2);
    tuple3.attr1=point3.x;
    tuple3.attr2=point3.y;
    tuples.push_back(tuple3);
    tuple4.attr1=point4.x;
    tuple4.attr2=point4.y;
    tuples.push_back(tuple4);
    tuple5.attr1=point5.x;
    tuple5.attr2=point5.y;
    tuples.push_back(tuple5);
    tuple6.attr1=point6.x;
    tuple6.attr2=point6.y;
    tuples.push_back(tuple6);


    /*
    vector<Tuple> clusters[2]  保存的就是二个簇的分组信息
      运行完下面的语句就可以得到二个分组
      */
    vector<Tuple> clusters[2];
    Kmeans ks;
    //调用kmeans算法得到二个簇  保存在clusters中
    ks.KMeans(tuples,2,clusters);

    //取出第一个簇
    vector<Tuple> cluster1=clusters[0];
    //取出第二个簇
    vector<Tuple> cluster2=clusters[1];



    /*
      下面的代码是我的测试代码，主要是为了显示分簇之后的效果，在原图上面用不同颜色的圆形进行显示
      其中圆形的中心是检测得到的标准质心，半径是我随便指定的
      */
    //显示第一个簇到图片上面
    if(4==cluster1.size())
    {
        Point p1_1;
        Point p2_1;
        Point p3_1;
        Point p4_1;

        Tuple t1_1=cluster1[0];
        Tuple t2_1=cluster1[1];
        Tuple t3_1=cluster1[2];
        Tuple t4_1=cluster1[3];

        p1_1.x=t1_1.attr1;
        p1_1.y=t1_1.attr2;
        p2_1.x=t2_1.attr1;
        p2_1.y=t2_1.attr2;
        p3_1.x=t3_1.attr1;
        p3_1.y=t3_1.attr2;
        p4_1.x=t4_1.attr1;
        p4_1.y=t4_1.attr2;


        circle(src,p1_1,24,Scalar(0,0,255),2);
        circle(src,p2_1,24,Scalar(0,0,255),2);
        circle(src,p3_1,24,Scalar(0,0,255),2);
        circle(src,p4_1,24,Scalar(0,0,255),2);
    }
    else
    {
        Point p1_1;
        Point p2_1;
        Tuple t1_1=cluster1[0];
        Tuple t2_1=cluster1[1];
        p1_1.x=t1_1.attr1;
        p1_1.y=t1_1.attr2;
        p2_1.x=t2_1.attr1;
        p2_1.y=t2_1.attr2;
        circle(src,p1_1,24,Scalar(0,0,255),2);
        circle(src,p2_1,24,Scalar(0,0,255),2);

    }

    //显示第二个簇到图片上面
    if(4==cluster2.size())
    {
        Point p1_1;
        Point p2_1;
        Point p3_1;
        Point p4_1;

        Tuple t1_1=cluster2[0];
        Tuple t2_1=cluster2[1];
        Tuple t3_1=cluster2[2];
        Tuple t4_1=cluster2[3];

        p1_1.x=t1_1.attr1;
        p1_1.y=t1_1.attr2;
        p2_1.x=t2_1.attr1;
        p2_1.y=t2_1.attr2;
        p3_1.x=t3_1.attr1;
        p3_1.y=t3_1.attr2;
        p4_1.x=t4_1.attr1;
        p4_1.y=t4_1.attr2;


        circle(src,p1_1,24,Scalar(0,255,255),2);
        circle(src,p2_1,24,Scalar(0,255,255),2);
        circle(src,p3_1,24,Scalar(0,255,255),2);
        circle(src,p4_1,24,Scalar(0,255,255),2);
    }
    else
    {
        Point p1_1;
        Point p2_1;
        Tuple t1_1=cluster2[0];
        Tuple t2_1=cluster2[1];
        p1_1.x=t1_1.attr1;
        p1_1.y=t1_1.attr2;
        p2_1.x=t2_1.attr1;
        p2_1.y=t2_1.attr2;
        circle(src,p1_1,24,Scalar(0,255,255),2);
        circle(src,p2_1,24,Scalar(0,255,255),2);

    }

    imshow("src",src);
    waitKey(0);





}

