#include<opencv2\opencv.hpp>
#include<vector>

using namespace cv;
using namespace std;
int main() {

	double scale =  3.0;
	CascadeClassifier faceCascade;
	faceCascade.load("D:\\Desktop\\opencvcpp\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_default.xml");


	VideoCapture cap(0);
	if (!cap.isOpened())
		return -1;
	// infinite loop
	for (;;)
	{     //matrix object
		Mat frame;
		cap >> frame;

		Mat grayscale;
		cvtColor(frame, grayscale, COLOR_BGR2GRAY);
		//resize to improve efficiency
		resize(grayscale, grayscale, Size(grayscale.size().width / scale, grayscale.size().height / scale));

		//all the results stored in vector

		vector<Rect> faces;
		faceCascade.detectMultiScale(grayscale, faces, 1.1, 3, 0, Size(30, 30));

		for (Rect area : faces)
		{
			Scalar drawColor = Scalar(250, 0, 0);
			//image to be detected=frame,points are top left and bottom right corner,color of rectangle
			rectangle(frame, Point(cvRound(area.x * scale), cvRound(area.y * scale)),
				Point(cvRound((area.x + area.width - 1) * scale), cvRound((area.y + area.height - 1) * scale)), drawColor);

			rectangle(frame, Point(0, 0), Point(230, 70), Scalar(250, 0, 0), FILLED);

			putText(frame, to_string(faces.size())+" Face Found", Point(10, 40), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255), 1);


			
		}

	
         imshow("Webcam Window", frame); //name of window

		if (waitKey(30) >= 0)
			break;
	}


	return 0;
}