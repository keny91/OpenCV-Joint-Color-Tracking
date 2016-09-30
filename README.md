# OpenCV-Joint-Color-Tracking

This is a project is meant to be a parallel project to [Kinect-Rehab-Experiment](https://github.com/keny91/Kinect-Rehab-Experiment), using OpenCV instead of NiTE2. 


## Color Band Recognition

The will be a different set of color bands that should be worn in the shoulder, elbow and wrist (Red, blue and green respectively).
To have a proper detection, we require that the colors are disposed inside its respective ranges (represented in HSV color space): red[(345,100,100),(11,100,100)]; blue[(214,100,100),(234,100,100)]; green[(92,100,100),(121,100,100)].

We will be using our own algorithm to create a virtual skeleton tiying together the joints represented by the color bands. Then we will draw lines representing the skeleton bones.



# TO DO LIST
## Smoothing Algorithm

The joint detection is unstable at the moment. The points change after every frame making the linking bones to constantly chance

## Depth map extraction

Using the disparity of the capture system we can compute a depth image.

## Stable Skeleton display

More solid than we already have implemented.

## Calibration 

## Create a NiTE skeleton
and test compatibility with [Kinect-Rehab-Experiment](https://github.com/keny91/Kinect-Rehab-Experiment).
