#pragma once

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "cvblob/cvblob.h"
#include "features2d.hpp"

class BlobTracking
{
private:
  bool firstTime;
  int minArea;
  int maxArea;
  
  bool debugTrack;
  bool debugBlob;
  bool showBlobMask;
  bool showOutput;

  cvb::CvTracks tracks;
  void saveConfig();
  void loadConfig();

public:
  BlobTracking();
  ~BlobTracking();

  void process(const cv::Mat &img_input, const cv::Mat &img_mask, cv::Mat &img_output);
  const cvb::CvTracks getTracks();
};

