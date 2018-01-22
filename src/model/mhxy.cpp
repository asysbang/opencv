#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
int getHuoDongRiLi() {
	const char *pstrImageName = "huodongrili.png";
	Mat matSrc = imread(pstrImageName);
	Mat matGray = Mat(240, 320, CV_8U, cv::Scalar(100));
	namedWindow("Test");     //创建一个名为Test窗口
	for (int i = 0; i < matGray.rows; i++)        //遍历每一行每一列并设置其像素值
			{
		for (int j = 0; j < matGray.cols; j++) {
			matGray.at<uchar>(i, j) = 255;
		}
	}
	cv::Point p1;
	p1.x = 10;
	p1.y = 10;
	cv::Point p2;
	p2.x = 100;
	p2.y = 200;
	line(matGray, p1, p2, Scalar(0), 2, CV_AA);        //2为线的宽度，CV_AA为反走样形式
	imshow("Test", matGray);   //窗口中显示图像
	imwrite("a111.jpg", matGray);    //保存生成的图片
	waitKey(); //等待5000ms后窗口自动关闭
	return -1;
}
