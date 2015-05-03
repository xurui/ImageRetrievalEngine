//
//  ImagePreProcess.cpp
//  ImageRetrievalEngine
//
//  Created by XuRui on 15-3-21.
//  Copyright (c) 2015Äê XuRui. All rights reserved.
//
#include "ImagePreProcess.h"

void ImagePreProcess::HSVimgQuantization(const cv::Mat& hsv_img, cv::Mat& quantized_img) {
    std::vector<cv::Mat> splited;
    cv::split(hsv_img.clone(), splited);
    cv::Mat img_H = splited[0];
    cv::Mat img_S = splited[1];
	cv::Mat img_V = splited[2];
	int quantized_H = 0;
	int quantized_S = 0;
	int quantized_V = 0;
	quantized_img.create(hsv_img.rows, hsv_img.cols, CV_8UC1);
	for (int i = 0; i < hsv_img.rows; ++i) {
		for (int j = 0; j < hsv_img.cols; ++j) {
			if (158 <= img_H.at<uchar>(i,j) || img_H.at<uchar>(i,j) <= 10) {
				quantized_H = 0;
			} else if (11 <= img_H.at<uchar>(i,j) && img_H.at<uchar>(i,j) <= 20) {
				quantized_H = 1;
			} else if (21 <= img_H.at<uchar>(i,j) && img_H.at<uchar>(i,j) <= 38) {
				quantized_H = 2;
			} else if (39 <= img_H.at<uchar>(i,j) && img_H.at<uchar>(i,j) <= 77) {
				quantized_H = 3;
			} else if (78 <= img_H.at<uchar>(i,j) && img_H.at<uchar>(i,j) <= 95) {
				quantized_H = 4;
			} else if (96 <= img_H.at<uchar>(i,j) && img_H.at<uchar>(i,j) <= 135) {
				quantized_H = 5;
			} else if (136 <= img_H.at<uchar>(i,j) && img_H.at<uchar>(i,j) <= 147) {
				quantized_H = 6;
			} else if (148 <= img_H.at<uchar>(i,j) && img_H.at<uchar>(i,j) <= 157) {
				quantized_H = 7;
			} if (0 <= img_S.at<uchar>(i,j) && img_S.at<uchar>(i,j) <= 51) {
				quantized_S = 0;
			} else if (52 <= img_S.at<uchar>(i,j) && img_S.at<uchar>(i,j) <= 178) {
				quantized_S = 1;
			} else if (179 <= img_S.at<uchar>(i,j) && img_S.at<uchar>(i,j) <= 255) {
				quantized_S = 2;
			} if (0 <= img_V.at<uchar>(i,j) && img_V.at<uchar>(i,j) <= 51) {
				quantized_V = 0;
			} else if (52 <= img_V.at<uchar>(i,j) && img_V.at<uchar>(i,j) <= 178) {
				quantized_V = 1;
			} else if (179 <= img_V.at<uchar>(i,j) && img_V.at<uchar>(i,j) <= 255) {
				quantized_V = 2;
			}
			quantized_img.at<uchar>(i,j) = 9 * quantized_H + 3 * quantized_S + quantized_V;
		}
	}
}

//resize image to 128*128
void ImagePreProcess::ImgResizeProcess(const cv::Mat& img, cv::Mat& resized_img) {
	float k = 1.0;
	if (img.rows < 128 && img.cols < 128) {
		k = ceil(float(128 / img.rows));
	} else if (img.rows > 128 && img.cols > 128) {
		k = 1 / ceil(float(img.rows / 128));
	}
	cv::resize(img, resized_img, cv::Size(int(k * img.rows), int(k * img.cols)));
}