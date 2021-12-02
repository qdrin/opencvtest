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
  String wName;
  Mat image = imread(filename.c_str());
  Mat gray;
  cvtColor(image, gray, COLOR_RGB2GRAY);
  if(image.empty())
  {
    cout << "Could not open or find the image " << filename << endl;
    cin.get();
    return -1;
  }

  vector<Rect> rects;
  vector<Mat*> letters;
  textCandidates(image, rects);
  Mat res = Mat::zeros(gray.size(), CV_8UC1);
  for(int i=rects.size()-1; i < rects.size(); i++)
  {
    Mat part(image, rects[i]);
    textContours(part, letters, 100.0, 200.0);
    rectangle(image, rects[i], Scalar(0, 255, 0), 1);
    Rect r;
    r.x = rects[i].x;
    r.y = rects[i].y;
    int num = 0;
    for(vector<Mat*>::iterator it=letters.begin(); it != letters.end(); it++) {
      r.width = (*it)->size().width;
      r.height = (*it)->size().height;
      wName = num++;
      // namedWindow(wName);
      // imshow(wName, **it);
      (*it)->copyTo(Mat(res(r)));
      r.x = r.x + r.width + 2;
    }
  }

  wName = "Ерундульки";
  namedWindow(wName);
  imshow(wName, image);
  wName = "Ерундульки_drawing";
  namedWindow(wName);
  imshow(wName, res);
  waitKey(0);
  destroyAllWindows();

  return 0;
}
