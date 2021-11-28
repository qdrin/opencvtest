#include <opencv2/opencv.hpp>
#include "text_detection.hpp"

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
  Mat gray;
  cvtColor(image, gray, COLOR_RGB2GRAY);
  if(image.empty())
  {
    cout << "Could not open or find the image " << filename << endl;
    cin.get();
    return -1;
  }
  vector<Rect> &rects = textCandidates(image);
  for(int i=0; i < rects.size(); i++)
  {
    Mat part(image, rects[i]);
    Mat &contour = textContours(part);
    contour.copyTo(Mat(gray, rects[i]));
    rectangle(gray, rects[i], Scalar(0, 255, 0), 1);
  }
  String wName;
  wName = "Ерундульки_gray";
  namedWindow(wName);
  imshow(wName, gray);
  waitKey(0);
  destroyAllWindows();

  return 0;
}
