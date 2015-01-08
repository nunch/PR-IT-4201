#include <iostream>
#include "highgui.h"
#include "cv.h"

int main(int argc, char const *argv[])
{
	int width = 50;
	int height = 50;
	IplImage *im_in = cvCreateImage(cvSize(64,64),  IPL_DEPTH_8U, 0);
	uchar* im_in_data = (uchar *) im_in->imageData;
	width = im_in-> widthStep;
	cvNamedWindow("Input", CV_WINDOW_AUTOSIZE);
    cvMoveWindow("Input", 0,0);
	for(int i=0;i<width*height;i++){
		im_in_data[i]=0;
		if(i%(width) == width/2) im_in_data[i] = 255;
	}



	std::cout << im_in->width << " "<< im_in->height << "\n" << im_in-> widthStep << " " << im_in->nChannels << std::endl;
	

	cvSaveImage("truc.png", im_in);
	cvShowImage( "Input", im_in);
	cvWaitKey(10);
	//cvSaveImage("bidule.png", im_in);
	while(1);
	cvDestroyWindow("Input");
	return 0;
}