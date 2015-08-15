#include"util.h"
#include<iostream>
#include"seamlessclone.h"
using namespace std;


vector<FPoint>  Util::convert_frames_points(vector<vector<string> > frames)
{
    vector<FPoint> tuples;
    FPoint ft;
   vector<vector<string> > frame=frames;
   vector<vector<string> >::iterator it_frame=frame.begin();
   while(it_frame!=frame.end()){
      vector<string> first_frame=*it_frame;
      vector<string>::iterator it_string=first_frame.begin();
      string str_frame=(*it_string);
      it_string++;
      string str_x=(*it_string);
      it_string++;
      string str_y=(*it_string);
      int int_frame=atoi(str_frame.c_str());
      float float_x=atof(str_x.c_str());
      float float_y=atof(str_y.c_str());
      ft.frame=int_frame;
      ft.x=float_x;
      ft.y=float_y;
      tuples.push_back(ft);
      it_frame++;
   }
 //cout<<"here is OK"<<endl;
    return tuples;
}


void Util::Show_FPoint(vector<FPoint> fp)
{
    //输出当前的簇
    for(int lable=0;lable<fp.size();lable++){
        cout<<"第"<<lable+1<<"个簇："<<endl;
        FPoint t = fp[lable];
        cout<<"("<<t.frame<<","<<t.x<<","<<t.y<<")"<<"   ";
        cout<<endl;
    }
}


vector<Tuple>  Util::convert_FPoint_tuple(vector<FPoint> fps)
{
    vector<Tuple> tuples;
    Tuple tp;
    for(int i=0;i<fps.size();i++)
    {
        FPoint fp=fps[i];
        tp.attr1=fp.x;
        tp.attr2=fp.y;
        tuples.push_back(tp);
    }
    return tuples;
}

void Util::Show_Tuple(vector<Tuple> tps)
{
    //输出当前的簇
    for(int lable=0;lable<tps.size();lable++){
        cout<<"第"<<lable+1<<"个："<<endl;
        Tuple t = tps[lable];
        cout<<"("<<t.attr1<<","<<t.attr2<<")"<<"   ";
        cout<<endl;
    }
}

int Util::k_real(double dis[],int k0,int length)
{
    int K=0;
    double max=0;
    int flag=0;  //记录下标的位置
    for(int i=1;i<length;i++)
    {
        if(abs((dis[i]-dis[i-1]))>max)
        {
            max=abs((dis[i]-dis[i-1]));
            flag=i;
        }
    }
    K=flag+k0;
    return K;
}



void  Util::convert_tuple_fpoint(vector<Tuple> clusters[],int k,vector<FPoint> fps,vector<FPoint> fp[])
{
    //vector<FPoint> fp[k];

    for(int i=0;i<k;i++)
    {
        vector<Tuple> tuple=clusters[i];
        //cout<<"tuple.size()="<<tuple.size()<<endl;
        for(int j=0;j<tuple.size();j++)
        {
            Tuple te=tuple[j];
            for(int t=0;t<fps.size();t++)
            {
                FPoint temp=fps[t];
                if((te.attr1==temp.x) && (te.attr2==temp.y))
                    fp[i].push_back(temp);
            }
        }
    }
    //return fp;
}


void Util::Show_after_FPoints(vector<FPoint> fps[],int kk)
{
 //输出当前的簇
for(int lable=0;lable<kk;lable++){
    cout<<"第"<<lable+1<<"个："<<endl;
    vector<FPoint> tt = fps[lable];
    for(int k=0;k<tt.size();k++){
        FPoint t=tt[k];
    cout<<"("<<t.frame<<","<<t.x<<","<<t.y<<")"<<"   ";
    cout<<endl;
    }
}
}


