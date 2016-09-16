#include "BodyCapture.h"

/*
JointList = new JointType[NITE_JOINT_COUNT]();
JointList[0] = JOINT_HEAD;
JointList[1] = JOINT_NECK;
JointList[2] = JOINT_LEFT_SHOULDER;
JointList[3] = JOINT_RIGHT_SHOULDER;
JointList[4] = JOINT_LEFT_ELBOW;
JointList[5] = JOINT_RIGHT_ELBOW;
JointList[6] = JOINT_LEFT_HAND;
JointList[7] = JOINT_RIGHT_HAND;
JointList[8] = JOINT_TORSO;
JointList[9] = JOINT_LEFT_HIP;
JointList[10] = JOINT_RIGHT_HIP;
JointList[11] = JOINT_LEFT_KNEE;
JointList[12] = JOINT_RIGHT_KNEE;
JointList[13] = JOINT_LEFT_FOOT;
JointList[14] = JOINT_RIGHT_FOOT;
*/

BodyCapture::BodyCapture()
{
	
}

BodyCapture::BodyCapture(int NJoints) {
	JointArray = new struct Joint[NJoints]();
}

BodyCapture::~BodyCapture()
{
}



// Set Joint Data
void Joint::SetHue(int minH, int maxH) {
	iLowH = minH;
	iHighH = maxH;
}

void Joint::SetValue(int minV, int maxV) {
	iLowV = minV;
	iHighV = maxV;
}

void Joint::SetSaturation(int minS, int maxS) {
	iLowS = minS;
	iHighS = maxS;
}

void Joint::SetJointType(int theType) {

	if (theType >= 0 && theType <= 14)
		type = theType;

	else
		cout << "Invalid Joint ID: "<< theType << ". Choose a number between 0-14. " << endl;
}

/// <param> HSVImage an image already converted into the HSV color space
/// </param>
/// <summary> Filter the image
/// </summary>
void Joint::CreateFilteredImage(Mat HSVImage, bool display) {
	//cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);
	inRange(HSVImage, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), theFilteredImage);
	
	//morphological opening (removes small objects from the foreground)
	erode(theFilteredImage, theFilteredImage, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(theFilteredImage, theFilteredImage, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	//morphological closing (removes small holes from the foreground)
	dilate(theFilteredImage, theFilteredImage, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(theFilteredImage, theFilteredImage, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));


	// Keep the largest object
	vector<vector<Point>> contours; // Vector for storing contour
	vector<Vec4i> hierarchy;
	int largest_area = 0;
	int largest_contour_index = 0;
	Rect bounding_rect;
	Mat dst(HSVImage.rows, HSVImage.cols, CV_8UC1, Scalar::all(0));


	findContours(theFilteredImage, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE); // Find the contours in the image

	

	for (int i = 0; i< contours.size(); i++) // iterate through each contour. 
	{
		double a = contourArea(contours[i], false);  //  Find the area of contour
		if (a>largest_area) {
			largest_area = a;
			largest_contour_index = i;                //Store the index of largest contour
													  //bounding_rect = boundingRect(contours[i]); // Find the bounding rectangle for biggest contour
		}

	}


	Scalar color(255, 255, 255);
	drawContours(dst, contours, largest_contour_index, color, CV_FILLED, 8, hierarchy); // Draw the largest contour using previously stored index.
		
	//rectangle(src, bounding_rect, Scalar(0, 255, 0), 1, 8, 0);
	vector<Point> WhitePixels;
	findNonZero(dst, WhitePixels);	
//imshow("src", src);
	//cout << "Cloud all white pixels: " << WhitePixels.size() << endl;
	if (WhitePixels.size() < 500) {
		cout << "Joint "<< type << endl;
	}


	if (display) {
		char str[10];
		char str2[100];
		char*temp = "largest Contour Joint";
		//strcpy_s(str2, temp);
		//_itoa_s(type, str,100,10);
		//strcat_s(str2, str);
		imshow(temp, dst);
	}


}



void Joint::UpdatePoint2DUsingMoments(Mat imgline, bool draw) {
	Moments oMoments = moments(theFilteredImage);
	double dM01 = oMoments.m01;
	double dM10 = oMoments.m10;
	aArea = oMoments.m00;

	// if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
	if (aArea > 100)
	{
		//calculate the position of the ball
		posX = dM10 / aArea;
		posY = dM01 / aArea;

		if (prevPosX >= 0 && prevPosY >= 0 && posX >= 0 && posY >= 0 && draw)
		{
			Mat provisionalImg = Mat::zeros(imgline.size(), CV_8UC3);
			//Draw a red line from the previous point to the current point
			line(provisionalImg, Point(posX, posY), Point(prevPosX, prevPosY), Scalar(0, 0, 255), 2);
			imgline = provisionalImg + imgline;
		}

		//cout << "Old Y:" << prevPosY << "New Y :" << posY << endl;
		//cout << "Old X:" << prevPosX << "New X :" << posX << endl;
		prevPosX = posX;
		prevPosY = posY;


	}
	else
		cout << "Ignored a the new position" << endl;
}

/*
*/
void Joint::DrawJointLine(Mat imgline) {
	if (aArea > 100){
		if (prevPosX >= 0 && prevPosY >= 0 && posX >= 0 && posY >= 0)
		{
			//Draw a red line from the previous point to the current point
			line(imgline, Point(posX, posY), Point(prevPosX, prevPosY), Scalar(0, 0, 255), 2);
		}
		cout << "Old Y:" << prevPosY << "New Y :" << posY << endl;
		cout << "Old X:" << prevPosX << "New X :" << posX << endl;
		prevPosX = posX;
		prevPosY = posY;


	}
	else
		cout << "Ignored a the new position" << endl;
}

void JointLink::ConnectJoints(Joint* An, Joint* Bn) {

	A = An;
	B = Bn;
	Connected = true;
	color = Scalar(140, 300, 140);
}


void JointLink::DrawLink(Mat imgLine) {


	Point origin = Point(A->posX, A->posY);
	Point destiny = Point(B->posX, B->posY);
	line(imgLine, origin, destiny, color, 2);
}

void BodyCapture::setMainDepth(float B) {
	mainDepth = B;
}

