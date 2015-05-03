//
//  LocalitySensitiveHashing.cpp
//  LSH_Color
//
//  Created by XuRui on 15-4-22.
//  Modified by XuRui on 15-4-28.
//  Copyright (c) 2015年 XuRui. All rights reserved.
//

#include "LocalitySensitiveHashing.h"

using namespace std;
using namespace cv;

void LocalitySensitiveHashing::initialLSHFunction(const string& LSH_file) {
    RandomNumGen generate_random;
    vector<vector<LSHFunction> > g_lshfunctions;
    FileStorage fs(LSH_file, FileStorage::WRITE);
    LSHFunction single_lsh;
    single_lsh.a.assign(D, 0);
    vector<LSHFunction> lsh_vec(K, single_lsh);
    g_lshfunctions.assign(L, lsh_vec);
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < K; ++j) {
            for (int d = 0; d < D; ++d) {
                g_lshfunctions[i][j].a[d] = generate_random.genGaussRand(0.0, 1.0);
            }
            g_lshfunctions[i][j].b = generate_random.genUniformRand(0.0, w);
        }
    }
    for (int l = 0; l < L; ++l) {
        std::stringstream l_temp;
        std::string l_num;
        l_temp << l;
        l_temp >> l_num;
        fs << "g" + l_num << "[";
        for (int k = 0; k < K; ++k) {
            std::stringstream k_temp;
            std::string k_num;
            k_temp << k;
            k_temp >> k_num;
            fs << "{" << "k" + k_num + "_a" << "[";
            for (int d = 0; d < D; ++d) {
                fs << g_lshfunctions[l][k].a[d];
            }
            fs << "]" << "}";
            fs << "{" << "k" + k_num + "_b";
            fs << g_lshfunctions[l][k].b << "}";
        }
        fs << "]";
    }
    fs.release();
}

void LocalitySensitiveHashing::computeLSH(const vector<double>& feature, const int& l, const double& w,
                            const vector<vector<LSHFunction> >& g_lshfunctions, vector<int>& lsh_vec) {
    for (int i = 0; i < g_lshfunctions[l].size(); ++i) {
        double value = 0.0;
        for (int j = 0; j < feature.size(); ++j) {
            value += g_lshfunctions[l][i].a[j] * feature[j];
        }
        lsh_vec[i] = floor((value + g_lshfunctions[l][i].b) / w);
    }
}

void LocalitySensitiveHashing::readLSHFunctions(const string& LSH_file, vector<vector<LSHFunction> >& g_lshfunctions) {
    FileStorage fs(LSH_file, FileStorage::READ);
    FileNode f_root = fs.root();
    int l = 0;
    for (FileNodeIterator it = f_root.begin(); it != f_root.end(); ++it, ++l) {
        string root_name = (*it).name();
        FileNode lsh_k = fs[root_name];
        int k = 0;
        for (FileNodeIterator it = lsh_k.begin(); it != lsh_k.end(); ++it, ++k) {
            if (k % 2 != 1) {
                std::stringstream k_temp;
                std::string k_num;
                k_temp << k/2;
                k_temp >> k_num;
                string a_vec_name = "k" + k_num + "_a";
                (*it)[a_vec_name] >> g_lshfunctions[l][k/2].a;
            } else {
                std::stringstream k_temp;
                std::string k_num;
                k_temp << k/2;
                k_temp >> k_num;
                string b_name = "k" + k_num + "_b";
                (*it)[b_name] >> g_lshfunctions[l][k/2].b;
            }
        }
    }
}
