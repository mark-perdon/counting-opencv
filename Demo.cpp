#include <iostream>
#include <cv.h>
#include <highgui.h>
#include "package_bgs/PBAS/PixelBasedAdaptiveSegmenter.h"
#include "package_tracking/BlobTracking.h"
#include "package_analysis/PeopleCounting.h"
#include <string>
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main(int argc, char **argv)
{
  std::cout << "Using OpenCV " << CV_MAJOR_VERSION << "." << CV_MINOR_VERSION << "." << CV_SUBMINOR_VERSION << std::endl;

  /* Open video file */
  CvCapture *capture;
  capture = cvCaptureFromAVI("dataset/lowres8x.mp4");
  double fps = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
  if (!capture){
    std::cerr << "Cannot open video!" << std::endl;
	return 0;
  }
 

  /* Background Subtraction Algorithm */
  IBGS *bgs;
  bgs = new PixelBasedAdaptiveSegmenter;
  
  /* Blob Tracking Algorithm */
  cv::Mat img_blob;
  BlobTracking* blobTracking;
  blobTracking = new BlobTracking;

  /* Vehicle Counting Algorithm */
  PeopleCounting* peopleCounting;
  peopleCounting = new PeopleCounting;

  std::cout << "Press 'q' to quit..." << std::endl;
  int key = 0;
  IplImage *frame;
  while (key != 'q')
  {
    frame = cvQueryFrame(capture);
    if(!frame) break;

    cv::Mat img_input(frame);
    //cv::imshow("Input", img_input);

    // bgs->process(...) internally process and show the foreground mask image
    cv::Mat img_mask;
    bgs->process(img_input, img_mask);
    
    if(!img_mask.empty())
    {
      // Perform blob tracking
      blobTracking->process(img_input, img_mask, img_blob);

      // Perform vehicle counting
      peopleCounting->setInput(img_blob);
      peopleCounting->setTracks(blobTracking->getTracks());
      peopleCounting->process();
	}
    key = cvWaitKey(5);
  }

  //delete vehicleCounting;
  //delete blobTracking;
  //delete bgs;

//  cvDestroyAllWindows();
//  cvReleaseCapture(&capture);
  
//  return 0;
}
