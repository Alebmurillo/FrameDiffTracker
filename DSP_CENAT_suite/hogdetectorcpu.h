#ifndef HOGDETECTORGPU_H
#define HOGDETECTORGPU_H
#include "imageimpro_opencvimpl.h"
#define PIX_BLOCK_X 32
#define PIX_BLOCK_Y 32
#define PIX_CELL_X 8
#define PIX_CELL_Y 8
class HOGDetectorCPU{

public:
    HOGDetectorCPU();   
    ImageImPro* processImage(ImageImPro* ptrImage);
    void processVideo(char* ptrNameInput, char* ptrNameOutput);
    Mat* detectPeople(Mat* ptrImage);
};

#endif
