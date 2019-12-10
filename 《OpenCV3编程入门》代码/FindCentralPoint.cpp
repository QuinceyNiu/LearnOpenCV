#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
using namespace std;
using namespace cv;

int main() {
	Mat img = imread("2.jpg", 1);
	Mat grayImage, binaryImage;
	cvtColor(img, grayImage, CV_BGR2GRAY);
	medianBlur(grayImage, grayImage, 7);

	threshold(grayImage, binaryImage, 100, 255, CV_THRESH_BINARY_INV);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binaryImage, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point());

	Mat drawingPicture = Mat::zeros(binaryImage.size(), CV_8UC1); 
	vector<RotatedRect> box(contours.size()); 
	for (int i = 0; i < contours.size(); i++)
	{
		drawContours(drawingPicture, contours, i, Scalar(255), 1, 8, hierarchy);
 
		RotatedRect rect = minAreaRect(contours[i]);
		box[i] = minAreaRect(Mat(contours[i]));

		Point2f P[4];
		circle(img, Point(box[i].center.x, box[i].center.y), 5, Scalar(0, 255, 0), -1, 8);
		printf("The coordination of the central point is: (%d, %d)\n", box[i].center.x, box[i].center.y);

		rect.points(P);
		for (int j = 0; j <= 3; j++)
		{
			line(img, P[j], P[(j + 1) % 4], Scalar(0, 0, 255), 1);
			line(drawingPicture, P[j], P[(j + 1) % 4], Scalar(111), 2);
		}
	}
	imshow("minAreaRect", img);
	waitKey(0);
	return 0;
}
