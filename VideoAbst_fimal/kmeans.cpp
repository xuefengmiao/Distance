#include"kmeans.h"



////存放元组的属性信息
//struct Tuple{
//    float attr1;
//    float attr2;
//};

//计算两个元组间的欧几里距离
float Kmeans::getDistXY(Tuple t1, Tuple t2)
{
    return sqrt((t1.attr1 - t2.attr1) * (t1.attr1 - t2.attr1) + (t1.attr2 - t2.attr2) * (t1.attr2 - t2.attr2));
}

//根据质心，决定当前元组属于哪个簇
int Kmeans::clusterOfTuple(Tuple means[],Tuple tuple,int k){
    float dist=getDistXY(means[0],tuple);
    float tmp;
    int label=0;//标示属于哪一个簇
    for(int i=1;i<k;i++){
        tmp=getDistXY(means[i],tuple);
        if(tmp<dist) {dist=tmp;label=i;}
    }
    return label;
}
//获得给定簇集的平方误差
float Kmeans::getVar(vector<Tuple> clusters[],Tuple means[],int k){
    float var = 0;
    for (int i = 0; i < k; i++)
    {
        vector<Tuple> t = clusters[i];
        for (int j = 0; j< t.size(); j++)
        {
            var += getDistXY(t[j],means[i]);
        }
    }
    //cout<<"sum:"<<sum<<endl;
    return var;

}
//获得当前簇的均值（质心）
Tuple Kmeans::getMeans(vector<Tuple> cluster){

    int num = cluster.size();
    double meansX = 0, meansY = 0;
    Tuple t;
    for (int i = 0; i < num; i++)
    {
        meansX += cluster[i].attr1;
        meansY += cluster[i].attr2;
    }
    t.attr1 = meansX / num;
    t.attr2 = meansY / num;
    return t;
    //cout<<"sum:"<<sum<<endl;


}
//void Kmeans::KMeans(vector<Tuple> tuples,int k){
void Kmeans::KMeans(vector<Tuple> tuples,int k,vector<Tuple> clusters[]){
//    vector<Tuple> clusters[k];
    Tuple means[k];
    int i=0;
    //默认一开始将前K个元组的值作为k个簇的质心（均值）
    for(i=0;i<k;i++){
        means[i].attr1=tuples[i].attr1;
        means[i].attr2=tuples[i].attr2;
    }
    int lable=0;
    //根据默认的质心给簇赋值
    for(i=0;i!=tuples.size();++i){
        lable=clusterOfTuple(means,tuples[i],k);
        clusters[lable].push_back(tuples[i]);
    }
//    //输出刚开始的簇
//    for(lable=0;lable<3;lable++){
//        cout<<"第"<<lable+1<<"个簇："<<endl;
//        vector<Tuple> t = clusters[lable];
//        for (i = 0; i< t.size(); i++)
//        {
//            cout<<"("<<t[i].attr1<<","<<t[i].attr2<<")"<<"   ";
//        }
//        cout<<endl;
//    }
    float oldVar=-1;
    float newVar=getVar(clusters,means,k);
    while(abs(newVar - oldVar) >= 1) //当新旧函数值相差不到1即准则函数值不发生明显变化时，算法终止
    {

        for (i = 0; i < k; i++) //更新每个簇的中心点
        {
            means[i] = getMeans(clusters[i]);
            //cout<<"means["<<i<<"]:"<<means[i].attr1<<"  "<<means[i].attr2<<endl;
        }
        oldVar = newVar;
        newVar = getVar(clusters,means,k); //计算新的准则函数值
        for (i = 0; i < k; i++) //清空每个簇
        {
            clusters[i].clear();
        }
        //根据新的质心获得新的簇
        for(i=0;i!=tuples.size();++i){
            lable=clusterOfTuple(means,tuples[i],k);
            clusters[lable].push_back(tuples[i]);
        }
//        //输出当前的簇
//        for(lable=0;lable<k;lable++){
//            cout<<"第"<<lable+1<<"个簇："<<endl;
//            vector<Tuple> t = clusters[lable];
//            for (i = 0; i< t.size(); i++)
//            {
//                cout<<"("<<t[i].attr1<<","<<t[i].attr2<<")"<<"   ";
//            }
//            cout<<endl;
//        }
    }

}


void Kmeans::Show_Point(vector<Tuple> clusters[],int k)
{
    Mat  image(1000,1000,CV_8UC3,Scalar(0,0,0));
    //输出当前的簇
    int color1=255;
    int color2=255;
    int color3=255;
    int i=0;
    for(int lable=0;lable<k;lable++){
        cout<<"第"<<lable+1<<"个簇："<<endl;
        vector<Tuple> t = clusters[lable];
        for (int i = 0; i< t.size(); i++)
        {
            cout<<"("<<t[i].attr1<<","<<t[i].attr2<<")"<<"   ";
            cv::circle(image,Point(int(t[i].attr1),int(t[i].attr2)),16,Scalar(color1,color2,color3),1);
        }
        cout<<endl;
        color1=color1-50;
        color2=color2-40;
        color3=color3-30;
//        i++;
//        if(i==1)
//            color1=0;
//        if(i==2)
//            color2=0;
    }
    imshow("image",image);
    waitKey(0);
}

double Kmeans::D_max(vector<Tuple> tp)
{
    double max=0;
    for(int i=0;i<tp.size();i++)
        for(int j=1;j<tp.size();j++)
        {
            if(i!=j)
            {
            Tuple out=tp[i];
            Tuple in=tp[j];
            double x1=out.attr1;
            double y1=out.attr2;
            double x2=in.attr1;
            double y2=in.attr2;
            double distance=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
            if(distance>max)
                max=distance;
            }
        }
    return max;
}

