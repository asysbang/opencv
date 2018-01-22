//============================================================================
// Name        : asys_opencv.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
using namespace std;
using namespace cv;

int mainx() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!



	const char *pstrImageName = "1.png";
	const char *pstrSaveImageName = "save.png";
	Mat mat = imread(pstrImageName);
	namedWindow("aaa", CV_WINDOW_NORMAL);
	imshow("aaa",mat);
	waitKey();


//	double fScale = 0.4;
//	CvSize cvSize;
//
//	IplImage *pdataImage = cvLoadImage(pstrImageName, CV_LOAD_IMAGE_UNCHANGED);
//	IplImage *pdataSaveImage = NULL;
//
//	cvSize.width = pdataImage->width * fScale;
//	cvSize.height = pdataImage->height * fScale;
//
//
//	imread(pstrImageName,1);
//
//	pdataSaveImage = cvCreateImage(cvSize, pdataImage->depth, pdataImage->nChannels);
//	cvResize(pdataImage, pdataSaveImage, CV_INTER_AREA);
//
//	cvNamedWindow(pstrImageName, CV_WINDOW_AUTOSIZE);
//	cvNamedWindow(pstrSaveImageName, CV_WINDOW_AUTOSIZE);
//
//	//在指定窗口中显示图像
//	cvShowImage(pstrImageName, pdataImage);
//	cvShowImage(pstrSaveImageName, pdataSaveImage);
//
//	//等待按键事件
//	cvWaitKey();
//
//	//保存图片
//	cvSaveImage(pstrSaveImageName, pdataSaveImage);
//
//	cvDestroyWindow(pstrImageName);
//	cvDestroyWindow(pstrSaveImageName);
//	cvReleaseImage(&pdataImage);
//	cvReleaseImage(&pdataSaveImage);

	return 0;
}
