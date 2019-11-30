#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

int main() {
	Mat srcImage = imread("1.jpg");
	Mat midImage, dstImage;
	imshow("��ԭʼͼ��", srcImage);

	cvtColor(srcImage, midImage, COLOR_BGR2GRAY);
	GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);

	vector<Vec3f> circles;
	HoughCircles(midImage, circles, HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);

	for (size_t i = 0; i < circles.size(); i++) {
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);

		circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);

		circle(srcImage, center, radius, Scalar(155, 50, 255), 3, 8, 0);
	}
	imshow("��Ч��ͼ��", srcImage);

	waitKey(0);
	return 0;

}