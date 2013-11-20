#ifndef BACKGROUNDSEGMENTATORAGMM_H
#define BACKGROUNDSEGMENTATORAGMM_H
#include "backgroundsegmentator.h"

class BackgroundSegmentatorAGMM : public BackgroundSegmentator{
private:
    cv::BackgroundSubtractorMOG2* ptrBGM2;
    list<cv::Rect> getContoursRectangles(std::vector<std::vector<cv::Point> > contours, int delta, int threshold, cv::Mat::MSize size);
    list<cv::Rect> getTrackingCandidates(std::vector<std::vector<cv::Point> > contours, int delta, int threshold, cv::Mat::MSize size);
public:
    BackgroundSegmentatorAGMM();
    BackgroundSegmentatorAGMM(int history, float varThreshold, bool bShadowDetection=true);
    list<ImageImPro*> substractForegroundMasks(ImageImPro* ptrInput, double alpha, int delta);

    ImageImPro* getBackgroundImage();

};

#endif // BACKGROUNDSEGMENTATORAGMM_H
