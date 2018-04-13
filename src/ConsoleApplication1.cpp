// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;


int main()
{
	printf("%s\n", CV_VERSION);

	Mat imagine;
	Mat img_gray;

	imagine = imread("F:/Hough/hough/data/doualinii.png");
	cvtColor(imagine, img_gray, COLOR_BGR2GRAY);

	cvNamedWindow("fereastra");

	int diagonala = sqrt(img_gray.rows * img_gray.rows + img_gray.cols * img_gray.rows) + 1;

	int **accumulator;
	accumulator = new int *[diagonala];

	//alocam memorie dinamic
	for (int i = 0; i < diagonala; i++) {
		accumulator[i] = new int[180];
	}//gata

	//aici vine codul.


	//initializare
	for (int i = 0; i < diagonala; i++) {
		for (int j = 0; j < 180; j++) {
			accumulator[i][j] = 0;
		}
	}


	for (int y = 0; y < img_gray.rows; y++) {
		for (int x = 0; x < img_gray.cols; x++) {
			unsigned char culoare = img_gray.at<unsigned char>(y, x);
			if (culoare < 255) {
				for (int theta = 0; theta < 180; theta++) {
					double r = x * cos(theta / 180 * 3.14) + y * sin(theta / 180 * 3.14);
					accumulator[int(r)][theta]++;
				}
			}
		}
	}


	// calculare maxim din accumulator
	int maxacc = 0;
	for (int r = 0; r < diagonala; r++) {
		for (int theta = 0; theta < 180; theta++) {
			if (maxacc < accumulator[r][theta]) {
				maxacc = accumulator[r][theta];
			}
		}
	}

	//scalare accumulator la 0-255
	for (int r = 0; r < diagonala; r++) {
		for (int theta = 0; theta < 180; theta++) {
			accumulator[r][theta] = accumulator[r][theta] / (double)maxacc * 255;
		}
	}

	// creez imagine
	Mat acc_grafic(diagonala, 180, CV_8UC1);


	//populez imaginea
	for (int r = 0; r < diagonala; r++) {
		for (int theta = 0; theta < 180; theta++) {
			acc_grafic.at<unsigned char>(r, theta) = accumulator[r][theta];
		}
	}

	cvNamedWindow("accumulator");
	imshow("accumulator", acc_grafic);

	// aici golim memoria alocata dinamic
	for (int i = 0; i < diagonala; i++) {
		delete[] accumulator[i];
	}
	delete[] accumulator;
	// pana aici 

	imshow("fereastra", imagine);

	cvWaitKey();

	return 0;

}

