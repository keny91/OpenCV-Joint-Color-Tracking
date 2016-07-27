
#include "BodyCapture.h"

<<<<<<< HEAD
=======
int main(int argc, char** argv)
{
	VideoCapture cap(0); //capture the video from webcam

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	/*
	In the above application, I have considered that the red object has HUE, SATURATION and VALUE in between 170-180, 160-255, 60-255 respectively. Here the HUE is unique for that specific color distribution of that object. But SATURATION and VALUE may be vary according to the lighting condition of that environment.

Hue values of basic colors
Orange  0-22
Yellow 22- 38
Green 38-75
Blue 75-130
Violet 130-160
Red 160-179

*/


	//TO DO::
// Only draw the positions of the joints when 


	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"



	int iLowHR = 170;
	int iHighHR = 179;
>>>>>>> parent of d1bd961... Added Stereo  Vision

#include "F:\opencv3\build\install\include\opencv2\calib3d.hpp"
#include "F:\opencv3\build\install\include\opencv2\core\core.hpp"

#include <F:\opencv3\build\install\include\opencv2\highgui\highgui.hpp>
#include "F:\opencv3\build\install\include\opencv2\imgproc\imgproc.hpp"
#include "F:\opencv3\build\install\include\opencv2\imgproc.hpp"


#include <stdio.h>
#include <string.h>
using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	Mat img1, img2, g1, g2;
	Mat disp, disp8;

	//char* method = argv[3];
	char* method = "SGBM";

	//img1 = imread(argv[1]);
	//img2 = imread(argv[2]);
	img1 = imread("leftImage.jpg");
	img2 = imread("rightImage.jpg");

<<<<<<< HEAD
	cvtColor(img1, g1, CV_BGR2GRAY);
	cvtColor(img2, g2, CV_BGR2GRAY);

	if (!(strcmp(method, "BM")))
	{
		StereoBM sbm;
		sbm.state->SADWindowSize = 9;
		sbm.state->numberOfDisparities = 112;
		sbm.state->preFilterSize = 5;
		sbm.state->preFilterCap = 61;
		sbm.state->minDisparity = -39;
		sbm.state->textureThreshold = 507;
		sbm.state->uniquenessRatio = 0;
		sbm.state->speckleWindowSize = 0;
		sbm.state->speckleRange = 8;
		sbm.state->disp12MaxDiff = 1;
		sbm(g1, g2, disp);
	}
	else if (!(strcmp(method, "SGBM")))
	{
		StereoSGBM sbm;
		sbm.SADWindowSize = 3;
		sbm.numberOfDisparities = 144;
		sbm.preFilterCap = 63;
		sbm.minDisparity = -39;
		sbm.uniquenessRatio = 10;
		sbm.speckleWindowSize = 100;
		sbm.speckleRange = 32;
		sbm.disp12MaxDiff = 1;
		sbm.fullDP = false;
		sbm.P1 = 216;
		sbm.P2 = 864;
		sbm(g1, g2, disp);
	}
=======
	// Initialize a body with 3 joints
	BodyCapture NewBody = BodyCapture(3);
	NewBody.JointArray[0] = Joint();
	NewBody.JointArray[1] = Joint();
	NewBody.JointArray[2] = Joint();
	//NewBody.JointArray[0] = joint1;
>>>>>>> parent of d1bd961... Added Stereo  Vision


	normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);

	imshow("left", img1);
	imshow("right", img2);
	imshow("disp", disp8);

<<<<<<< HEAD
	waitKey(0);
=======
	//Start Loop
	while (true)
	{
		Mat imgOriginal;
		Mat SkeletonDrawn = Mat::zeros(imgTmp.size(), CV_8UC3);  //Reset the value of the joints for every frame
		bool bSuccess = cap.read(imgOriginal); // read a new frame from video



		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		Mat imgHSV;

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		Mat imgThresholded;
		Mat BlueThresholdedImg;
		Mat RedThresholdedImg;
		Mat GreenThresholdedImg;

		//inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

		


		

		NewBody.JointArray[0].CreateFilteredImage(imgHSV, true);
		NewBody.JointArray[0].UpdatePoint2DUsingMoments(imgLines, true);
		NewBody.JointArray[0].DrawJointLine(imgLines);

/**/
		//Red Catch
		

		//NewBody.JointArray[1].CreateFilteredImage(imgHSV);
		//NewBody.JointArray[1].UpdatePoint2DUsingMoments(imgLines, true);
		//NewBody.JointArray[1].DrawJointLine(imgLines, true);
		//NewBody.JointArray[1].CreateFilteredImage(imgHSV);

		//Green Catch
		

		NewBody.JointArray[2].CreateFilteredImage(imgHSV,false);
		NewBody.JointArray[2].UpdatePoint2DUsingMoments(imgLines, true);

		
		/*
		//Calculate the moments of the thresholded image
		//Moments oMoments = moments(imgThresholded);
		Moments oMoments = moments(NewBody.JointArray[0].theFilteredImage);
		double dM01 = oMoments.m01;
		double dM10 = oMoments.m10;
		double dArea = oMoments.m00;

		// if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
		
		if (dArea > 50)
		{
			//calculate the position of the ball

			int posX = dM10 / dArea;
			int posY = dM01 / dArea;
			cout << "Old Y:" << iLastY << "  New Y :" << posY << endl;
			cout << "Old X:" << iLastX << "  New X :" << posX << endl;
			if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
			{
				//Draw a red line from the previous point to the current point
				line(imgLines, Point(posX, posY), Point(iLastX, iLastY), Scalar(0, 0, 255), 2);
			}

			iLastX = posX;
			iLastY = posY;
		}
		*/

		//imshow("Thresholded Image", imgThresholded); //show the thresholded image

		imgOriginal = imgOriginal + imgLines;
		imshow("Original", imgOriginal); //show the original image

		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
>>>>>>> parent of d1bd961... Added Stereo  Vision

	return(0);