#include <stdint.h>
#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include  <conio.h>

int calcArea(const int xSizeArea, const int ySizeArea, int startingPoint, IplImage *img);
int comprare(const int xSizeArea, const int ySizeArea, int startingPointG, IplImage *img2, int f);

int main(int argc, char* argv[])
{
	const char* wName1 = "Pic1_L"; // window name 
	const char* wName2 = "Pic1_R"; // 
	const char* wNameC = "Combined"; // 
	cvNamedWindow(wName1, 0); // create simple window    
	cvNamedWindow(wName2, 0); // 
//	cvNamedWindow(wNameC, 0); // 



	IplImage *img1, *img2 = 0; // pointers to images 
	IplImage *imgC;// = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U, 1);
	img1 = cvLoadImage("PIC1_L.png", 0);
	img2 = cvLoadImage("PIC1_R.png", 0);
	imgC = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U, 1);


	const int xSizeArea = 10;
	const int ySizeArea = 10;
	int xStart = 25;
	int xStartF[20];
	int xStartG[20];
	int yStart = 12;
	int yStartF[20];
	int yStartG[20];

	int startingPointF = xStart + yStart * img1->widthStep;
	int startingPointG = 0;

	int f =0;
	int g = 0;
	int m1 = 1;

	for (size_t k = 0; k < 20; k++)
	{
		startingPointF = startingPointF + (img1->widthStep * (int)k/10);
		f = calcArea(xSizeArea, ySizeArea, startingPointF, img1);
		printf("f= %d \n", f);
		g = 0;
		m1 = 1;
		startingPointG = comprare(xSizeArea, ySizeArea, startingPointG, img2, f);

		xStartG[k] = startingPointG % img2->widthStep;
		yStartG[k] = startingPointG / img2->widthStep;
		xStartG[k] = xStartG[k] + 5;
		yStartG[k] = yStartG[k] + 5;

		xStartF[k] = startingPointF % img1->widthStep;
		yStartF[k] = startingPointF / img1->widthStep;
		xStartF[k] = xStartF[k] + 5;
		yStartF[k] = yStartF[k] + 5;
		
		cvLine(img1, cvPoint(xStartF[k] - 5, yStartF[k]  -5), cvPoint(xStartF[k] + 5, yStartF[k] + 5), cvScalar(255, 0, 0), 1);
		cvLine(img1, cvPoint(xStartF[k] + 5, yStartF[k] - 5), cvPoint(xStartF[k] - 5, yStartF[k] + 5), cvScalar(255, 0, 0), 1);
		cvLine(img2, cvPoint(xStartG[k] - 5, yStartG[k] - 5), cvPoint(xStartG[k] + 5, yStartG[k] + 5), cvScalar(255, 0, 0), 1);
		cvLine(img2, cvPoint(xStartG[k] + 5, yStartG[k] - 5), cvPoint(xStartG[k] - 5, yStartG[k] + 5), cvScalar(255, 0, 0), 1);
	}
	//cvRectangle(img2, cvPoint(xStartG[30] - 50, yStartG[30] - 50), cvPoint(xStartG[30] + 50, yStartG[30] + 50), cvScalar(255, 0, 0)	, 1);


	//printf("f= %d g= %d starting point g= %d xStart = %d yStart = %d \n", f, g, startingPointG, xStart, yStart);

	cvMoveWindow(wName2, 100, 100);
	cvResizeWindow(wName1, img1->width, img1->height);
	cvResizeWindow(wName2, img2->width, img2->height);

	while (1)
	{
		cvShowImage(wName1, img1);
		cvShowImage(wName2, img2);
		int quit = cvWaitKey(0);
		if (quit == 'q')
		{
			break;
		}
	}
	
	
	
	cvReleaseImage(&img1);
	cvReleaseImage(&img2);
	cvReleaseImage(&imgC);
	cvDestroyWindow(wName1);
	cvDestroyWindow(wName2);
//	cvDestroyWindow(wNameC);

	return 0;
}

int calcArea(const int xSizeArea, const int ySizeArea, int startingPoint, IplImage *img, IplImage *img2)
{
	//printf("%d Image width", img->widthStep);
	int areaImg1[10][10];
	int f=0;
	int n = 0;
	for (size_t x = 0; x < (xSizeArea); x++)
	{
		for (size_t y = 0; y < ySizeArea; y++)
		{	
			//printf("%d %d x=,y=", x, y);
			n = startingPoint + x + (y*img->widthStep);
			areaImg1[x][y] = img->imageData[n];
			
			f = f + abs(areaImg1[x][y]);
			//printf("areaImg1[%d][%d]= %d\n", x, y, areaImg1[x][y]);
		}
	}

	// calc g

	int g = 0;
	int m1 = 1;
	int areaImg2[10][10];

	startingPoint = 0;// startingPointG;
	while (m1 != 0)
	{
		startingPoint++;
		//g = calcArea(xSizeArea, ySizeArea, startingPoint, img2);


		g = 0;
		n = 0;
		for (size_t x = 0; x < (xSizeArea); x++)
		{
			for (size_t y = 0; y < ySizeArea; y++)
			{
				//printf("%d %d x=,y=", x, y);
				n = startingPoint + x + (y*img2->widthStep);
				areaImg2[x][y] = img2->imageData[n];

				m1 = m1 + abs(areaImg1[x][y] - areaImg2[x][y]);
				printf("areaImg1[%d][%d]= %d areaImg2[%d][%d]= %d\n", x, y, areaImg1[x][y], x, y, areaImg2[x][y]);
			}
		}






		//m1 = abs(f - g);
		if (startingPoint > ((img2->height - 10)* img2->width))
		{
			startingPoint = startingPoint;
			printf("end");
			break;
		}
	}
	//return startingPoint;



	return f;
}

int comprare(const int xSizeArea,  const int ySizeArea, int startingPointG, IplImage *img2, int f)
{
	int g = 0;
	int m1 = 1;

	int startingPoint = startingPointG;
	while (m1 != 0)
	{
		startingPoint++;
		g = calcArea(xSizeArea, ySizeArea, startingPoint, img2);
		m1 = abs(f - g);
		if (startingPoint > ((img2->height -10)* img2->width))
		{
			startingPoint = startingPointG;
			printf("end");
			break;
		}
	}
	return startingPoint;
}