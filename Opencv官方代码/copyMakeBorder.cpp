#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;
Mat src, dst;
int top, bottom, left, right;
int borderType;
const char* window_name = "copyMakeBorder Demo";
RNG rng(12345);
int main(int argc, char** argv)
{
	String imageName("1.jpg"); // by default
	if (argc > 1)
	{
		imageName = argv[1];
	}
	src = imread(imageName, IMREAD_COLOR); // Load an image
	if (src.empty())
	{
		printf(" No data entered, please enter the path to an image file \n");
		return -1;
	}
	printf("\n \t copyMakeBorder Demo: \n");
	printf("\t -------------------- \n");
	printf(" ** Press 'c' to set the border to a random constant value \n");
	printf(" ** Press 'r' to set the border to be replicated \n");
	printf(" ** Press 'ESC' to exit the program \n");
	namedWindow(window_name, WINDOW_AUTOSIZE);
	top = (int)(0.05*src.rows); bottom = (int)(0.05*src.rows);
	left = (int)(0.05*src.cols); right = (int)(0.05*src.cols);
	dst = src;
	imshow(window_name, dst);
	for (;;)
	{
		char c = (char)waitKey(500);
		if (c == 27)
		{
			break;
		}
		else if (c == 'c')
		{
			borderType = BORDER_CONSTANT;
		}
		else if (c == 'r')
		{
			borderType = BORDER_REPLICATE;
		}
		Scalar value(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		copyMakeBorder(src, dst, top, bottom, left, right, borderType, value);
		imshow(window_name, dst);
	}
	return 0;
}