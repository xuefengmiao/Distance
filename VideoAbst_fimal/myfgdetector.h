
#ifndef  MYFGDETECTOR_H
#define  MYFGDETECTOR_H
#include "vibeBackgroundOwn.h"
#include "bs_post_processing.h"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/legacy/blobtrack.hpp"
#include "opencv2/legacy/legacy.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc_c.h>

#include <stdio.h>
#include <iostream>
using namespace std;
using namespace cv;


class MyFGDetector:public CvFGDetector
{
 protected:
  int m_framecount;
  double m_alpha;
  double m_threshold;

  IplImage* m_pFrame;
  IplImage* m_pFGMask;

  CvMat* m_pFrameMat;
  CvMat* m_pFGMat;
  CvMat* m_pBkMat;

  void Create(double alpha, double threshold);

 public:
  vibeModel* vbM;
  MyFGDetector();
  MyFGDetector(double alpha, double threshold);
  ~MyFGDetector();

  IplImage* GetMask();
  /* process current image */
  void    Process(IplImage* pFrame);
  /* release foreground detector */
  void    Release();
};

#endif
