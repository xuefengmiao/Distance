/*
 * DetectionBasedTracker_example.cpp
 *
 * Copyright 2012 RITESH <ritesh@ritsz>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Do anything You want with the code. :)
 */

//------------------------------ INCLUDES ------------------------------------------------

#include "iostream"
#include "opencv/cv.h"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/contrib/detection_based_tracker.hpp"
#include <stdio.h>
#include <QDir>
#include <istream>
#include <cstdlib>
#include <string>
#include <sys/time.h>
#include <string>
#include <sstream>


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <qsqlquery.h>

//------------------------------ NAMESPACES -----------------------------------------------

using namespace cv;
using namespace std;


// 得到数组长度
template <class T>
int getArrayLen(T &array)
{
    return (sizeof(array) / sizeof(array[0]));
}
//int i = getArrayLen(array);    // 一维长度
//int j = getArrayLen(array[0]);// 二维长度





vector< DetectionBasedTracker::Object > faces;      // Object is a pair<Rect,int>.Hence use Object.first for image.
vector<cv::Mat> learnt_face;
vector<int> learnt_label;
cv::Rect_<int> face_i;


CascadeClassifier face_cascade;

//string face_cascade_name = "/home/havstack/miaoxuefeng/haarcascade_frontalface_alt.xml";
string face_cascade_name = "/usr/local/opencv/data/haarcascades/haarcascade_frontalface_alt2.xml";
// string eyes_cascade_name = "/home/xuefengmiao/QT-workspace/temp/haarcascade_eye_tree_eyeglasses.xml";

 string window_name = "Cascade-Delete-Image";
bool pred = false;


 string name[10] = {"gjh", "zjl", "lzx", "mxf","zxy","lzx","zjl","gjh","cqh","zmx"};


 string output_folder = "/home/xuefengmiao/result/result2/";


Ptr<cv::FaceRecognizer> model = cv::createLBPHFaceRecognizer();



void learn(cv::Mat image,int label)
{
    learnt_face.push_back(image);
    learnt_label.push_back(label);

    if(learnt_face.size() >= 100)
    {
        learnt_face.erase(learnt_face.begin());
        learnt_label.erase(learnt_label.begin());
    }
}




//获得系统时间，精确到毫秒
long getCurrentTime()
{
   struct timeval tv;
   gettimeofday(&tv,NULL);
   return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}


void train()
{
    model->train(learnt_face,learnt_label);
}

void update()
{
    model->update(learnt_face,learnt_label);
}



void known();
void  UpdateTrainDataBase();
void  unknown();
void detectAndDisplay( Mat frame,string addr,int label);

//读取文件列表
QFileInfoList GetFileList(QString path)
{
     QDir dir(path);
     QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
     QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

     for(int i = 0; i != folder_list.size(); i++)
     {
          QString name = folder_list.at(i).absoluteFilePath();
          QFileInfoList child_file_list = GetFileList(name);
          file_list.append(child_file_list);
     }

     return file_list;
 }


int main(){

    Ptr<cv::FaceRecognizer> model1 = cv::createLBPHFaceRecognizer(20,65);


    model->load("/home/xuefengmiao/wel-sys-xml/wel_sys_lbphfaces.xml");

    cout<<"Ok"<<endl;


                     QString qstr;
                     std::string str="/home/xuefengmiao/QT-workspace/src/facerec-img/test2/test/";
                     qstr = QString::fromStdString(str);

                     QFileInfoList list=GetFileList(qstr);
                     std::cout << "Reading file is OK ing" << std::endl;



                     cout<<"ok"<<endl;

                     int mm=0;
                     //--读取特定路径下的图片
                          for (int i = 0; i < list.size(); ++i)
                          {
                              mm++;
                              cout<<"before mm="<<mm<<endl;
                              QFileInfo fileInfo = list.at(i);
                              std::string addr="";
                              std::string fileName=fileInfo.fileName().toStdString();
                              std::ostringstream oss1;
                              oss1<<str<<fileName;
                              addr+=oss1.str();
                             // cout<<addr<<endl;
                               Mat frame=imread(addr);

                             if(frame.channels()!=1)
                              cv::cvtColor( frame, frame, CV_BGR2GRAY );

                                 learn(frame,5);

                              //detectAndDisplay(frame,addr,0);
                          }
                          cout<<"before train"<<endl;
                    model->update(learnt_face,learnt_label);
                     cout<<"after train"<<endl;

                     model->update("/home/xuefengmiao/wel-sys-xml/wel_sys_lbphfaces.xml");
                     cout<<"after save"<<endl;


                     cout<<"save succeed!"<<endl;

/*
                    learnt_label.empty();
                    learnt_face.empty();

                    cout<<" learnt_label.clear()="<<learnt_label.size()<<endl;
                    cout<<"learnt_face.empty()="<<learnt_face.size()<<endl;
*/


                  //  learnt_face.clear();
                   // learnt_label.clear();
                    cout<<" learnt_label.clear()="<<learnt_face.size()<<endl;
                    cout<<"learnt_face.empty()="<<learnt_label.size()<<endl;

                    cout<<"here2"<<endl;



                      /*

                     for(int n=mm;n>0;n--)
                     {
                         cout<<"after n="<<n<<endl;
                       learnt_face.pop_back();
                       learnt_label.pop_back();


                       cout<<" learnt_label.clear()="<<learnt_face.size()<<endl;
                       cout<<"learnt_face.empty()="<<learnt_label.size()<<endl;

                     }


*/



                     //model->save("/home/xuefengmiao/wel-sys-xml/wel_sys_lbphfaces.xml");
                     model->save("/home/xuefengmiao/wel-sys-xml/wel_sys_lbphfaces.xml");
                     cout<<"save succeed!"<<endl;



     /*
       break;
}
cv::imshow("Detection Based Tracker",img);      // Show the results.
         waitKey(133);

              }
         }
         */

    return 0;
    }





/** @函数 detectAndDisplay */
void detectAndDisplay( Mat frame,string addr,int label)
{
    //cv::namedWindow(window_name,cv::WINDOW_AUTOSIZE);
   //cout<<"here is running"<<endl;
  std::vector<Rect> faces;
  Mat frame_gray,gray_img,crop_face,crop_face_res;
  cv::Rect_<int> face_i;

  cvtColor( frame, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );
  imshow( window_name,frame);
    waitKey(130);
  //-- 多尺寸检测人脸
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
  //cout<<"faces.size（）==++----======"<<faces.size()<<endl;

  int length=0;
  for( int i = 0; i < faces.size(); i++ )
  {
       //cout<<"here"<<endl;
      //length++;

      rectangle(frame, faces[i], CV_RGB(0, 255,0), 2);
      face_i=faces[i];
         cv::cvtColor(frame,gray_img,CV_RGB2GRAY);
      crop_face = gray_img(face_i);
      cv::resize(crop_face, crop_face_res, Size(100,120), 1.0, 1.0, INTER_CUBIC);
      cv::equalizeHist(crop_face_res,crop_face_res);

      if((!crop_face.empty()))
      {
         // cout<<"Learning"<<endl;
          cv::rectangle(frame, face_i, CV_RGB(255*i, 255*(i-1),255*(i+1)), 1);
          learn(crop_face_res.clone(),label);
     }



      // cout<<"here"<<endl;

      //把用户新上传的图片上传到训练集中

  }
 }





