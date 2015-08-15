
#include "myfgdetector.h"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/legacy/blobtrack.hpp"
#include "opencv2/legacy/legacy.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc_c.h>

#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include <sstream>
#include<vector>
#include<opencv2/opencv.hpp>
#include<cv.h>
#include<map>
//#include"util.h"
#include"read_xml.h"
#include"kmeans.h"
#include"seamlessclone.h"
#include"blob_run.h"
#include<time.h>
/*
//用time()来计时  秒
    time_t timeBegin, timeEnd;
    timeBegin = time(NULL);
    Sleep(1000);
    timeEnd = time(NULL);
    printf("%dn", timeEnd - timeBegin);
  */
int main()
{
    /*
      此处开始从a.txt读取文件  然后生成摘要视频
argv[7]="track=/home/xuefengmiao/test_blob/a.txt";
argv[8]="btavi=b2.avi";
argv[9]="fgavi=f2.avi";
argv[10]="/home/xuefengmiao/test_blob/new_test/people_real.avi
      */
    char* file_path="track=/home/xuefengmiao/test/test/a.txt";
    char* path="/home/xuefengmiao/test/test/a.txt";
    char* video_path="/home/xuefengmiao/test/test/people_real.avi";
    string video_out__path="/home/xuefengmiao/test/test/output.avi";

    //VibeKalman *vk=new VibeKalman();
    time_t blob_start,blob_end;
    blob_start=time(NULL);
    BLOB_run *br=new BLOB_run();
    br->run(file_path,video_path);   //void BLOB_run::run(char* fg,char* track,char *video_name)
    blob_end=time(NULL);
    printf("blob_time=%d\n", blob_end - blob_start);


    time_t read_xml_start,read_xml_end;
    read_xml_start=time(NULL);
    Read_Xml *rx=new Read_Xml();

//    char* path="/home/xuefengmiao/test_blob/new_test/a.txt";
//    string video_path="/home/xuefengmiao/test_blob/new_test/people_real.avi";
//    string video_out__path="/home/xuefengmiao/test_blob/new_test/output.avi";

    time_t map_xml_start,map_xml_end;
    map_xml_start=time(NULL);
    vector<vector<string> > frames=rx->map_xml(path);//得到所有的轨迹的集合
    map_xml_end=time(NULL);
    printf("map_xml_time=%d\n",map_xml_end-map_xml_start);
    //rx->Show_Xml(frames);//显示所有的轨迹


   Util *ul=new Util();
   vector<FPoint>  ft;
   ft=ul->convert_frames_points(frames);    //把目标的起始帧和坐标取出来
   //ul->Show_FPoint(ft);  //显示这些坐标
   vector<Tuple> tp;
   tp=ul->convert_FPoint_tuple(ft);
  // ul->Show_Tuple(tp);


   time_t kmeans_start,kmeans_end;
   kmeans_start=time(NULL);
   Kmeans *ks=new Kmeans();

   vector<Tuple> clusters[7];
   double dis[7]; //此处保存的是所有的K对应的取值
   double distance=0;
   int k=2;//簇个数的起点
   int m=k;//保存数组的下标
   for(;k<8;k++)
   {
       ks->KMeans(tp,k,clusters);
       for(int m=0;m<k;m++)
       {
          double temp=ks->D_max(clusters[m]);
          distance=distance>temp?distance:temp;
       }
       dis[k-m]=distance;
       //cout<<"distance==="<<distance<<endl;
       distance=0;
       //ks->Show_Point(clusters,k);
   }

   for(int j=0;j<k-m;j++)
       cout<<dis[j]<<"->";
       cout<<endl;

   //调用函数 得到最合适的K值
   int K_final=ul->k_real(dis,m,k-m);
   //cout<<"K_final="<<K_final<<endl;

   //根据最终的K值得到最好的簇
   ks->KMeans(tp,K_final,clusters);
   kmeans_end=time(NULL);
   printf("kmeans_time=%d\n",kmeans_end-kmeans_start);

   cout<<"here runing---"<<endl;
   cout<<"K_final="<<K_final<<endl;
   //根据得到的分类还原到FPoint中  这样通过帧号和起点坐标唯一确定目标
   vector<FPoint> after_fp[7];
   ul->convert_tuple_fpoint(clusters,K_final,ft,after_fp);
   //ul->Show_after_FPoints(after_fp,K_final);

   /*
    *把对应位置的图片存到相应的vector中  然后就可以贴在前景物体上面
    */
   //定义一个vector<Mat>[7]用于保存所有的图片数据
   //vector<vector<string> > frames=rx->map_xml(path);//得到所有的轨迹的集合
  vector<vector<string> > vm[K_final];
  ul->convert_fpoint_vector(frames,vm,K_final,after_fp);
  //ul->Show_convert_fpoint_vector(vm,K_final);

  cout<<"convert_fpoint_vector---OK"<<endl;

   /*
     *把对应的轨迹坐标转化为图片
     */
//   vector<Point> points[K_final];
//   vector<Mat> mats[K_final];
  time_t  zuobiao_start,zuobiao_end;
  zuobiao_start=time(NULL);
   vector<vector<Point> >  points;
   vector<vector<Mat> > mats;
   ul->convert_zuobiao_rect(vm, points,mats,video_path,K_final);
   //rx->Show_Xml(frames);//显示所有的轨迹
   cout<<"convert_zuobiao_rect---OK"<<endl;
   zuobiao_end=time(NULL);
   printf("zuobiao_time=%d\n",zuobiao_end-zuobiao_start);

   time_t possion_start, possion_end;
   possion_start=time(NULL);
   ul->possion_edit_output(video_path,video_out__path,points,mats,K_final);
   cout<<"possion_edit_output---OK"<<endl;
   possion_end=time(NULL);
   printf("possion_time=%d\n",possion_end-possion_start);


    return 0;
}/* main */



