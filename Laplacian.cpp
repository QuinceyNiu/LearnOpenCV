#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main() {
	Mat src, src_gray, dst, abs_dst;
	src = imread("1.jpg");
	imshow("【原始图】图像Laplace变换", src);
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	cvtColor(src, src_gray, COLOR_RGB2GRAY);
	Laplacian(src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);
	imshow("【效果图】图像Laplace变换", abs_dst);

	waitKey(0);
	return 0;
}