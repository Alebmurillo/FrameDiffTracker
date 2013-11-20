#include "hogdetectorcpu.h"
#include <iostream>
#define WIN_X 32
#define WIN_Y 32
using namespace std;

HOGDetectorCPU::HOGDetectorCPU()
{
}

//More eficient version, designed for video processing
Mat* HOGDetectorCPU::detectPeople(Mat* ptrMat){
   Mat* ptrMatImage = ptrMat;
   vector<float> detector;
   vector<Rect> found;
   Size win_size(48, 96);
   cv::HOGDescriptor gpu_hog;
   //Sets the svm trained to detect people
   detector = cv::HOGDescriptor::getDefaultPeopleDetector();
   gpu_hog.setSVMDetector(detector);
   double hitThreshold = -0.5;
   Size sizeWinStride(8,8);
   double scale0 = 1.05;
   int groupThreshold = 2;
   gpu_hog.detectMultiScale(*ptrMat, found, hitThreshold, sizeWinStride, Size(32,32), scale0, groupThreshold);
   for(int i = 0; i < (int)found.size(); ++i){
       Rect current = found[i];
       rectangle(*ptrMatImage, current.tl(), current.br(),  CV_RGB(0, 255, 0), 3);
   }
   return ptrMatImage;
}

void HOGDetectorCPU::processVideo(char* ptrNameInput, char* ptrNameOutput){
    VideoCapture inputVideo(ptrNameInput);
    Mat* ptrMatOut;
    Mat* ptrMat;
    vector<Mat> spl;
    while(inputVideo.grab()){
        ptrMat = new Mat();
        inputVideo >> *ptrMat; // get a new frame from video
        Mat finalMat;
        split(*ptrMat, spl);
        cvtColor(*ptrMat, *ptrMat, CV_BGR2GRAY);
        ptrMatOut = detectPeople(ptrMat);
        spl[0] = *(ptrMatOut);
        spl[1] = *(ptrMatOut);
        spl[2] = *(ptrMatOut);
        //merge(spl, finalMat);
        imshow("HOG", *(ptrMatOut));
        if(waitKey(30) >= 0) break;
        //Deletes the processed frame
        delete ptrMatOut;
    }
 }
ImageImPro* HOGDetectorCPU::processImage(ImageImPro* ptrImage)
{
    Mat* ptrMatOut;
    vector<Mat> spl;
    Mat* ptrMat = ptrImage->getMat();
    Mat finalMat;
    split(*ptrMat, spl);
    cvtColor(*ptrMat, *ptrMat, CV_BGR2GRAY);
    ptrMatOut = detectPeople(ptrMat);
    spl[0] = *(ptrMatOut);
    spl[1] = *(ptrMatOut);
    spl[2] = *(ptrMatOut);
    merge(spl, finalMat);
    ImageImPro_OpenCvImpl* ptrImageProc = new ImageImPro_OpenCvImpl(ptrMatOut);
    return ptrImageProc;
}

