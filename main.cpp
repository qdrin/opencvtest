#include <opencv2/opencv.hpp>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
using namespace cv;

double min_text_fill = 0.4, max_text_fill = 0.8;
int min_text_height = 8, min_text_width = 8;

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
  Mat imgGray, imgTh;
  Mat grad;
  Mat kernel_3x3 = getStructuringElement(MORPH_ELLIPSE, Size(3,3));
  Mat kernel_9x1 = getStructuringElement(MORPH_RECT, Size(9,1));
  cvtColor(image, imgGray, COLOR_BGR2GRAY);

  morphologyEx(imgGray, grad, MORPH_GRADIENT, kernel_3x3);
  threshold(grad, imgTh, 0, 255, THRESH_BINARY | THRESH_OTSU);
  Mat connected;
  morphologyEx(imgTh, connected, MORPH_CLOSE, kernel_9x1);
  // morphologyEx(imgTh, imgEr, MORPH_CLOSE, kernel_3x3);
  
  // Canny(imgGray, canny_out, thresh, thresh*2);
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  // findContours(canny_out, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
  findContours(connected, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
  vector<Rect> boundRect(contours.size());
  // hierarchy: [Next, Previous, First_Child, Parent]
  cout << "contours found: " << contours.size() << endl;
  Mat drawing = Mat::zeros(imgTh.size(), CV_8UC1);
  Scalar color = Scalar(255, 255, 255);
  for(int idx=0; idx >=0; idx = hierarchy[idx][0]) {
    Rect rect = boundingRect(contours[idx]);
    Mat maskROI(drawing, rect);
    maskROI = Scalar(0, 0, 0);
    drawContours(drawing, contours, idx, color, FILLED);
    double r = static_cast<double>(countNonZero(maskROI))/(rect.width*rect.height);
    cout << idx << ": r=" << r << endl;
    if(
      r > min_text_fill && r < max_text_fill &&
      rect.height > min_text_height && rect.width > min_text_width
      )
    {
      rectangle(image, rect, Scalar(0, 255, 0), 2);
    }
  }
  String wName;
  wName = "Ерундульки";
  namedWindow(wName);
  imshow(wName, image);
  waitKey(0);
  destroyAllWindows();

  return 0;
}