void Util::convert_fpoint_vector(vector<vector<string> > frame,vector<vector<string> > vm[],int k,vector<FPoint> after_fp[])
{
    for(int i=0;i<k;i++)
    {
        vector<vector<string> >::iterator it_frame=frame.begin();
        vector<FPoint> fps=after_fp[i];
        for(int j=0;j<frame.size();j++)
        {
            FPoint fp=fps[j];
            int frame_fp=fp.frame;
            float x_fp=fp.x;
            float y_fp=fp.y;

            while(it_frame!=frame.end()){
               vector<string> first_frame=*it_frame;
               vector<string>::iterator it_string=first_frame.begin();
               string str_frame=(*it_string);
               it_string++;
               string str_x=(*it_string);
               it_string++;
               string str_y=(*it_string);
               int int_frame=atoi(str_frame.c_str());
               float float_x=atof(str_x.c_str());
               float float_y=atof(str_y.c_str());


               if((frame_fp==int_frame) && (x_fp==float_x) && (y_fp==float_y))
               {
                   vm[i].push_back(first_frame);
                   break;
               }
               it_frame++;

            }

        }
    }
}


void Util::Show_convert_fpoint_vector(vector<vector<string> > vm[],int k)
{
    for(int i=0;i<k;i++)
    {
        vector<vector<string> > vvs=vm[i];
        //cout<<"vvs.size=="<<vvs.size()<<endl;
        vector<vector<string> >::iterator it_string=vvs.begin();
        while(it_string!=vvs.end())
        {
            vector<string> vs=*it_string;
            vector<string>::iterator it=vs.begin();
            while(it!=vs.end())
            {
                string s=*it;
                cout<<s<<" ";
                it++;
            }
        cout<<endl;
        it_string++;
        }
    }
    cout<<endl;
}


void Util::

