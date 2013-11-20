#ifndef BACKGROUNDSEGMETATOR_H
#define BACKGROUNDSEGMETATOR_H
#include "includes.h"
#include "imageimpro_opencvimpl.h"

class BackgroundSegmentator
{
public:
    BackgroundSegmentator();

    virtual list<ImageImPro*> substractForegroundMasks(ImageImPro* ptrInput, double alpha, int delta) = 0;
    virtual ImageImPro* getBackgroundImage() = 0;
};

#endif // BACKGROUNDSEGMETADOR_H
