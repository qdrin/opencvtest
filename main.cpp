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
  String wName = "Ерундульки";
  namedWindow(wName);
  imshow(wName, image);
  waitKey(0);
  destroyWindow(wName);
  return 0;
}
