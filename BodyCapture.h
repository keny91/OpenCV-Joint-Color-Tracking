#pragma once

#include <iostream>
#include "disparity_filters.h"
#include <F:\opencv\MyBuild\install\include\opencv2\opencv.hpp>
#include <F:\opencv\MyBuild\install\include\opencv\highgui.h>


#include "F:\opencv\MyBuild\install\include\opencv2\calib3d.hpp"
#include "F:\opencv\MyBuild\install\include\opencv2\imgproc.hpp"
#include "F:\opencv\MyBuild\install\include\opencv2\imgcodecs.hpp"
#include "F:\opencv\MyBuild\install\include\opencv2\core\utility.hpp"
//#include "F:\opencv\MyBuild\install\include\opencv2\ximgproc.hpp"
//#include "opencv2/ximgproc/disparity_filter.hpp"



using namespace cv;
using namespace std;


#define CAMERA_RESOLUTION_X 640
#define CAMERA_RESOLUTION_Y 480

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



struct Joint {
private:
	//Hue;
	int iLowH;
	int iHighH;
	//Saturation
	int iLowS;
	int iHighS;
	//Value
	int iLowV;
	int iHighV;
	//type of joint
	int type;

	
	double aArea;


public:
	Joint() {
	};


	int posX, posY;
	int prevPosX, prevPosY;


	Mat theFilteredImage;
	void SetHue(int minH, int maxH);
	void SetValue(int minv, int maxv);
	void SetSaturation(int minH, int maxH);
	void SetJointType(int type);
	bool Detected;
	void CreateFilteredImage(Mat HSVImage, bool display);
	void UpdatePoint2DUsingMoments(Mat imgline, bool draw);
	void DrawJointLine(Mat imgline);
};


struct JointLink {
public:
	bool Connected;
	bool Detected;
	Scalar color; 
	void ConnectJoints(Joint* A, Joint* B);
	void DrawLink(Mat imgLine);

private:
	float distance;  // Will require conversions
	int JointA;
	int JointB;
	float z;
	Joint* A;
	Joint* B;
	//int intDistance;
};

class BodyCapture
{

private:
	int MaxBodyJointStored;
	
public:

	struct Joint* JointArray;
	struct JointLink* JointLinkArray;
	float mainDepth;
	void setMainDepth(float B);
	BodyCapture();
	BodyCapture(int NJoints);
	~BodyCapture();
};



class StereoDepth
{

private:
	int MaxBodyJointStored;

public:
	StereoDepth();
	//void GenerateDepthMap(Mat LeftSidedImg, Mat RightSidedImg );
	Mat DepthMap;
	float mainDepth;
	void setMainDepth(float B);

};

//Mat GenerateDepthMap(Mat LeftSidedImg, Mat RightSidedImg);
StereoBM* GenerateDepthMap(Mat leftimg, Mat rightimg, int numDisparities=16, int blockSize=2);