#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

String face_cascade = "C:\\opencv 4.4.0\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalcatface.xml";
String eye_cascade = "C:\\opencv 4.4.0\\opencv\\sources\\data\\haarcascades\\haarcascade_eye.xml";
CascadeClassifier face;
CascadeClassifier eye;

/*
void FaceAndEyeDetect(Mat);

// ����

int main() {
	Mat f = imread("C:\\Users\\������\\Desktop\\������\\������.jpg");
	assert(f.data);

	bool b1 = face.load(face_cascade); // ��
	bool b2 = eye.load(eye_cascade);   // ��
	assert(b1 && b2);
	FaceAndEyeDetect(f);

	waitKey();
	return 0;
}


// ķ
/*
int main() {
	VideoCapture v(0);
	assert(v.isOpened());

	bool b1 = face.load(face_cascade);
	bool b2 = face.load(face_cascade);
	assert(b1 && b2);

	Mat frame;

	while (true) {
		v.read(frame);
		FaceAndEyeDetect(frame);

		if ((char)waitKey(20) == 27)
			break;
	}
	return 0;
}
*/

/*
void FaceAndEyeDetect(Mat img) {
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	std::vector<Rect> face_pos;
	face.detectMultiScale(gray, face_pos, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(10, 10));

	for (int i = 0; i < face_pos.size(); i++) {
		rectangle(img, face_pos[i], Scalar(255, 0, 0), 2);
	}

	// �� ����
	for (int i = 0; i < face_pos.size(); i++) {
		std::vector<Rect> eye_pos;
		Mat roi = gray(face_pos[i]);

		eye.detectMultiScale(roi, eye_pos, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(10, 10));

		for (int j = 0; j < eye_pos.size(); j++) {
			Point center(face_pos[i].x + eye_pos[j].x + eye_pos[j].width * 0.5, face_pos[i].y + eye_pos[j].y + eye_pos[j].height * 0.5);
			int radius = cvRound((eye_pos[j].width + eye_pos[j].height) * 0.25);
			circle(img, center, radius, Scalar(0, 0, 255), 2, 8, 0);
		}
	}
	namedWindow("�� ����");
	imshow("�� ����", img);
}
*/

// �˰������� 14���� OpenCV

int main() {

	Mat imgColor = imread("C:\\Users\\������\\Desktop\\������\\������.jpg", 1);
	Mat imgGray = imread("C:\\Users\\������\\Desktop\\������\\������.jpg", 0);

	imshow("color", imgColor);
	imshow("gray", imgGray);

	waitKey(5000);

	return 0;
}