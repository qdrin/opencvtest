#include <opencv2/opencv.hpp>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
using namespace cv;

int main()
{
  String filename = "./erundulki.jpg";
  Mat image = imread(filename.c_str());
  if(image.empty())
  {
    cout << "Could not open or find the image " << filename << endl;
    cin.get();
    return -1;
  }
  int th_val = 200, th_max = 255;  // threshhold value and max(black)
  Mat imgGray, imgTh, imgEr;
  Mat kernel_3x3;
  Mat kernel_5x5;
  cvtColor(image, imgGray, COLOR_BGR2GRAY);
  adaptiveThreshold(imgGray, imgTh, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 7, 21);
  erode(imgTh, imgEr, getStructuringElement(MORPH_RECT, Size(3,3)));

  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  findContours(imgEr, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
  Mat drawing = Mat::zeros(imgEr.size(), CV_8UC3);
  for(int i=0; i < contours.size(); i++)
    drawContours(drawing, contours, i, 255, 2, LINE_8, hierarchy, 0);
  String wName;
  wName = "Ерундульки";
  namedWindow(wName);
  imshow(wName, image);
  wName = "Ерундульки threshold";
  namedWindow(wName);
  imshow(wName, imgTh);
  wName = "Ерундульки erode";
  namedWindow(wName);
  imshow(wName, imgEr);
  wName = "Ерундульки contours";
  namedWindow(wName);
  imshow(wName, drawing);
  waitKey(0);
  destroyAllWindows();

  return 0;
}
