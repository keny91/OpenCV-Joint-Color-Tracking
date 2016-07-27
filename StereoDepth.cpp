#include "BodyCapture.h"
#include "disparity_filters.h"
#include "edge_filter.h"

StereoBM* GenerateDepthMap(Mat leftimg, Mat rightimg, int numDisparities, int blockSize) {



	//Mat stereo = cv::StereoBM_create(numDisparities = 16, blockSize = 15);


	//cv::Mat leftimg = cv::imread("leftimage.jpg");
	//cv::Mat rightimg = cv::imread("rightimage.jpg");
	cv::Size imagesize = leftimg.size();
	cv::Mat g1, g2, disp, disp8;
	cv::cvtColor(leftimg, g1, cv::COLOR_BGR2GRAY);
	cv::cvtColor(rightimg, g2, cv::COLOR_BGR2GRAY);

	//cv::StereoBM *sbm = cv::createStereoBM(16, 2);
	StereoBM *sbm = StereoBM::create(numDisparities, blockSize);
	sbm->setDisp12MaxDiff(1);
	sbm->setSpeckleRange(8);
	sbm->setSpeckleWindowSize(0);
	sbm->setUniquenessRatio(0);
	sbm->setTextureThreshold(507);
	sbm->setMinDisparity(-39);
	sbm->setPreFilterCap(61);
	sbm->setPreFilterSize(5);
	sbm->compute(g1, g2, disp);
	normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);

	cv::imshow("left", leftimg);
	cv::imshow("right", rightimg);
	cv::imshow("disp", disp8);

	return sbm;
		/*
		//We start by loading the source stereopair. For this tutorial we will take a somewhat challenging example from the MPI-Sintel dataset with a lot of texture-less regions.
		//Mat left = imread(left_im, IMREAD_COLOR);
		if (LeftSidedImg.empty())
		{
			cout << "Cannot read image file: " << left_im;
			return -1;
		}
		//Mat right = imread(right_im, IMREAD_COLOR);
		if (RightSidedImg.empty())
		{
			cout << "Cannot read image file: " << right_im;
			return -1;
		}





		//We perform downscaling of the views to speed-up the matching stage at the cost of minor quality degradation.
		//To get the best possible quality downscaling should be avoided.
		Mat left_for_matcher, right_for_matcher;
		max_disp /= 2;
		if (max_disp % 16 != 0)
			max_disp += 16 - (max_disp % 16);
		resize(left, left_for_matcher, Size(), 0.5, 0.5);
		resize(right, right_for_matcher, Size(), 0.5, 0.5);



		//We are using StereoBM for faster processing. If speed is not critical, though, StereoSGBM would provide better quality. The filter instance is created by providing the StereoMatcher instance that we intend to use. Another matcher instance is returned by the createRightMatcher function. These two matcher instances are then used to compute disparity maps both for the left and right views, that are required by the filter.

		Ptr<StereoBM> left_matcher = StereoBM::create(max_disp, wsize);
		wls_filter = createDisparityWLSFilter(left_matcher);
		Ptr<StereoMatcher> right_matcher = createRightMatcher(left_matcher);
		cvtColor(left_for_matcher, left_for_matcher, COLOR_BGR2GRAY);
		cvtColor(right_for_matcher, right_for_matcher, COLOR_BGR2GRAY);
		matching_time = (double)getTickCount();
		left_matcher->compute(left_for_matcher, right_for_matcher, left_disp);
		right_matcher->compute(right_for_matcher, left_for_matcher, right_disp);
		matching_time = ((double)getTickCount() - matching_time) / getTickFrequency();
		*/


	int max_disp = 16;
	bool no_downscale = false;
	Rect computeROI(Size2i src_sz, Ptr<StereoMatcher> matcher_instance);
	int wsize = 15;


	Mat left = leftimg;
	Mat Right = rightimg;

	bool noGT;
	Mat GT_disp;
	noGT = false; // no evaluation

	Mat left_for_matcher, right_for_matcher;
	Mat left_disp, right_disp;
	Mat filtered_disp;
	Mat conf_map = Mat(left.rows, left.cols, CV_8U);
	conf_map = Scalar(255);
	Rect ROI;
	//aaaaaaaaaaaaaaaPtr<DisparityWLSFilter> wls_filter;
	double matching_time, filtering_time;



	if (!no_downscale)
	{
		// downscale the views to speed-up the matching stage, as we will need to compute both left
		// and right disparity maps for confidence map computation
		//! [downscale]
		max_disp /= 2;
		if (max_disp % 16 != 0)
			max_disp += 16 - (max_disp % 16);
		resize(left, left_for_matcher, Size(), 0.5, 0.5);
	/////////////////////////	resize(right, right_for_matcher, Size(), 0.5, 0.5);
		//! [downscale]
	}
	else
	{
		left_for_matcher = left.clone();
	//////////////////	right_for_matcher = right.clone();
	}


}