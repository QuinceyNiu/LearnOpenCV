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

	//��ȡ��Ƶ��ǰ������

	cap.open("1.mp4"); //����Ƶ,��������ȼ���VideoCapture cap("E://2.avi");

								//Ҳ����ֱ�Ӵ���ҳ�л�ȡͼƬ��ǰ������ҳ����Ƶ���Լ����ٹ���

	if (!cap.isOpened())//�����Ƶ�����������򷵻�

		return 0;

	Mat frame;

	cvNamedWindow("�ҵ�����ͷ", CV_WINDOW_AUTOSIZE);

	int frames = (int)cap.get(CV_CAP_PROP_FRAME_COUNT);

	if (frames != 0)

	{

		cvCreateTrackbar("positions", "�ҵ�����ͷ", &g_slide_position, frames, onTrasckbarSlide);

	}

	while (1)

	{

		cap >> frame;//�ȼ���cap.read(frame);

		if (frame.empty())//���ĳ֡Ϊ�����˳�ѭ��

			break;

		imshow("�ҵ�����ͷ", frame);



		waitKey(20);//ÿ֡��ʱ20����

		cvSetTrackbarPos("positions", "�ҵ�����ͷ", g_slide_position);

		g_slide_position++;

	}

	cap.release();//�ͷ���Դ



	cvDestroyWindow("�ҵ�����ͷ");

	return 0;

}