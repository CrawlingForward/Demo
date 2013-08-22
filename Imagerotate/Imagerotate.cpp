#include "stdafx.h"

#include <cv.h>
#include <highgui.h>
#include<math.h>
#include <stdio.h>


int main (int argc, char **argv)
{
	IplImage *src = 0;
	IplImage *dst = 0;

	/* the first command line parameter must be image file name */
	if ((argc == 3) && (src = cvLoadImage (argv[1], -1)) != 0)
	{
		int delta = 1;
		int angle = 0;
		
		// 0:  仅仅旋转
		double factor;
		dst = cvCloneImage (src);
		//计算信噪比
		//CvScalar sum=cvSum(dst);  
		//CvScalar mean=cvAvg(dst);  
		//CvScalar stddev0;  
		//cvAvgSdv(dst,NULL,&stddev0);  
		//double psnr0=20*log10((double)255/stddev0.val[0]);  
		//printf("%lf\n",sum.val[0]);  
		//printf("%lf\n",mean.val[0]);  
		//printf("%lf\n",stddev.val[0]);  
		//printf("信噪比:%lf\n",psnr0); 

		angle = atoi(argv[2]);

		float m[6];
		// Matrix m looks like:
		//
		// [ m0  m1  m2 ] ===>  [ A11  A12   b1 ]
		// [ m3  m4  m5 ]       [ A21  A22   b2 ]
		//
		CvMat M = cvMat (2, 3, CV_32F, m);
		int w = src->width;
		int h = src->height;

		//仅仅旋转
		factor = 1;
		m[0] = (float) (factor * cos (-angle * CV_PI / 180.));
		m[1] = (float) (factor * sin (-angle * CV_PI / 180.));
		m[3] = -m[1];
		m[4] = m[0];
		// 将旋转中心移至图像中间
		m[2] = w * 0.5f;
		m[5] = h * 0.5f;
		//  dst(x,y) = A * src(x,y) + b
		cvZero (dst);
		cvGetQuadrangleSubPix (src, dst, &M);

		//计算信噪比
		CvScalar sum=cvSum(dst);  
		CvScalar mean=cvAvg(dst);  
		CvScalar stddev;  
		cvAvgSdv(dst,NULL,&stddev);  
		double psnr=20*log10(255/stddev.val[0]);  
		//printf("%lf\n",sum.val[0]);  
		//printf("%lf\n",mean.val[0]);  
		//printf("%lf\n",stddev.val[0]);  
		printf("信噪比:%lf\n",psnr);  

		
		cvNamedWindow ("dst", 1);
		cvShowImage ("dst", dst);
		cvWaitKey(0);

		cvDestroyWindow("dst");  
		cvReleaseImage(&dst );  
		return 0;
		
	}
	return 0;
}




/***********************************************************************
 * OpenCV 2.4.3 测试例程
 * 于仕琪 提供
 ***********************************************************************/
/*
#include "stdafx.h"
 
#include <opencv2/opencv.hpp>
 
using namespace std;
using namespace cv;
 

int _tmain(int argc, _TCHAR* argv[])
{
	const char* imagename = "lena.jpg";
 
	//从文件中读入图像
	Mat img = imread(imagename);
 
	//如果读入图像失败
	if(img.empty())
	{
		fprintf(stderr, "Can not load image %s\n", imagename);
		return -1;
	}
 
	//显示图像
	imshow("image", img);
 
	//此函数等待按键，按键盘任意键就返回
	waitKey();
 
	return 0;
}
*/