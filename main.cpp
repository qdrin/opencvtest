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
  int thresh = 200;
  Mat imgGray, imgTh, imgEr, imgTmp;
  Mat canny_out, cannyEr;
  Mat kernel_3x3 = getStructuringElement(MORPH_ELLIPSE, Size(3,3));
  Mat kernel_5x5 = getStructuringElement(MORPH_RECT, Size(5,5));
  cvtColor(image, imgGray, COLOR_BGR2GRAY);

  threshold(imgGray, imgTh, thresh, 255, THRESH_BINARY);
  // adaptiveThreshold(imgGray, imgTh, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 7, 21);
  morphologyEx(imgTh, imgEr, MORPH_CLOSE, kernel_3x3);
  // morphologyEx(imgTmp, imgEr, MORPH_OPEN, kernel_3x3);
  
  // Canny(imgGray, canny_out, thresh, thresh*2);
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  // findContours(canny_out, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
  findContours(imgEr, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_NONE);
  vector<Rect> boundRect(contours.size());
  // hierarchy: [Next, Previous, First_Child, Parent]
  cout << "contours found: " << contours.size() << endl;
  Mat drawing = Mat::zeros(imgEr.size(), CV_8UC3);
  Scalar color = Scalar(255, 255, 255);
  int count = 0;
  for(int i=0; i < contours.size(); i++) {
    drawContours(drawing, contours, i, color, 2, LINE_8, hierarchy, 0);
    if(hierarchy[i][3] > -2) {
      boundRect[i] = boundingRect(contours[i]);
      rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 1);
    }
  }
  cout << "first-level contours: " << count << endl;
  String wName;
  wName = "Ерундульки";
  namedWindow(wName);
  imshow(wName, image);
  wName = "Ерундульки imgTh";
  namedWindow(wName);
  imshow(wName, imgTh);
  wName = "Ерундульки imgEr";
  namedWindow(wName);
  imshow(wName, imgEr);
  wName = "Ерундульки contours";
  namedWindow(wName);
  imshow(wName, drawing);
  waitKey(0);
  destroyAllWindows();

  return 0;
}
