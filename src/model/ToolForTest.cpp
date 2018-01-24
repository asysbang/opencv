#include "opencv2/opencv.hpp"
using namespace cv;
//定义全局变量
const int g_ndMaxValue = 100;
const int g_nsigmaColorMaxValue = 200;
const int g_nsigmaSpaceMaxValue = 200;
int g_ndValue;
int g_nsigmaColorValue;
int g_nsigmaSpaceValue;

Mat g_srcImage;
Mat g_dstImage;
void on_bilateralFilterTrackbar(int, void*) {

	//方框滤波函数
	bilateralFilter(g_srcImage, g_dstImage, g_ndValue, g_nsigmaColorValue, g_nsigmaSpaceValue);
	imshow("方框滤波", g_dstImage);
}
void bilateralFilterTest() {
	g_srcImage = imread("1516610426.png");

	namedWindow("原图像", WINDOW_AUTOSIZE);
	imshow("原图像", g_srcImage);

	//定义输出图像窗口属性和轨迹条属性
	namedWindow("双边滤波图像", WINDOW_AUTOSIZE);
	g_ndValue = 10;
	g_nsigmaColorValue = 10;
	g_nsigmaSpaceValue = 10;

	char dName[20];
	sprintf(dName, "邻域直径 %d", g_ndMaxValue);

	char sigmaColorName[20];
	sprintf(sigmaColorName, "sigmaColor %d", g_nsigmaColorMaxValue);

	char sigmaSpaceName[20];
	sprintf(sigmaSpaceName, "sigmaSpace %d", g_nsigmaSpaceMaxValue);

	//创建轨迹条
	createTrackbar(dName, "双边滤波图像", &g_ndValue, g_ndMaxValue, on_bilateralFilterTrackbar);
	on_bilateralFilterTrackbar(g_ndValue, 0);

	createTrackbar(sigmaColorName, "双边滤波图像", &g_nsigmaColorValue, g_nsigmaColorMaxValue, on_bilateralFilterTrackbar);
	on_bilateralFilterTrackbar(g_nsigmaColorValue, 0);

	createTrackbar(sigmaSpaceName, "双边滤波图像", &g_nsigmaSpaceValue, g_nsigmaSpaceMaxValue, on_bilateralFilterTrackbar);
	on_bilateralFilterTrackbar(g_nsigmaSpaceValue, 0);

	waitKey(0);
}

int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;
int const max_elem = 2;
int const max_kernel_size = 21;
Mat src, erosion_dst, dilation_dst;
void Erosion(int, void*) {
	int erosion_type;
	if (erosion_elem == 0) {
		erosion_type = MORPH_RECT;
	} else if (erosion_elem == 1) {
		erosion_type = MORPH_CROSS;
	} else if (erosion_elem == 2) {
		erosion_type = MORPH_ELLIPSE;
	}

	Mat element = getStructuringElement(erosion_type, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size));

	/// 腐蚀操作
	erode(src, erosion_dst, element);
	imshow("Erosion", erosion_dst);
}

void Dilation(int, void*) {
	int dilation_type;
	if (dilation_elem == 0) {
		dilation_type = MORPH_RECT;
	} else if (dilation_elem == 1) {
		dilation_type = MORPH_CROSS;
	} else if (dilation_elem == 2) {
		dilation_type = MORPH_ELLIPSE;
	}

	Mat element = getStructuringElement(dilation_type, Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size));
	///膨胀操作
	dilate(src, dilation_dst, element);
	imshow("Dilation Demo", dilation_dst);
}
void erodeTest() {
	src = imread("test.png");
	/// 创建显示窗口
	namedWindow("Erosion", CV_WINDOW_AUTOSIZE);
	namedWindow("Dilation Demo", CV_WINDOW_AUTOSIZE);

	/// 创建腐蚀 Trackbar
	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion", &erosion_elem, max_elem, Erosion);

	createTrackbar("Kernel size:\n 2n +1", "Erosion", &erosion_size, max_kernel_size, Erosion);

	/// 创建膨胀 Trackbar
	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo", &dilation_elem, max_elem, Dilation);

	createTrackbar("Kernel size:\n 2n +1", "Dilation Demo", &dilation_size, max_kernel_size, Dilation);

	/// Default start
	Erosion(0, 0);
	Dilation(0, 0);

	waitKey(0);
	return;
}

