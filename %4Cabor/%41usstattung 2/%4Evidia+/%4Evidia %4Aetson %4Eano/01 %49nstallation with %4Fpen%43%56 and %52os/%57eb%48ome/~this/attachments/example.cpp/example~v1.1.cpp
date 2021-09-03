/******************************************************************************************
 - File Name     :  example.cpp

 - Created by   :  Matthias Domnik

 - Description  :  Demo program to determine if the installation of OpenCV went
fine.
*****************************************************************************************/

#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudafilters.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;
using namespace cv::cuda;

int main(int argc, const char *argv[]) {

  std::cout << "Welcome to OpenCV " << CV_VERSION << std::endl;

  int num_gpu = cuda::getCudaEnabledDeviceCount();
  std::cout << "Number of GPUs: " << num_gpu << std::endl;

  VideoCapture cap(0);
  if (!cap.isOpened())
    return -1;

  Mat frame, Gframe, Gbuff_, Cframe;
  cuda::GpuMat Gsrc, Gdst;
  vector<cv::Mat> frame_split(3), Gframe_split(3), Cframe_split(3);

  Ptr<cuda::CLAHE> clahe = cuda::createCLAHE();
  clahe->setClipLimit(4.);
  clahe->setTilesGridSize(Size(16, 16));

  Ptr<cv::CLAHE> clahe_cpu = cv::createCLAHE();
  clahe_cpu->setClipLimit(4);

  int64_t start = 0;
  double timeSec = 0;

  for (size_t i = 0; i < 20; i++) {
    cap >> frame;

    cv::split(frame, Gframe_split);
    cv::split(frame, Cframe_split);

    Gsrc.upload(Gframe_split[2]);
    start = getTickCount();
    clahe->apply(Gsrc, Gdst);
    timeSec = (getTickCount() - start) / getTickFrequency();
    cout << "GPU Time : " << timeSec * 1000 << " ms" << endl;
    Gdst.download(Gbuff_);

    Gframe_split[2] = Gbuff_;
    cv::merge(Gframe_split, Gframe);

    start = getTickCount();
    clahe_cpu->apply(Cframe_split[2], Cframe_split[2]);
    timeSec = (getTickCount() - start) / getTickFrequency();
    cout << "CPU Time : " << timeSec * 1000 << " ms" << endl;

    cv::merge(Cframe_split, Cframe);

    // imshow("GPU result", Gframe);
    // if (waitKey(30) >= 0)
    //   break;
    //
    // imshow("CPU result", Cframe);
    // if (waitKey(30) >= 0)
    //   break;
  }
  return 0;
}
