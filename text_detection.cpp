#include "text_detection.hpp"

using namespace cv;
using namespace std;

vector<Rect>& textCandidates(
  Mat image,
  double min_text_fill, double max_text_fill,
  int min_text_height, int min_text_width
  )
{
  Mat gray, grad, imgTh, connected;
  Mat kernel_3x3 = getStructuringElement(MORPH_ELLIPSE, Size(3,3));
  Mat kernel_9x1 = getStructuringElement(MORPH_RECT, Size(9,1));
  cvtColor(image, gray, COLOR_BGR2GRAY);

  morphologyEx(gray, grad, MORPH_GRADIENT, kernel_3x3);
  threshold(grad, imgTh, 0, 255, THRESH_BINARY | THRESH_OTSU);
  morphologyEx(imgTh, connected, MORPH_CLOSE, kernel_9x1);
  
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  findContours(connected, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
  vector<Rect> *result = new vector<Rect>;
  Mat drawing = Mat::zeros(imgTh.size(), CV_8UC1);
  Scalar color = Scalar(255, 255, 255);
  for(int idx=0; idx >=0; idx = hierarchy[idx][0]) {
    Rect rect = boundingRect(contours[idx]);
    Mat maskROI(drawing, rect);
    maskROI = Scalar(0, 0, 0);
    drawContours(drawing, contours, idx, color, FILLED);
    double r = static_cast<double>(countNonZero(maskROI))/(rect.width*rect.height);
    if(
      r > min_text_fill && r < max_text_fill &&
      rect.height > min_text_height && rect.width > min_text_width
      )
    {
      result->insert(result->end(), rect);
    }
  }
  return *result;
}

Mat &textContours(const Mat& image, double thresh)
{
  Mat gray, imgTh;
  Mat kernel_3x3 = getStructuringElement(MORPH_ELLIPSE, Size(3,3));
  cvtColor(image, gray, COLOR_BGR2GRAY);
  threshold(gray, imgTh, thresh, 255, THRESH_BINARY);
  Mat *res = new Mat();
  imgTh.copyTo(*res);
  return *res;
}