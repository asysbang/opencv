#include "iostream"
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <dirent.h>
#include <string.h>
using namespace cv;
using namespace std;

Point getDianXiaoEr() {
	DIR * dir;                   // return value for opendir()
	dir = opendir("test");
	struct dirent * filename;
	while ((filename = readdir(dir)) != NULL) {
		// get rid of "." and ".."
		if (strcmp(filename->d_name, ".") == 0 || strcmp(filename->d_name, "..") == 0)
			continue;
		string path;
		path.append("test/").append(filename->d_name);
		cout << "======================>>>>>>" << path << endl;

		//原始数据 -> resize -> hsv
		Mat matSrc, matResize, matHsv;
		matSrc = imread(path);
		resize(matSrc, matResize, Size(), 0.5, 0.5, 1);
		cvtColor(matResize, matHsv, CV_BGR2HSV);
		//====== resize and hsv over ======

		//根据颜色过滤yellow和blue
		Mat matYellow, matBlue;
		//gimp   hsv： 23-46    27-54   175-69   210-82
		//（46, 65, 40）   （56,82,93）  s位置如果是57的话 背景很多被识别了
		inRange(matHsv, Scalar(23, 169, 100), Scalar(28, 210, 240), matYellow);
		Mat out;
		Mat element = getStructuringElement(MORPH_ELLIPSE, Size(2, 2));
		erode(matYellow, out, element);
		//膨胀
		Mat element1 = getStructuringElement(MORPH_RECT, Size(2 * 5 + 1, 2 * 5 + 1));
		Mat matDilate = Mat::zeros(out.rows, out.cols, CV_8UC3);
		dilate(out, matDilate, element1);
		//分割
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		findContours(matDilate, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		cout << "size = " << contours.size() << endl;
		Mat dst = Mat::zeros(matDilate.rows, matDilate.cols, CV_8UC3);
		int idx = 0;
		for (; idx >= 0; idx = hierarchy[idx][0]) {
			Rect r0 = boundingRect(Mat(contours[idx]));
			double area = contourArea(contours[idx]);
//			cout << "idx = " << idx << " : " << area << endl;
			if (area > 1000 && area < 2000 && r0.width < 40) {
				cout << "idx = " << idx << " : " << area << endl;
//				cout << "width  = " << r0.width << " , " << endl;
//				cout << "height  = " << r0.height << endl;
				Scalar color(rand() & 255, rand() & 255, rand() & 255);
				//			rectangle(matDilate, r0, Scalar(90, 233, 45), 1, -1, 0);
				drawContours(matResize, contours, idx, Scalar(0, 0, 255), FILLED, 1, hierarchy);
				Moments mu = moments(contours[idx], false);
				Point2f mc = Point2f(mu.m10 / mu.m00, mu.m01 / mu.m00);
				circle( matResize, mc, 4, Scalar(0, 255, 0), -1, 8, 0 );
			}
		}


		string targetPath;
		targetPath.append("target/").append(filename->d_name);
		imwrite(targetPath, matResize);

	}
	Point position;
	return position;
}

Point getDianXiaoErBack() {
	const char *pstrImageName = "1516610426.png";
	//原始数据
	Mat matSrc = imread(pstrImageName);
	Mat matResize;
	resize(matSrc, matResize, Size(), 0.5, 0.5, 1);
	Mat matHsv;
	cvtColor(matResize, matHsv, CV_BGR2HSV);

	//hsv过滤
	Mat imgThresholded;
	const Scalar hsvGreenLo(23, 175, 115);
	const Scalar hsvGreenHi(27, 210, 230);
	inRange(matHsv, hsvGreenLo, hsvGreenHi, imgThresholded);
	Mat out;
//	imshow("imgThresholded",imgThresholded);
//	//高斯滤波
//	GaussianBlur(imgThresholded, out, Size(13, 13), 2, 2);
//	bilateralFilter(imgThresholded, out, 40, 120, 120);
	//腐蚀
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(2, 2));
	erode(imgThresholded, out, element);
//	imshow("erode",out);
	//膨胀
	Mat element1 = getStructuringElement(MORPH_RECT, Size(2 * 5 + 1, 2 * 5 + 1));
	Mat matDilate = Mat::zeros(out.rows, out.cols, CV_8UC3);
	dilate(out, matDilate, element1);
//	imshow("dilate",matDilate);

	//分割
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(matDilate, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	cout << "size = " << contours.size() << endl;
	Mat dst = Mat::zeros(matDilate.rows, matDilate.cols, CV_8UC3);
	int idx = 0;
	for (; idx >= 0; idx = hierarchy[idx][0]) {
		Rect r0 = boundingRect(Mat(contours[idx]));
		//45x125
		if (r0.height > 33 && r0.height < 66) {
			cout << "idx = " << idx << " : ";
			cout << "width  = " << r0.width << " , ";
			cout << "height  = " << r0.height << endl;
			Scalar color(rand() & 255, rand() & 255, rand() & 255);
			//			rectangle(matDilate, r0, Scalar(90, 233, 45), 1, -1, 0);
			drawContours(matResize, contours, idx, Scalar(0, 0, 255), FILLED, 1, hierarchy);
		}
//		drawContours(dst, contours, idx, color, FILLED, 1, hierarchy);
	}

	namedWindow("getDianXiaoEr", 1);
	imshow("getDianXiaoEr", matResize);
//	imwrite("ok.png", matResize);
	waitKey();

	Point position;
	return position;
}

int getHuoDongRiLi() {
	const char *pstrImageName = "huodongrili.png";
	const char *pstrTargetImageName = "huodongrili_target.png";
	const char *pstrTargetThresholdImageName = "huodongrili_target_threshols.png";
	//灰度图像
	Mat matSrc = imread(pstrImageName, 0);
	//裁剪对应的区域
	Rect rc(880, 260, 200, 60);
	Mat matGray = Mat(matSrc, rc);
	imwrite(pstrTargetImageName, matGray);
	//二值化
	Mat matThreshold = matGray.clone();
	threshold(matGray, matThreshold, 145, 255, CV_THRESH_TOZERO);
	//膨胀
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * 1 + 1, 2 * 10 + 1));
	Mat matDilate = Mat::zeros(matThreshold.rows, matThreshold.cols, CV_8UC3);
	dilate(matThreshold, matDilate, element);
	//分割
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(matDilate, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	Mat dst = Mat::zeros(matDilate.rows, matDilate.cols, CV_8UC3);
	int idx = 0;
	for (; idx >= 0; idx = hierarchy[idx][0]) {
		Scalar color(rand() & 255, rand() & 255, rand() & 255);
		Rect r0 = boundingRect(Mat(contours[idx]));
		rectangle(matThreshold, r0, Scalar(90, 233, 45), 1, 1, 0);
//		drawContours(dst, contours, idx, color, FILLED, 1, hierarchy);
	}
	imwrite(pstrTargetThresholdImageName, matThreshold);
	namedWindow("Components", 1);
	imshow("Components", matThreshold);
	waitKey();
	return -1;
}
