
#include "BodyCapture.h"

int main(int argc, char** argv)
{
	VideoCapture cap(0); //capture the video from webcam
	VideoCapture cap2(2);
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

	int iLowHB = 75;
	int iHighHB = 130;

	int iLowHG = 20;
	int iHighHG = 75;

	int iLowH = iLowHG;
	int iHighH = iHighHG;

	int iLowS = 119;  // original 150
	int iHighS = 255;

	int iLowV = 60;
	int iHighV = 255;

	//Create trackbars in "Control" window
	createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	createTrackbar("HighH", "Control", &iHighH, 179);

	createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	createTrackbar("HighS", "Control", &iHighS, 255);

	createTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
	createTrackbar("HighV", "Control", &iHighV, 255);

	int iLastX = -1;
	int iLastY = -1;

	//Capture a temporary image from the camera
	Mat imgTmp;
	cap.read(imgTmp);

	//Create a black image with the size as the camera output
	Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);

	Mat RedFiltImg = Mat::zeros(imgTmp.size(), CV_8UC3);
	Mat BlueFiltImg = Mat::zeros(imgTmp.size(), CV_8UC3);
	Mat GreenFiltImg = Mat::zeros(imgTmp.size(), CV_8UC3);

	// Initialize a body with 3 joints
	BodyCapture NewBody = BodyCapture(3);
	NewBody.JointArray[0] = Joint();
	NewBody.JointArray[1] = Joint();
	NewBody.JointArray[2] = Joint();
	//NewBody.JointArray[0] = joint1;
	JointLink sampleLink;
	JointLink sampleLink2;

	//Make connections
	sampleLink.ConnectJoints(&NewBody.JointArray[0], &NewBody.JointArray[2]);
	sampleLink.ConnectJoints(&NewBody.JointArray[2], &NewBody.JointArray[1]);

	//init joints

	//Blue Catch
	NewBody.JointArray[0].SetHue(iLowHB, iHighHB);
	NewBody.JointArray[0].SetSaturation(iLowS, iHighS);
	NewBody.JointArray[0].SetValue(iLowV, iHighV);
	NewBody.JointArray[0].SetJointType(0);
	//Red Catch
	NewBody.JointArray[1].SetHue(iLowHR, iHighHR);
	NewBody.JointArray[1].SetSaturation(iLowS, iHighS);
	NewBody.JointArray[1].SetValue(iLowV, iHighV);
	NewBody.JointArray[1].SetJointType(1);
	//Green Catch
	NewBody.JointArray[2].SetHue(iLowHG, iHighHG);
	NewBody.JointArray[2].SetSaturation(iLowS, iHighS);
	NewBody.JointArray[2].SetValue(iLowV, iHighV);
	NewBody.JointArray[2].SetJointType(2);


	//Start Loop
	while (true)
	{
		Mat imgOriginal;
		Mat imgOriginal2;
		Mat SkeletonDrawn = Mat::zeros(imgTmp.size(), CV_8UC3);  //Reset the value of the joints for every frame
		bool bSuccess = cap.read(imgOriginal); // read a new frame from video
		cap2.read(imgOriginal2); // read a new frame from video



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
		sampleLink.DrawLink(SkeletonDrawn);
		imgOriginal = imgOriginal + imgLines;
		imgOriginal = imgOriginal + SkeletonDrawn;
		imshow("Original", imgOriginal); //show the original image
		imshow("Original2", imgOriginal2); //show the original image

		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{ 
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}

	return 0;
}