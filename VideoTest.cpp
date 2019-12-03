#include <imgproc/imgproc.hpp>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
using namespace cv;
VideoCapture cap;

int g_slide_position = 0;

void onTrasckbarSlide(int pos)

{

	cap.set(CV_CAP_PROP_POS_FRAMES, pos);

}



int main()

{

	//读取视频，前进后退

	cap.open("1.mp4"); //打开视频,以上两句等价于VideoCapture cap("E://2.avi");

								//也可以直接从网页中获取图片，前提是网页有视频，以及网速够快

	if (!cap.isOpened())//如果视频不能正常打开则返回

		return 0;

	Mat frame;

	cvNamedWindow("我的摄像头", CV_WINDOW_AUTOSIZE);

	int frames = (int)cap.get(CV_CAP_PROP_FRAME_COUNT);

	if (frames != 0)

	{

		cvCreateTrackbar("positions", "我的摄像头", &g_slide_position, frames, onTrasckbarSlide);

	}

	while (1)

	{

		cap >> frame;//等价于cap.read(frame);

		if (frame.empty())//如果某帧为空则退出循环

			break;

		imshow("我的摄像头", frame);



		waitKey(20);//每帧延时20毫秒

		cvSetTrackbarPos("positions", "我的摄像头", g_slide_position);

		g_slide_position++;

	}

	cap.release();//释放资源



	cvDestroyWindow("我的摄像头");

	return 0;

}