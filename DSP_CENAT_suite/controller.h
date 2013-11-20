#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "includes.h"
#include "openimprolib_opencvimpl.h"
#include "imageimpro_opencvimpl.h"
#include "unittests.h"
#include "hogdetectorcpu.h"
#include "videoimpro_opencvimpl.h"
#include "backgroundsegmentator.h"
#include "backgroundsegmentatoragmm.h"
#define DEF_IMAGE "lena.png"
#define DEF_VIDEO "../input/videos/video.mp4"
/*
*Controller image
*/
class Controller{

private:   
    /*Library to use*/
    OpenImProLib* ptrLib; 
    /*Pointer to the image to modify*/
    ImageImPro* ptrImage;
    /*Pointer to the current video image*/
    ImageImPro* ptrCurrVideoImage;
    /*Pointer to the video to process*/
    VideoImPro* ptrVideo;
    /*Pointer to the hogVideo */
    HOGDetectorCPU* ptrHogVideo;
    /*Pointer to the Segmentation algorithm class*/
    BackgroundSegmentator* ptrSegVideo;


public:   
    /*Exception class*/
    class ControllerException: public exception{
      public:
      /*Exception message*/
      const char* ptrMessage;
      /*Exception constructor*/
      ControllerException(){}
      /*
      *Exception constructor
      *@param errorMesage, error message string
      */
      ControllerException(const char* ptrErrorMessage):ptrMessage(ptrErrorMessage){
        this->ptrMessage = ptrMessage;
      }
      /*
      *Throw method
      *@returns message
      */
      virtual const char* what() const throw(){
        return this->ptrMessage;
      }
    }controllerException;
    /*Controller constructor*/
    Controller();
    /*
    *Returns the modified image of the controller
    *@return modified image
    */
    ImageImPro* getImage();
    /*
    *Returns the modified image of the video
    *@return modified image
    */
    ImageImPro* getVideo();
    /*
    *Plays the loaded video
    *@param ptrName, image path
    */
    void playVideo();
    /*
    *Plays the video hog-processed
    *@param ptrName, image path
    */
    void playVideoHog(QString fileName);//throw (ControllerException);
    /*
    *Loads the video in the given path of the Controller's video
    *@param ptrName, image path
    */
    void loadVideo(char* ptrPath);//throw (ControllerException);
    /*
    *Loads the image in the given path to the Controller's image
    *@param ptrName, image path
    */
    void loadImage(char* ptrPath)throw (ControllerException);
    /*
    *Applies the canny filter to the controller's image
    */
    void applyFilterCanny()throw (ControllerException);
    /*
    *Applies the binary threshold to the controller's image
    */
    void applyBinaryThreshold()throw (ControllerException);
    /*
    *Applies the Sobel operator to the controller's image
    */
    void applyFilterSobel()throw (ControllerException);
    /*
    *Applies the Gauss operator to the controller's image
    */
    void applyFilterGauss()throw (ControllerException);
    /*
    *Applies the Bilateral operator to the controller's image
    */
    void applyBilateral()throw (ControllerException);
    /*
    *Converts the image to the HSV color model representation
    */
    void convertToHSV()throw (ControllerException);
    /*
    *Prints the segmented video
    */
    void playVideoSegmented();
    /*Controller destructor*/
    ~Controller();
};

#endif
