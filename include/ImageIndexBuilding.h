//
//  ImageIndexBuilding.h
//  ImageRetrievalEngine
//
//  Created by XuRui on 15-3-22.
//  Copyright (c) 2015Äê XuRui. All rights reserved.
//


#ifndef __ImageRetrievalEngine__ImageIndexBuilding__
#define __ImageRetrievalEngine__ImageIndexBuilding__

#include <opencv2/opencv.hpp>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include "LocalitySensitiveHashing.h"


class ImageIndexBuilding {
public:
	void BuildingIndex(const std::string& LSH_file, const std::string& img_path,
                       const std::string& index_file);
private:
	std::vector<std::string> image_dataset;
	cv::Mat candidate_img;
	cv::Mat resized_img;
	cv::Mat hsv_img;
	cv::Mat qua_img;
};
#endif /* defined(__ImageRetrievalEngine__ImageIndexBuilding__) */