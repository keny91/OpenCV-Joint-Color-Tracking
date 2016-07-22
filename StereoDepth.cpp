#include "BodyCapture.h"

Mat GenerateDepthMap(Mat LeftSidedImg, Mat RightSidedImg) {


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

	/*We perform downscaling of the views to speed-up the matching stage at the cost of minor quality degradation. 
	To get the best possible quality downscaling should be avoided.*/
	Mat left_for_matcher, right_for_matcher;
	max_disp /= 2;
	if (max_disp % 16 != 0)
		max_disp += 16 - (max_disp % 16);
	resize(left, left_for_matcher, Size(), 0.5, 0.5);
	resize(right, right_for_matcher, Size(), 0.5, 0.5);



	/*We are using StereoBM for faster processing. If speed is not critical, though, StereoSGBM would provide better quality. The filter instance is created by providing the StereoMatcher instance that we intend to use. Another matcher instance is returned by the createRightMatcher function. These two matcher instances are then used to compute disparity maps both for the left and right views, that are required by the filter.
*/
	Ptr<StereoBM> left_matcher = StereoBM::create(max_disp, wsize);
	wls_filter = createDisparityWLSFilter(left_matcher);
	Ptr<StereoMatcher> right_matcher = createRightMatcher(left_matcher);
	cvtColor(left_for_matcher, left_for_matcher, COLOR_BGR2GRAY);
	cvtColor(right_for_matcher, right_for_matcher, COLOR_BGR2GRAY);
	matching_time = (double)getTickCount();
	left_matcher->compute(left_for_matcher, right_for_matcher, left_disp);
	right_matcher->compute(right_for_matcher, left_for_matcher, right_disp);
	matching_time = ((double)getTickCount() - matching_time) / getTickFrequency();

}