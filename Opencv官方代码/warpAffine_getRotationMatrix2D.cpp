#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
const char* source_window = "Source image";
const char* warp_window = "Warp";
const char* warp_rotate_window = "Warp + Rotate";
int main(int, char** argv)
{
	Point2f srcTri[3];
	Point2f dstTri[3];
	Mat rot_mat(2, 3, CV_32FC1);
	Mat warp_mat(2, 3, CV_32FC1);
	Mat src, warp_dst, warp_rotate_dst;
	src = imread("3.jpg", IMREAD_COLOR);
	warp_dst = Mat::zeros(src.rows, src.cols, src.type());
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(src.cols - 1.f, 0);
	srcTri[2] = Point2f(0, src.rows - 1.f);
	dstTri[0] = Point2f(src.cols*0.0f, src.rows*0.33f);
	dstTri[1] = Point2f(src.cols*0.85f, src.rows*0.25f);
	dstTri[2] = Point2f(src.cols*0.15f, src.rows*0.7f);
	warp_mat = getAffineTransform(srcTri, dstTri);
	warpAffine(src, warp_dst, warp_mat, warp_dst.size());
	Point center = Point(warp_dst.cols / 2, warp_dst.rows / 2);
	double angle = -50.0;
	double scale = 0.6;
	rot_mat = getRotationMatrix2D(center, angle, scale);
	warpAffine(warp_dst, warp_rotate_dst, rot_mat, warp_dst.size());
	namedWindow(source_window, WINDOW_AUTOSIZE);
	imshow(source_window, src);
	namedWindow(warp_window, WINDOW_AUTOSIZE);
	imshow(warp_window, warp_dst);
	namedWindow(warp_rotate_window, WINDOW_AUTOSIZE);
	imshow(warp_rotate_window, warp_rotate_dst);
	waitKey(0);
	return 0;
}