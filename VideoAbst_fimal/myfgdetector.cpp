
#include "myfgdetector.h"
//#include"vibe.h"
MyFGDetector::MyFGDetector()
{
  this->Create(0.003, 60.0);
}

MyFGDetector::MyFGDetector(double alpha, double threshold)
{
  this->Create(alpha, threshold);
}

MyFGDetector::~MyFGDetector()
{
  this->Release();
}

void MyFGDetector::Create(double alpha, double threshold)
{
  m_framecount = 0;
  m_alpha = alpha;
  m_threshold = threshold;

  m_pFrame=0;
  m_pFGMask=0;

  m_pFrameMat=0;
  m_pFGMat=0;
  m_pBkMat=0;
  vibeModel* vbM = NULL;
}


IplImage* MyFGDetector::GetMask()
{
  return m_pFGMask;
}

void MyFGDetector::Release()
{
  m_framecount = 0;

  if(m_pFrame) cvReleaseImage(&m_pFrame);
  if(m_pFGMask) cvReleaseImage(&m_pFGMask);

  if(m_pFrameMat) cvReleaseMat(&m_pFrameMat);
  if(m_pFGMat) cvReleaseMat(&m_pFGMat);
  if(m_pBkMat) cvReleaseMat(&m_pBkMat);

}


void MyFGDetector::Process(IplImage* pFrame)
{
        int width = pFrame->width;
        int height = pFrame->height;
        int nChannels = pFrame->nChannels;
        unsigned char*  image_data = NULL;
        image_data = (unsigned char *) pFrame->imageData;

        unsigned char*  output_data = NULL; // image data after background subtraction

  if(m_framecount==0)
    {
      m_pFGMask = cvCreateImage(cvSize(pFrame->width, pFrame->height),  IPL_DEPTH_8U,1);

      m_pBkMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
      m_pFGMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
      m_pFrameMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);

      if( !m_pFGMask || !m_pBkMat || !m_pFGMat || !m_pFrameMat)
    {
      fprintf(stderr, "Can not alloc memeory.\n");
      return ;
    }

      //convert to single channel
      cvCvtColor(pFrame, m_pFGMask, CV_BGR2GRAY);

      cvConvert(m_pFGMask, m_pFrameMat);
      cvConvert(m_pFGMask, m_pFGMat);
      cvConvert(m_pFGMask, m_pBkMat);
      vbM = VibeModelInit(width, height, nChannels, image_data);
    }
 else
  {
      cvCvtColor(pFrame,m_pFGMask,CV_BGR2GRAY);
      cvConvert(m_pFGMask,m_pFrameMat);
//      cvSmooth(m_pFrameMat, m_pFrameMat, CV_GAUSSIAN, 3, 0, 0);
//      cvThreshold(m_pFGMat, m_pFGMask, m_threshold, 255.0, CV_THRESH_BINARY);
//      cvErode(m_pFGMask, m_pFGMask, 0, 1);
//      cvDilate(m_pFGMask, m_pFGMask, 0, 1);


      output_data = (unsigned char *) malloc (width * height * nChannels);
      VibeModelUpdate(vbM, image_data, output_data);
      IplImage *foreground = cvCreateImage(cvGetSize(pFrame), pFrame->depth, 1);
      foreground->imageData = (char *) output_data;
      cvMorphologyEx(foreground, foreground, 0, 0, CV_MOP_CLOSE, 1);
      cvMorphologyEx(foreground, foreground, 0, 0, CV_MOP_OPEN, 1);
      cvConvert(foreground,m_pBkMat);


      cvConvert(m_pBkMat,m_pFGMat);
      cvConvert(m_pFGMat,m_pFGMask);

      //update(m_pFrameMat,m_pBkMat,rng,m_framecount);//更新背景

  }
