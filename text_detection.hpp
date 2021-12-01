#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

vector<Rect>& textCandidates(
  Mat image,
  double min_text_fill = 0.4,
  double max_text_fill = 0.9,
  int min_text_height = 8,
  int min_text_width = 8
);

Mat &textContours(const Mat& image, double thresh = 100.0, double m_thresh = 200.0);
