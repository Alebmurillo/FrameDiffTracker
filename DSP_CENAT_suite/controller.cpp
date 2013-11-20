#include "controller.h"
#include <time.h>

#include <stdio.h>

#include <iostream>     //for using cout
#include <stdlib.h>
#include <time.h>

using namespace std;


Controller::Controller(){
     this->ptrImage = NULL;
     this->ptrVideo = NULL;
     this->ptrHogVideo = new HOGDetectorCPU();
     this->ptrLib = new OpenImProLib_OpenCvImpl();     
     this->ptrSegVideo = new BackgroundSegmentatorAGMM();
}

void Controller::loadVideo(char* ptrPath){
    if(this->ptrVideo != NULL){
        delete this->ptrVideo;
    }
    this->ptrVideo = new VideoImPro_OpenCvImpl(ptrPath);
    if(this->ptrVideo == NULL){
        throw ControllerException("Invalid video name");
    }
    ImageImPro* ptrFrame = this->ptrVideo->getNextFrame();
    this->ptrCurrVideoImage = ptrFrame;

}

void Controller::playVideo(){
    ImageImPro* ptrFrame = this->ptrVideo->getNextFrame();
    if(this->ptrCurrVideoImage != NULL){
        delete this->ptrCurrVideoImage;
    }
    this->ptrCurrVideoImage = ptrFrame;
}
void Controller::playVideoHog(QString fileName){

    VideoCapture inputVideo(fileName.toStdString());
    Mat* ptrMatOut;
    Mat* ptrMat;
    vector<Mat> spl;
    while(inputVideo.grab()){
        ptrMat = new Mat();
        inputVideo >> *ptrMat; // get a new frame from video
        Mat finalMat;
        split(*ptrMat, spl);
        cvtColor(*ptrMat, *ptrMat, CV_BGR2GRAY);
        ptrMatOut = this->ptrHogVideo->detectPeople(ptrMat);
        spl[0] = *(ptrMatOut);
        spl[1] = *(ptrMatOut);
        spl[2] = *(ptrMatOut);
        merge(spl, finalMat);
        imshow("HOGs", *(ptrMatOut));
        if(waitKey(30) >= 0) break;
        //Deletes the processed frame
        delete ptrMatOut;
    }
}




void Controller::playVideoSegmented(){

    cout << "Entro" << endl;
    cv::Mat frame;

    cv::Mat bilF;

    cv::VideoCapture cap("../input/videos/video.mp4");

    cv::BackgroundSubtractorMOG2 bg(500, 20, false);

    bg.set("nmixtures", 3);

    cv::namedWindow("Contours");

    for(;;)

    {
        cap >> frame;
        int winDiameter = 9; double sigmaRange = 38; double sigmaSpace = 8;
        bilateralFilter( frame, bilF, winDiameter, sigmaRange, sigmaSpace);
        frame = bilF;
        cv::Mat * pnt_frame = &bilF;
        ImageImPro_OpenCvImpl * outframe = new ImageImPro_OpenCvImpl(pnt_frame);
        vector<ImageImPro*> foreground = this->ptrSegVideo->substractForegroundMasks(outframe,2.0,2);
        ImageImPro_OpenCvImpl imageN = foreground[0];
        Mat* imageNN = imageN.getMat();
        cv::imshow("Contours",*(imageNN));
        if(cv::waitKey(30) >= 0) break;
    }

}
void Controller::loadImage(char* ptrPath)throw (ControllerException){
    if(this->ptrImage != NULL){
        delete this->ptrImage;
    }
    this->ptrImage = new ImageImPro_OpenCvImpl(ptrPath);
    if(this->ptrImage == NULL){
        throw ControllerException("Invalid image name");
    }

}

void Controller::applyFilterCanny()throw (ControllerException){
    if(this->ptrImage != NULL){
        ImageImPro* ptrImageCanny = this->ptrLib->filterCanny(this->ptrImage, 10, 500, 3);
        delete this->ptrImage;
        ptrImage = ptrImageCanny;
    }
    else{
         throw ControllerException("No image loaded");
    }
 }

void Controller::applyBilateral()throw (ControllerException){
    if(this->ptrImage != NULL){
        ImageImPro* ptrImageBilateralFilter=this->ptrLib->filterBilateral(this->ptrImage, 14, 7, 10 );
        delete this->ptrImage;
        ptrImage = ptrImageBilateralFilter;        
    }
    else{
         throw ControllerException("No image loaded");
    }

}


void Controller::applyFilterSobel()throw (ControllerException){
     if(this->ptrImage != NULL){         
         ImageImPro* ptrImageSobel = this->ptrLib->filterSobel(ptrImage, 1, 1, 3);
         delete this->ptrImage;
         ptrImage = ptrImageSobel;
     }
     else{
         throw ControllerException("No image loaded");
     }
 }

void Controller::applyFilterGauss()throw (ControllerException){
    if(this->ptrImage != NULL){
        ImageImPro* ptrImageGauss = this->ptrLib->filterGauss(this->ptrImage, 0, 0, 11);
        delete this->ptrImage;
        ptrImage = ptrImageGauss;
    }
    else{
        throw ControllerException("No image loaded");
    }

}
void Controller::convertToHSV()throw (ControllerException){
    if(this->ptrImage != NULL){
        ImageImPro* ptrImageHSV = this->ptrImage->getHSV();
        cout<<"hizo la transcripcion RNA"<<endl;
        delete this->ptrImage;
        ptrImage = ptrImageHSV;
    }
    else{
        throw ControllerException("No image loaded");
    }
}

void Controller::applyBinaryThreshold()throw (ControllerException){
     if(this->ptrImage != NULL){        
         ImageImPro* ptrImageBin = this->ptrLib->applyThreshold(this->ptrImage, 100, 255, OpenImProLib::BINARY_THRESH);
         delete this->ptrImage;
         ptrImage = ptrImageBin;
     }
     else{
         throw ControllerException("No image loaded");
     }
 }

 ImageImPro* Controller::getImage(){
    return this->ptrImage;
 }
 ImageImPro* Controller::getVideo(){
    return this->ptrCurrVideoImage;
 }
Controller::~Controller(){
    if(this->ptrImage != NULL)
        delete this->ptrImage;
    if(this->ptrLib != NULL)
        delete this->ptrLib;
}