convert_zuobiao_rect(vector<vector<string> > vm[],vector<vector<Point> >  &points,vector<vector<Mat> > &mats,string path,int k)
{

//    vector<vector<Point> > points;
//    vector<vector<Mat> > mats;
    vector<Point> point; //保存目标的所有的质心
    vector<Mat> mat;   //保存目标的所有的mat和质心一一对应
   for(int i=0;i<k;i++)  //每个簇的组循环
   {
    vector<vector<string> > vvs=vm[i];
    point.clear();
    mat.clear();
    //cout<<"vvs.size="<<vvs.size()<<endl;
    for(int j=0;j<vvs.size();j++)  //簇类每个目标的循环
    {
        vector<string> vs=vvs[j];
        string str_frame=vs[0];
        int frame=atoi(str_frame.c_str()); //目标的起始帧
        //cout<<"frame="<<frame<<endl;
        VideoCapture cap(path);
        int frame_no=0;  //视频中的具体帧
        Mat image;
        while(frame!=frame_no)
        {
            cap.read(image);
            frame_no++;
        }
        //cout<<"frame_no="<<frame_no<<endl;
        cap.read(image);
        //cout<<"here"<<endl;
        for(int m=1;m<vs.size();)  //每个目标在各个帧的轨迹的循环
        {
             vector<int> four_number;
            for(int count_4=0;count_4<4;count_4++) //矩形坐标
            {// cout<<"here2"<<endl;
                string s_value=vs[m];
               int int_value=atoi(s_value.c_str());
               //cout<<int_value<<" ";
               four_number.push_back(int_value);
               m++;
            }
            int x1=four_number[0];
             int y1=four_number[1];
              int x2=four_number[2];
               int y2=four_number[3];
 //cout<<"x1="<<x1<<" y1="<<y1<<" x2="<<x2<<" y2="<<y2<<endl;
               four_number.clear();
               Point p(x1,y1);
               x1=abs(x1-x2/2);
               y1=abs(y1-y2/2);
               //cout<<"four_number.size()="<<four_number.size()<<endl;
            Rect rect(x1,y1,x2,y2);
            //cout<<"x1="<<x1<<" y1="<<y1<<" x2="<<x2<<" y2="<<y2<<endl;
            if((rect.x+rect.width>image.cols))
                {
                  cap.read(image);
                  continue;
               // cout<<"cols change"<<endl;
               // rect.width=abs(image.cols-rect.x);
                }
            if(rect.y+rect.height>image.rows)
            {
                  cap.read(image);
                  continue;
               // cout<<"rows change"<<endl;
               // rect.height=abs(image.rows-rect.y);
            }
//            if(((x1+x2)>image.cols))
//                {
//                cout<<"cols change"<<endl;
//                rect.width=image.cols-x1;
//                }
//            if((y1+y2)>image.rows)
//            {
//                cout<<"rows change"<<endl;
//                rect.height=image.rows-y1;
//            }
             // cout<<"x1="<<x1<<" y1="<<y1<<" rect.x="<<rect.width<<" rect.h="<<rect.height<<endl;
              //roi.x+roi.width<=m.cols
              //roi.y+roi.height<=m.rows
            Mat roi=(image)(rect);
           // cout<<"roi.cols="<<roi.cols<<" roi.rows="<<roi.rows<<endl;
            //rectangle(image,rect,Scalar(0,0,255),2);
            imshow("roi1",roi);
            waitKey(0);
            point.push_back(p);
//            Mat temp;
//            roi.copyTo(temp);
            mat.push_back(roi.clone());
            //imshow("roi2",roi);
            //waitKey(0);
            cap.read(image);
            //imshow("roi2",roi);
            //waitKey(0);
        }
    }
    //保存到每个簇中
    points.push_back(point);
    mats.push_back(mat);

   }



/*
//     vector<vector<Point> > points;
//     vector<vector<Mat> > mats;

//    for(int i=0;i<k;i++)  //每个簇的循环
//    {
//     vector<vector<string> > vvs=vm[i];
//     vector<Point> point; //保存目标的所有的质心
//     vector<Mat> mat;   //保存目标的所有的mat和质心一一对应
//     for(int j=0;j<vvs.size();j++)  //簇类每个目标的循环
//     {
//         vector<string> vs=vvs[j];
//         string str_frame=vs[0];
//         int frame=atoi(str_frame.c_str()); //目标的起始帧
//         cout<<"frame="<<frame<<endl;
//         VideoCapture cap(path);
//         int frame_no=0;  //视频中的具体帧
//         Mat image;
////         while(cap.read(image))
////         {
////             if(frame==frame_no)
////                 break;
////             cap.read(image);
////             frame_no++;
////         }
//         while(frame!=frame_no)
//         {
//             cap.read(image);
//             frame_no++;
//         }
//         cout<<"frame_no="<<frame_no<<endl;
//         cap.read(image);
//         cout<<"here"<<endl;
//         for(int m=1;m<vs.size();)  //每个目标在各个帧的轨迹的循环
//         {
//              vector<int> four_number;
//             for(int count_4=0;count_4<4;count_4++) //矩形坐标
//             {// cout<<"here2"<<endl;
//                 string s_value=vs[m];
//                int int_value=atoi(s_value.c_str());
//                //cout<<int_value<<" ";
//                four_number.push_back(int_value);
//                m++;
//             }
//             //cout<<"here3"<<endl;
//             int x1=four_number[0];
//              int y1=four_number[1];
//               int x2=four_number[2];
//                int y2=four_number[3];
//               //cout<<"x1="<<x1<<"y1="<<y1<<"x2="<<x2<<"y2="<<y2<<endl;
//                 cout<<"x1="<<x1<<" y1="<<y1<<" x2="<<x2<<" y2="<<y2<<endl;
//                Point p(x1,y1);
//                x1=x1-x2/2;
//                y1=y1-y2/2;
//                if(x1<0)
//                    x1=0;
//                if(y1<0)
//                    y1=0;
//             Rect rect(x1,y1,x2,y2);

//             Mat roi=(image)(rect);
//             cout<<"roi.cols="<<roi.cols<<" roi.rows="<<roi.rows<<endl;
//              //cout<<"x1="<<x1<<"y1="<<y1<<"x2="<<x2<<" y2="<<y2<<endl;
//             point.push_back(p);
//             mat.push_back(roi);
//             cap.read(image);
//         }
//     }
//     //保存到每个簇中
//     points.push_back(point);
//     mats.push_back(mat);
//     //points.clear();
//     //mats.clear();
//    }

//    cout<<"points="<<points.size()<<endl;
//    cout<<"mats="<<mats.size()<<endl;
//    /*
//     *vector<vector<Point> > 转化为pointsvector<Point>  p[],vector<Mat> m[]形式
//     */
}


