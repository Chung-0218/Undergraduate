#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/ml/ml.hpp>
#include <vector>
#include <opencv2/core.hpp>

using namespace cv;
using namespace std;
using namespace cv::ml;

/*
int main() {
	CascadeClassifier cascade;
	cascade.load("C:/opencv 4.4.0/opencvsources/data/lbpcascades/lbpcascade_frontalface.xml");

	Mat img = imread("C:\\Users\\정현석\\Desktop\\정현석\\face.jpeg", 1);
	int height = img.rows;
	int width = img.cols;
	vector<Rect> faces;

	cascade.detectMultiScale(img, faces, 1.1, 4, 0 | CASCADE_SCALE_IMAGE, Size(10, 10));

	for (int y = 0; y < faces.size(); y++) {
		Point lb(faces[y].x + faces[y].width, faces[y].y + faces[y].height);
		Point tr(faces[y].x, faces[y].y);

		rectangle(img, lb, tr, Scalar(0, 255, 0), 3, 8, 0);

		for (int y = 1; y < height; y++) {
			for (int x = 1; x < width; x++) {
				int val = 0;
				if (img.at<uchar>(y, x) < img.at<uchar>(y - 1, x)) val += 1;
				if (img.at<uchar>(y, x) < img.at<uchar>(y - 1, x + 1)) val += 2;
				if (img.at<uchar>(y, x) < img.at<uchar>(y, x + 1)) val += 4;
				if (img.at<uchar>(y, x) < img.at<uchar>(y + 1, x + 1)) val += 8;
				if (img.at<uchar>(y, x) < img.at<uchar>(y + 1, x)) val += 16;
				if (img.at<uchar>(y, x) < img.at<uchar>(y + 1, x - 1)) val += 32;
				if (img.at<uchar>(y, x) < img.at<uchar>(y, x - 1)) val += 64;
				if (img.at<uchar>(y, x) < img.at<uchar>(y - 1, x - 1)) val += 128;

				img.at<uchar>(y, x) = val;
			}
		}
	}
	imshow("Face", img);
	waitKey(50000);

	return 0;
}
*/

