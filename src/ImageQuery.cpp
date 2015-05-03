//
//  ImageQuery.cpp
//  ImageRetrievalEngine
//
//  Created by XuRui on 15-3-22.
//  Copyright (c) 2015Äê XuRui. All rights reserved.
//

#include "ImageQuery.h"
#include "ImageDescriptor.h"
#include "ImagePreProcess.h"

void ImageQuery::QueryImage(const std::string& LSH_file, const cv::Mat& img, const std::string& index_file) {
	ImagePreProcess img_preprocess;
	ColorAutoCorrelogram img_match;
	const int L = 25;
	const int K = 5;
	const double w = 4;
    const int D = 360;
    LocalitySensitiveHashing LSH(L, K, w, D);
    LSHFunction single_lsh;
    single_lsh.a.assign(360, 0);
    std::vector<LSHFunction> lsh_vec(K, single_lsh);
    std::vector<std::vector<LSHFunction> > g_lshfunctions;
    g_lshfunctions.assign(L, lsh_vec);
    LSH.readLSHFunctions(LSH_file, g_lshfunctions);
    std::vector<double> correlogram_target(360, 0.0);
	img_preprocess.ImgResizeProcess(img, resized_query_img);
	cvtColor(resized_query_img, hsv_query_img, CV_BGR2HSV);
	img_preprocess.HSVimgQuantization(hsv_query_img, qua_query_img);
	img_match.CreateColorAutoCorrelogram(qua_query_img, correlogram_target);
	cv::FileStorage fs(index_file, cv::FileStorage::READ);
    cv::FileStorage feature("color_feature.yml", cv::FileStorage::READ);
	cv::FileNode f_root = fs.root();
    for (cv::FileNodeIterator it = f_root.begin(); it != f_root.end(); ++it) {
        std::string root_name = (*it).name();
        cv::FileNode lsh = fs[root_name];
		int l = 0;
        for (cv::FileNodeIterator it = lsh.begin(); it != lsh.end(); ++it, ++l) {
			std::vector<int> quary_lsh_vec(K, 0);
			LSH.computeLSH(correlogram_target, l, w, g_lshfunctions, quary_lsh_vec);
            double cos_dis = 0.0;
            std::stringstream l_temp;
            std::string l_num;
            l_temp << l;
            l_temp >> l_num;
            std::string vec_name = "g" + l_num;
            std::vector<int> candidate_vec;
            (*it)[vec_name] >> candidate_vec;
            cos_dis = CalcuCosineDistance(quary_lsh_vec, candidate_vec);
            if (cos_dis >= 0.99) {
                std::string res_name;
                std::string cadidate_name;
                root_name.erase(0, 3);
                cadidate_name = "jpg" + root_name;
                std::vector<double> correlogram_candidates;
                correlogram_candidates.clear();
                feature[cadidate_name] >> correlogram_candidates;
                match_res = img_match.CorrelogramMatching(correlogram_target, correlogram_candidates);
                res_name = "jpg1/" + root_name + ".jpg";
                index_map.push_back(std::make_pair(match_res, res_name));
                std::cout << root_name << std::endl;
				break;
            }
        }
    }
    sort(index_map.begin(), index_map.end());
    for (int i = 0; i < query_num; ++i) {
        cv::Mat res_img = cv::imread(index_map[i].second);
        imwrite("res/" + index_map[i].second, res_img);
    }
}

double ImageQuery::CalcuCosineDistance(const std::vector<int>& quary_vec, const std::vector<int>& candidate_vec) {
	double cosdis_res = 0.0;
	double dot_product = 0.0;
	double quary_square = 0.0;
	double candidate_square = 0.0;
	for (int i = 0; i != quary_vec.size(); ++i) {
		dot_product += quary_vec[i] * candidate_vec[i];
		quary_square += quary_vec[i] * quary_vec[i];
		candidate_square += candidate_vec[i] * candidate_vec[i];
	}
	cosdis_res = dot_product / (sqrt(quary_square) * sqrt(candidate_square));
	return cosdis_res;
}