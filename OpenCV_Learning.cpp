// OpenCV_Learning.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cv.h>
#include <highgui.h>

int main()
{
    CvCapture* capture;
    IplImage* image;

	int i, j;
	int index, nCount;
	int DrawX, DrawY;

    capture = cvCaptureFromCAM(0);
    cvNamedWindow("White Tracking", 0);
    cvResizeWindow("White Tracking", 320, 240);

	if (capture) {
		while(1) {
			cvGrabFrame(capture);
			image = cvRetrieveFrame(capture);
			nCount = 1;
			DrawX = 0; DrawY = 0;

			//BGR순으로 3채널 영상
			//lplimage->imgedata에서 색상을 축출 할 수 있다.
			for (i=0; i<image->height; i++) {
				for (j=0; j<image->widthStep; j+=image->nChannels) {
					index = i * image->widthStep + j;

					//RGB순으로 200이상의 색상을 검출 한다.
					if (((unsigned char)image->imageData[index+2] > 200) 
						&& ((unsigned char)image->imageData[index+1] > 200) 
						&& ((unsigned char)image->imageData[index] > 200)) {
						nCount++; //축출 카운팅
						DrawX += j/3;
						DrawY += i;
					}
				}
			}

			//좌표값의 총합과 축출 카운터 합을 나누면 중간점이 계산됨
			DrawX /= nCount;
			DrawY /= nCount;

			if (nCount > 1)
				cvCircle(image, cvPoint(DrawX, DrawY), 10, cvScalar(0,255,0),2);
			cvShowImage("White Tracking", image);

			if (cvWaitKey(10) >= 0) break;
		}
	}

	cvReleaseCapture(&capture);
    cvDestroyWindow("White Tracking");

	return 0;
}