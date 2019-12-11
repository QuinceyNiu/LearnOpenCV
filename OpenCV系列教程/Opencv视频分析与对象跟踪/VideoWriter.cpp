#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	//VideoCapture capture;
	//capture.open("D:/vcprojects/images/video_006.mp4");
	VideoCapture capture(0);
	if (!capture.isOpened()) {
		printf("could not load video data...\n");
		return -1;
	}
	// 获取帧的属性
	double fps = capture.get(CV_CAP_PROP_FPS);
	Size size = Size(capture.get(CV_CAP_PROP_FRAME_WIDTH), capture.get(CV_CAP_PROP_FRAME_HEIGHT));
	printf("FPS : %f", fps);
	VideoWriter writer("wv_demo.mp4", CV_FOURCC('D', 'I', 'V', 'X'), 15.0, size, true);

	// create window
	Mat frame, gray, binary;
	namedWindow("video-demo", CV_WINDOW_AUTOSIZE);

	// show each frame and save
	vector<Mat> bgr;
	while (capture.read(frame)) {
		//inRange(frame, Scalar(0, 127, 0), Scalar(127, 255, 127), gray);
		//cvtColor(frame, gray, COLOR_BGR2GRAY);
		//threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
		//bitwise_not(frame, frame);
		flip(frame, frame, 1);
		imshow("video-demo", frame);
		writer.write(frame);
		char c = waitKey(100);
		if (c == 27) {
			break;
		}
	}

	waitKey(0);
	return 0;
}