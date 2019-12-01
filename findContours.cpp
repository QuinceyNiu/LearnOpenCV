#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src = imread("1.jpg", 0);
	imshow("原始图", src);

	Mat dst = Mat::zeros(src.rows, src.cols, CV_8UC3);

	src = src > 119;
	imshow("取阈值后的原始图", src);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(src, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	int index = 0;
	for (; index >= 0; index = hierarchy[index][0]) {
		Scalar color(rand() & 255, rand() & 255, rand() & 255);
		drawContours(dst, contours, index, color, FILLED, 8, hierarchy); 
	}
	imshow("轮廓图", dst);

	waitKey(0);
}