#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main() {
	Mat src = imread("1.jpg", 0);
	imshow("src", src);

	Mat cornerStrength;
	cornerHarris(src, cornerStrength, 2, 3, 0.01);

	Mat harrisCorner;
	threshold(cornerStrength, harrisCorner, 0.00001, 255, THRESH_BINARY);
	imshow("binary image after cornerHarris", harrisCorner);

	waitKey(0);
	return 0;
}