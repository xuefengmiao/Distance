#ifndef READ_XML_H
#define READ_XML_H

#endif // READ_XML_H

#include<iostream>
#include<vector>
#include<stdio.h>
#include<map>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
class Read_Xml{

    public:
    Read_Xml();
    vector<vector<string> > map_xml(char* path);//读取轨迹文件信息
    void Show_Xml(vector<vector<string> > frame);  //遍历显示结果
};
