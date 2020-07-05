// Moravec.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat Srcimg = imread("D:\\lena.png", 0); 
	if (!Srcimg.data) {
		return -1;
	}
	Mat dst = imread("D:\\lena.png", -1);
	Mat Morimg = Srcimg.clone();
	int size = 5;
	int rsize = size / 2;

	const int Srows = Srcimg.rows;
	const int Scols = Srcimg.cols;

	int nCount = 0;
	CvPoint *p = new CvPoint[Srows * Scols];

	for (int i = rsize; i < Srcimg.rows - rsize; i++) {
		for (int j = rsize; j < Srcimg.cols - rsize; j++) {
			int v1, v2, v3, v4;
			v1 = v2 = v3 = v4 = 0;
			for (int k = -rsize; k < rsize; k++) { //ˮƽ������Ȥֵ
				v1 += (Srcimg.at<uchar>(i, j + k) - Srcimg.at<uchar>(i, j + k + 1) * (Srcimg.at<uchar>(i, j + k) - Srcimg.at<uchar>(i, j + k + 1)));
			}
			for (int k = -rsize; k < rsize; k++) { //��ֱ������Ȥֵ
				v2 += (Srcimg.at<uchar>(i + k, j) - Srcimg.at<uchar>(i + k + 1, j) * (Srcimg.at<uchar>(i + k, j) - Srcimg.at<uchar>(i + k + 1, j)));
			}
			for (int k = -rsize; k < rsize; k++) { //�Խ��߷�����Ȥֵ
				v3 += (Srcimg.at<uchar>(i + k, j + k) - Srcimg.at<uchar>(i + k + 1, j + k + 1) * (Srcimg.at<uchar>(i + k, j + k) - Srcimg.at<uchar>(i + k + 1, j + k + 1)));
			}
			for (int k = -rsize; k < rsize; k++) { //���Խ��߷�����Ȥֵ
				v4 += (Srcimg.at<uchar>(i + k, j - k) - Srcimg.at<uchar>(i + k + 1, j - k - 1) * (Srcimg.at<uchar>(i + k, j - k) - Srcimg.at<uchar>(i + k + 1, j - k - 1)));
			}

			int value = min(min(v1, v2), min(v3, v4)); //��СֵΪ���ص�������Ȥֵ
			int yu = 3000; //��ֵ
			if (value > yu) {
				p[nCount] = CvPoint(j, i);
				nCount++;
			}
		}
	}

	for (int i = 0; i < nCount; i++) { //���Ƶ�
		circle(dst, p[i], 2, Scalar(255, 0, 0));
	}
    //imshow("ԭͼ", Srcimg);
	imwrite("Moravec.png", dst);
	imshow("Moravec", dst);
	waitKey(0);
    return 0;
}