/*
    //创建一个随机数生成器
    RNG rng(0xFFFFFFFF);

  if(m_framecount==0)
    {
      m_pFGMask = cvCreateImage(cvSize(pFrame->width, pFrame->height),  IPL_DEPTH_8U,1);

      m_pBkMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
      m_pFGMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
      m_pFrameMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);

      if( !m_pFGMask || !m_pBkMat || !m_pFGMat || !m_pFrameMat)
    {
      fprintf(stderr, "Can not alloc memeory.\n");
      return ;
    }

      //convert to single channel
      cvCvtColor(pFrame, m_pFGMask, CV_BGR2GRAY);

      cvConvert(m_pFGMask, m_pFrameMat);
      cvConvert(m_pFGMask, m_pFGMat);
      cvConvert(m_pFGMask, m_pBkMat);
      Initialize(m_pFrameMat,rng);
    }
 else
  {
      cvCvtColor(pFrame,m_pFGMask,CV_BGR2GRAY);
      cvConvert(m_pFGMask,m_pFrameMat);
      cvConvert(m_pFGMask,m_pFGMat);

      cvSmooth(m_pFrameMat, m_pFrameMat, CV_GAUSSIAN, 3, 0, 0);
      //cvAbsDiff(m_pFrameMat, m_pBkMat, m_pFGMat);
      cvThreshold(m_pFGMat, m_pFGMask, m_threshold, 255.0, CV_THRESH_BINARY);
      cvErode(m_pFGMask, m_pFGMask, 0, 1);
      cvDilate(m_pFGMask, m_pFGMask, 0, 1);

      update(m_pFrameMat,m_pBkMat,rng,m_framecount);//更新背景
      cvConvert(m_pBkMat,m_pFGMat);
      cvConvert(m_pFGMat,m_pFGMask);
  }
*/
  /*
  IplImage* m_pFrame;
  IplImage* m_pFGMask;

  CvMat* m_pFrameMat;
  CvMat* m_pFGMat;
  CvMat* m_pBkMat;

    * add vibe
    IplImage* pFrame=NULL;CvMat* pFrameMat = NULL;//pFrame对象
    IplImage* pAfter=NULL;CvMat* pAfterMat=NULL;//保存pFrame对应的灰度图像
    IplImage* segMap=NULL;CvMat* segMat=NULL;//保存处理后的信息
    */
//  if(m_framecount==1){
////      segMap = cvCreateImage(cvSize(pFrame->width, pFrame->height),
////          IPL_DEPTH_8U,1);
////      segMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
////      pAfter=cvCreateImage(cvSize(pFrame->width, pFrame->height),
////          IPL_DEPTH_8U,1);
////      pAfterMat=cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
//      //转化成单通道图像再处理
//      cvCvtColor(pFrame, m_pFGMask, CV_BGR2GRAY);
//      cvConvert(m_pFGMask, m_pFrameMat);
//      //
//      Initialize(m_pFrameMat,rng);
//  }
//  else {
//      cvCvtColor(pFrame,m_pFGMask,CV_BGR2GRAY);
//      cvConvert(m_pFGMask,m_pFrameMat);
//      //高斯滤波先，以平滑图像
//      cvSmooth(m_pFrameMat, m_pFrameMat, CV_GAUSSIAN, 3, 0, 0);
////      ////当前帧跟背景图相减
////      cvAbsDiff(m_pFrameMat, m_pBkMat, m_pFGMat);
////        //二值化前景图
////        cvThreshold(m_pFGMat, m_pFGMask, m_threshold, 255.0, CV_THRESH_BINARY);
////        //进行形态学滤波，去掉噪音
////        cvErode(m_pFGMask, m_pFGMask, 0, 1);
////        cvDilate(m_pFGMask, m_pFGMask, 0, 1);
// //cvConvert(m_pBkMat,m_pFGMask);
//       //更新背景
////        cvRunningAvg(m_pFrameMat, m_pBkMat, 0.003, 0);
//      update(m_pFrameMat,m_pBkMat,rng,m_framecount);//更新背景
//      cvConvert(m_pBkMat,m_pFGMask);
//      cvConvert(m_pBkMat,m_pFGMask);
//  }
//  //转化成单信道图像再处理
//  cvCvtColor(pFrame, m_pFGMask, CV_BGR2GRAY);
//  cvConvert(m_pFGMask, m_pFrameMat);
//  //高斯滤波先，以平滑图像
//  cvSmooth(m_pFrameMat, m_pFrameMat, CV_GAUSSIAN, 3, 0, 0);

////当前帧跟背景图相减
// cvAbsDiff(m_pFrameMat, m_pBkMat, m_pFGMat);

//  //二值化前景图
//  cvThreshold(m_pFGMat, m_pFGMask, m_threshold, 255.0, CV_THRESH_BINARY);


//  //进行形态学滤波，去掉噪音
//  cvErode(m_pFGMask, m_pFGMask, 0, 1);
//  cvDilate(m_pFGMask, m_pFGMask, 0, 1);

// //更新背景
//  cvRunningAvg(m_pFrameMat, m_pBkMat, 0.003, 0);
  m_framecount++;
}

