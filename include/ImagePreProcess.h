//
//  ImagePreProcess.h
//  ImageRetrievalEngine
//
//  Created by XuRui on 15-3-21.
//  Copyright (c) 2015Äê XuRui. All rights reserved.
//

#ifndef __ImageRetrievalEngine__ImagePreProcess__
#define __ImageRetrievalEngine__ImagePreProcess__

#include <math.h>
#include <opencv2/opencv.hpp>


class ImagePreProcess {
public:
	void HSVimgQuantization(const cv::Mat& hsv_img, cv::Mat& quantized_img);
	void ImgResizeProcess(const cv::Mat& img, cv::Mat& resized_img);
};
#endif /* defined(__ImageRetrievalEngine__ImagePreProcess__) */