void  Util::possion_edit_output(string video_path,string video_out__path,vector<vector<Point> >  points,vector<vector<Mat> > mats,int k)
{
    vector<Mat>  mat0;
    vector<Point>  point0;
    vector<Mat>  mat1;
    vector<Point> point1;
    vector<Mat>  mat2;
    vector<Point> point2;
    vector<Mat>  mat3;
    vector<Point> point3;
    vector<Mat>  mat4;
    vector<Point> point4;
    vector<Mat>  mat5;
    vector<Point> point5;
    vector<Mat>  mat6;
    vector<Point> point6;


    for(int j=0;j<k;j++)
    {
        if(0==j)
           {
            mat0=mats[0];
            point0=points[0];
          }
        if(1==j)
           {
            mat1=mats[1];
            point1=points[1];
          }
        if(2==j)
           {
            mat2=mats[2];
            point2=points[2];
          }
        if(3==j)
           {
            mat3=mats[3];
            point3=points[3];
          }
        if(4==j)
           {
            mat4=mats[4];
            point4=points[4];
          }
        if(5==j)
           {
            mat5=mats[5];
            point5=points[5];
          }
        if(6==j)
           {
            mat6=mats[6];
            point6=points[6];
          }
    }

    Mat background;
    VideoCapture cap(video_path);
    cap.read(background);
    //Mat src_mask = 255 * Mat::ones(src.rows, src.cols, src.depth());
    int ex = static_cast<int>(cap.get(CV_CAP_PROP_FOURCC));
    char EXT[] = {ex & 0XFF , (ex & 0XFF00) >> 8,(ex & 0XFF0000) >> 16,(ex & 0XFF000000) >> 24, 0}; //ʲô
    cv::Size S = cv::Size((int)cap.get(CV_CAP_PROP_FRAME_WIDTH),(int)cap.get(CV_CAP_PROP_FRAME_HEIGHT));
    cv::VideoWriter cap_write;//写入视频
    cap_write.open(video_out__path , ex, 25,S, true); //打开写入文件并指定格式


    vector<Mat>::iterator it0=mat0.begin();
    vector<Mat>::iterator it1=mat1.begin();
    vector<Mat>::iterator it2=mat2.begin();
    vector<Mat>::iterator it3=mat3.begin();
    vector<Mat>::iterator it4=mat4.begin();
    vector<Mat>::iterator it5=mat5.begin();
    vector<Mat>::iterator it6=mat6.begin();
    vector<Mat>::iterator end0=mat0.end();
    vector<Mat>::iterator end1=mat1.end();
    vector<Mat>::iterator end2=mat2.end();
    vector<Mat>::iterator end3=mat3.end();
    vector<Mat>::iterator end4=mat4.end();
    vector<Mat>::iterator end5=mat5.end();
    vector<Mat>::iterator end6=mat6.end();

    vector<Point>::iterator p_it0=point0.begin();
    vector<Point>::iterator p_it1=point1.begin();
    vector<Point>::iterator p_it2=point2.begin();
    vector<Point>::iterator p_it3=point3.begin();
    vector<Point>::iterator p_it4=point4.begin();
    vector<Point>::iterator p_it5=point5.begin();
    vector<Point>::iterator p_it6=point6.begin();
    vector<Point>::iterator p_end0=point0.end();
    vector<Point>::iterator p_end1=point1.end();
    vector<Point>::iterator p_end2=point2.end();
    vector<Point>::iterator p_end3=point3.end();
    vector<Point>::iterator p_end4=point4.end();
    vector<Point>::iterator p_end5=point5.end();
    vector<Point>::iterator p_end6=point6.end();

    //while( (it0!=end0)|| (it1!=end1)|| (it2!=end2)|| (it3!=end3)|| (it4!=end4)|| (it5!=end5)|| (it6!=end6))
    while(1)
    {
        if((it0==end0)&& (it1==end1)&& (it2==end2)&& (it3==end3)&& (it4==end4)&& (it5==end5) && (it6==end6))
        {
            break;
        }
        Mat image;
        background.copyTo(image);
        //cout<<"here  !!!"<<endl;

        /*
          addWeighted()函数的第1个参数为输入图片1，第2个参数为图片1的系数，参数3为输入图片2，参数4为图片2的系数。其实这2个系数之和没有必要为1，
      我这里在程序中定为1是防止图片出现过饱和等情况。参数5为混合后图片的深度，如果图片1和图片2深度相同的话，则该参数为-1. 最后1个参数为输出混合图片结果保存处。
          */
         if(it0!=end0)
         {
             //cout<<"seamless   0  start--------"<<endl;
             Mat roi0=*it0;
             Point p0=*p_it0;
             p_it0++;
             Mat src_mask = 255 * Mat::ones(roi0.rows, roi0.cols, roi0.depth());
             it0++;
             //质心溢出
             if(p0.y<roi0.rows/2+1)
             {
                 continue;
                 //p0.y=roi0.rows/2+1;
                // cout<<"here1"<<endl;
             }
             if(p0.x<roi0.cols/2+1)
             {
                 continue;
                 //p0.x=roi0.cols/2+1;
                 //cout<<"here2"<<endl;
             }
             //图片溢出
             if(p0.x+roi0.cols>image.cols)
             {
                 continue;
                 //p0.x=image.cols-roi0.cols;
             }
             if(p0.y+roi0.rows>image.rows)
             {
                 continue;
                //p0.y=image.rows-roi0.rows;
             }

             Mat imageROI;
             imageROI=image(Rect(abs(p0.x-0.5*roi0.cols),abs(p0.y-0.5*roi0.rows),roi0.cols,roi0.rows));
             //roi0.copyTo(imageROI);
             addWeighted(roi0,0.5,imageROI,0.5,0,imageROI);
             //seamlessClone(roi0, image, src_mask, p0, image, 2);
             //addWeighted(roi0,0.5,image,0.5,0,image);
             //cout<<"seamless   0   end-------- "<<endl;
         }
         if(it1!=end1)
         {
             //cout<<"seamless   1  start--------"<<endl;
             Mat roi1=*it1;
             Point p1=*p_it1;
             p_it1++;
             Mat src_mask = 255 * Mat::ones(roi1.rows, roi1.cols, roi1.depth());
             it1++;
             if(p1.y<roi1.rows/2+1)
             {
                 continue;
                 //p1.y=roi1.rows/2+1;
                // cout<<"here1"<<endl;
             }
             if(p1.x<roi1.cols/2+1)
             {
                 continue;
                 //p1.x=roi1.cols/2+1;
                 //cout<<"here2"<<endl;
             }
             //图片溢出
             if(p1.x+roi1.cols>image.cols)
             {
                 continue;
                 //p1.x=image.cols-roi1.cols;
             }
             if(p1.y+roi1.rows>image.rows)
             {
                 continue;
                //p1.y=image.rows-roi1.rows;
             }
             Mat imageROI;
             imageROI=image(Rect(abs(p1.x-0.5*roi1.cols),abs(p1.y-0.5*roi1.rows),roi1.cols,roi1.rows));
             //roi1.copyTo(imageROI);
             //seamlessClone(roi1, image, src_mask, p1, image, 2);
             addWeighted(roi1,0.5,imageROI,0.5,0,imageROI);
             //cout<<"seamless 1   end--------"<<endl;
         }
         if(it2!=end2)
         {
             //cout<<"seamless   2  start--------"<<endl;
             Mat roi2=*it2;
             Point p2=*p_it2;
             p_it2++;
             Mat src_mask = 255 * Mat::ones(roi2.rows, roi2.cols, roi2.depth());
             it2++;
             if(p2.y<roi2.rows/2+1)
             {
                 continue;
                 //p2.y=roi2.rows/2+1;
                // cout<<"here1"<<endl;
             }
             if(p2.x<roi2.cols/2+1)
             {
                 continue;
                 //p2.x=roi2.cols/2+1;
                 //cout<<"here2"<<endl;
             }

//             if(((x1+x2)>image.cols))
//                 rect.width=image.cols-x1-1;
//             if((y1+y2)>image.rows)
//                 rect.height=image.rows-y1-1;
             //图片溢出
             if(p2.x+roi2.cols>image.cols)
             {
                 continue;
                 //p2.x=image.cols-roi2.cols;
             }
             if(p2.y+roi2.rows>image.rows)
             {
                 continue;
                //p2.y=image.rows-roi2.rows;
             }
             Mat imageROI;
             imageROI=image(Rect(abs(p2.x-0.5*roi2.cols),abs(p2.y-0.5*roi2.rows),roi2.cols,roi2.rows));
             //roi2.copyTo(imageROI);
             //seamlessClone(roi2, image, src_mask, p2, image, 2);
             addWeighted(roi2,0.5,imageROI,0.5,0,imageROI);
             //cout<<"seamless     2   end--------" <<endl;
         }
         if(it3!=end3)
         {
             //cout<<"seamless   3  start--------"<<endl;
             Mat roi3=*it3;
             Point p3=*p_it3;
             p_it3++;
             //cout<<"p3.x="<<p3.x<<" p3.y="<<p3.y<<endl;
             Mat src_mask = 255 * Mat::ones(roi3.rows, roi3.cols, roi3.depth());
             it3++;
             if(p3.y<roi3.rows/2+1)
             {
                 continue;
                 //p3.y=roi3.rows/2+1;
                // cout<<"here1"<<endl;
             }
             if(p3.x<roi3.cols/2+1)
             {
                 continue;
                 //p3.x=roi3.cols/2+1;
                 //cout<<"here2"<<endl;
             }
             //图片溢出
             if(p3.x+roi3.cols>image.cols)
             {
                 continue;
                 //p3.x=image.cols-roi3.cols;
             }
             if(p3.y+roi3.rows>image.rows)
             {
                 continue;
                //p3.y=image.rows-roi3.rows;
             }
             Mat imageROI;
             imageROI=image(Rect(abs(p3.x-0.5*roi3.cols),abs(p3.y-0.5*roi3.rows),roi3.cols,roi3.rows));
             //roi3.copyTo(imageROI);
             //seamlessClone(roi3, image, src_mask, p3, image, 2);
             addWeighted(roi3,0.5,imageROI,0.5,0,imageROI);
             //cout<<"seamless     3   end--------"<<endl;
         }
         if(it4!=end4)
         {
             //cout<<"seamless   4  start--------"<<endl;
             Mat roi4=*it4;
             Point p4=*p_it4;
             p_it4++;
             //cout<<"p4.x="<<p4.x<<" p4.y="<<p4.y<<endl;
             imwrite("/home/xuefengmiao/test_blob/miao.jpg",roi4);
             Mat src_mask = 255 * Mat::ones(roi4.rows, roi4.cols, roi4.depth());
             it4++;
             if(p4.y<roi4.rows/2+1)
             {
                 continue;
                 //p4.y=roi4.rows/2+1;
                // cout<<"here1"<<endl;
             }
             if(p4.x<roi4.cols/2+1)
             {
                 continue;
                 //p4.x=roi4.cols/2+1;
                 //cout<<"here2"<<endl;
             }
             //图片溢出
             if(p4.x+roi4.cols>image.cols)
             {
                 continue;
                 //p4.x=image.cols-roi4.cols;
             }
             if(p4.y+roi4.rows>image.rows)
             {
                 continue;
                //p4.y=image.rows-roi4.rows;
             }
             Mat imageROI;
             imageROI=image(Rect(abs(p4.x-0.5*roi4.cols),abs(p4.y-0.5*roi4.rows),roi4.cols,roi4.rows));
             //roi4.copyTo(imageROI);
             //seamlessClone(roi4, image, src_mask, p4, image, 2);
             addWeighted(roi4,0.5,imageROI,0.5,0,imageROI);
             //cout<<"seamless   4    end--------"<<endl;
         }
         if(it5!=end5)
         {
             //cout<<"seamless   5  start--------"<<endl;
             Mat roi5=*it5;
             Point p5=*p_it5;
             p_it5++;
             Mat src_mask = 255 * Mat::ones(roi5.rows, roi5.cols, roi5.depth());
             it5++;
             if(p5.y<roi5.rows/2+1)
             {
                 continue;
                 //p5.y=roi5.rows/2+1;
                // cout<<"here1"<<endl;
             }
             if(p5.x<=roi5.cols/2+1)
             {
                 continue;
                 //p5.x=roi5.cols/2+1;
                 //cout<<"here2"<<endl;
             }
             //图片溢出
             if(p5.x+roi5.cols>image.cols)
             {
                 continue;
                 //p5.x=image.cols-roi5.cols;
             }
             if(p5.y+roi5.rows>image.rows)
             {
                 continue;
                //p5.y=image.rows-roi5.rows;
             }
             Mat imageROI;
             imageROI=image(Rect(abs(p5.x-0.5*roi5.cols),abs(p5.y-0.5*roi5.rows),roi5.cols,roi5.rows));
             //roi5.copyTo(imageROI);
             //seamlessClone(roi5, image, src_mask, p5, image, 2);
             addWeighted(roi5,0.5,imageROI,0.5,0,imageROI);
             //cout<<"seamless    5    end--------"<<endl;
         }
         if(it6!=end6)
         {
             //cout<<"seamless   6  start--------"<<endl;
             Mat roi6=*it6;
             Point p6=*p_it6;
             p_it6++;
             Mat src_mask = 255 * Mat::ones(roi6.rows, roi6.cols, roi6.depth());
             it6++;
             if(p6.y<roi6.rows/2+1)
             {
                 continue;
                 //p6.y=roi6.rows/2+1;
                // cout<<"here1"<<endl;
             }
             if(p6.x<roi6.cols/2+1)
             {
                 continue;
                 //p6.x=roi6.cols/2+1;
                 //cout<<"here2"<<endl;
             }
             //图片溢出
             if(p6.x+roi6.cols>image.cols)
             {
                 continue;
                 //p6.x=image.cols-roi6.cols;
             }
             if(p6.y+roi6.rows>image.rows)
             {
                 continue;
                //p6.y=image.rows-roi6.rows;
             }
             Mat imageROI;
             imageROI=image(Rect(abs(p6.x-0.5*roi6.cols),abs(p6.y-0.5*roi6.rows),roi6.cols,roi6.rows));
             //roi6.copyTo(imageROI);
             //seamlessClone(roi6, image, src_mask, p6, image, 2);
             addWeighted(roi6,0.5,imageROI,0.5,0,imageROI);
             //cout<<"seamless    6    end--------"<<endl;
         }
//         imshow("image",image);
//         waitKey(10);
//         Mat write;
//         image.copyTo(write);
         if((it0!=end0)|| (it1!=end1)|| (it2!=end2)|| (it3!=end3)|| (it4!=end4)|| (it5!=end5)|| (it6!=end6))
         {
         cap_write<<image;
         }
    }

//    int count=0;
//         while(count<200)
//         {
//            cap.read(src);
//           cap_write<<src;
//           count++;
//         }

   /*
     Mat src = imread("/home/xuefengmiao/Images/birds.jpg");
     Mat dst = imread("/home/xuefengmiao/Images/moon.jpg");
     // Create an all white mask
     Mat src_mask = 255 * Mat::ones(src.rows, src.cols, src.depth());
     // The location of the center of the src in the dst
     Point center(5*dst.cols/7,2*dst.rows/9);

     // Seamlessly clone src into dst and put the results in output
     Mat normal_clone;
     Mat mixed_clone;

     circle(src,center,3,Scalar(255,255,0),-1);

     seamlessClone(src, dst, src_mask, center, normal_clone, 1);
     seamlessClone(src, dst, src_mask, center, mixed_clone, 2);
     circle(normal_clone,center,10,Scalar(255,255,0),-1);
     // Save results
 //    imwrite("images/opencv-normal-clone-example.jpg", normal_clone);
 //    imwrite("images/opencv-mixed-clone-example.jpg", mixed_clone);
     imshow("normal_clone",normal_clone);
     imshow("mixed_clone",mixed_clone);
     waitKey(0);*/

}

