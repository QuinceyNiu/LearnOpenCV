#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;

int main() {
	Mat srcImage, dstImage;
	srcImage = imread("1.jpg", 1);
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
	imshow("原始图", srcImage);

	equalizeHist(srcImage, dstImage);
	imshow("经过直方图均衡化后的图", dstImage);

	waitKey(0);
	return 0;
}