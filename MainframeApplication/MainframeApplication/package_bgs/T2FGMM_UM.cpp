/*
This file is part of BGSLibrary.

BGSLibrary is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

BGSLibrary is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with BGSLibrary.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "T2FGMM_UM.h"

using namespace bgslibrary::algorithms;

T2FGMM_UM::T2FGMM_UM() :
  frameNumber(0), threshold(9.0), alpha(0.01), km(1.5f), kv(0.6f), gaussians(3)
{
  std::cout << "T2FGMM_UM()" << std::endl;
  setup("./config/T2FGMM_UM.xml");
}

T2FGMM_UM::~T2FGMM_UM()
{
  std::cout << "~T2FGMM_UM()" << std::endl;
}

void T2FGMM_UM::process(const cv::Mat &img_input, cv::Mat &img_output, cv::Mat &img_bgmodel)
{
  init(img_input, img_output, img_bgmodel);
  frame = new IplImage(img_input);

  if (firstTime)
    frame_data.ReleaseMemory(false);
  frame_data = frame;

  if (firstTime)
  {
    int width = img_input.size().width;
    int height = img_input.size().height;

    lowThresholdMask = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
    lowThresholdMask.Ptr()->origin = IPL_ORIGIN_BL;

    highThresholdMask = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
    highThresholdMask.Ptr()->origin = IPL_ORIGIN_BL;

    params.SetFrameSize(width, height);
    params.LowThreshold() = threshold;
    params.HighThreshold() = 2 * params.LowThreshold();
    params.Alpha() = alpha;
    params.MaxModes() = gaussians;
    params.Type() = TYPE_T2FGMM_UM;
    params.KM() = km; // Factor control for the T2FGMM-UM [0,3] default: 1.5
    params.KV() = kv; // Factor control for the T2FGMM-UV [0.3,1] default: 0.6

    bgs.Initalize(params);
    bgs.InitModel(frame_data);
  }

  bgs.Subtract(frameNumber, frame_data, lowThresholdMask, highThresholdMask);
  lowThresholdMask.Clear();
  bgs.Update(frameNumber, frame_data, lowThresholdMask);

  img_foreground = cv::cvarrToMat(highThresholdMask.Ptr());
  img_background = cv::cvarrToMat(bgs.Background()->Ptr());
  //img_background = cv::Mat::zeros(img_input.size(), img_input.type());

#ifndef MEX_COMPILE_FLAG
  if (showOutput)
    cv::imshow("T2FGMM-UM", img_foreground);
#endif

  img_foreground.copyTo(img_output);
  img_background.copyTo(img_bgmodel);

  delete frame;
  firstTime = false;
  frameNumber++;
}

void T2FGMM_UM::saveConfig()
{
  CvFileStorage* fs = cvOpenFileStorage(config_xml.c_str(), nullptr, CV_STORAGE_WRITE);

  cvWriteReal(fs, "threshold", threshold);
  cvWriteReal(fs, "alpha", alpha);
  cvWriteReal(fs, "km", km);
  cvWriteReal(fs, "kv", kv);
  cvWriteInt(fs, "gaussians", gaussians);
  cvWriteInt(fs, "showOutput", showOutput);

  cvReleaseFileStorage(&fs);
}

void T2FGMM_UM::loadConfig()
{
  CvFileStorage* fs = cvOpenFileStorage(config_xml.c_str(), nullptr, CV_STORAGE_READ);

  threshold = cvReadRealByName(fs, nullptr, "threshold", 9.0);
  alpha = cvReadRealByName(fs, nullptr, "alpha", 0.01);
  km = cvReadRealByName(fs, nullptr, "km", 1.5);
  kv = cvReadRealByName(fs, nullptr, "kv", 0.6);
  gaussians = cvReadIntByName(fs, nullptr, "gaussians", 3);
  showOutput = cvReadIntByName(fs, nullptr, "showOutput", true);

  cvReleaseFileStorage(&fs);
}
