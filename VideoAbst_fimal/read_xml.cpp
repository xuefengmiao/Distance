#include"read_xml.h"


Read_Xml::Read_Xml(){}


vector<vector<string> > Read_Xml::map_xml(char* path){

    FILE *fp;
    if(NULL == (fp = fopen(path, "r")))
    {
        printf("error\n");
        exit(1);
    }

    std::stringstream ss;   //字符存储
    std::stringstream last_word;
    vector<string> vec;   //记录每个单词
    vector<vector<string> > frame;    //记录每帧的所有的信息

    char first;   //逐个取字符

    while(EOF != (first=fgetc(fp)))
    {
        if(first==',')   //字符串之间区分
        {
            vec.push_back(ss.str());
            ss.str("");
            last_word.str("");
            continue;
        }
       if(first!=' ')   //判断是否为空
        {
        ss<<first;
        last_word<<first;
        }


       if(first=='\n')    //判断是否换行
         {
            vec.push_back(ss.str());
            ss.str("");
            frame.push_back(vec);
            vec.clear();
        }
       if(first=='-' || first==' ')
           continue;
    }
    fclose(fp);


//    //把最后一个单词放入vector中
//    vector<string> add;
//    add=frame[frame.size()-1];
//   add.push_back(last_word.str());

////   vector<vector<string> >::iterator it=frame.begin();

////   int count_iter=0;
////    while(count_iter<frame.size()-1)  //得到最后一个vector,然后删除，再添加完整的变量
////    {
////        it++;
////        count_iter++;
////    }
////    frame.erase(it);
//    frame.push_back(add);



//    //遍历显示结果
//    vector<string> temp;//保存每帧图片的数据
//    for(int k=0;k<frame.size();k++)
//    {
//        temp=frame[k];
//        for(int m=0;m<temp.size();m++)
//        {
//           cout<<temp[m]<<" ";
//        }
//    }

return frame;
}

void Read_Xml::Show_Xml(vector<vector<string> > frame)
{
    vector<vector<string> > frames=frame;
    //遍历显示结果
    vector<string> temp;//保存每帧图片的数据
    for(int k=0;k<frames.size();k++)
    {
        temp=frames[k];
        for(int m=0;m<temp.size();m++)
        {
           cout<<temp[m]<<" ";
        }
    }
}
