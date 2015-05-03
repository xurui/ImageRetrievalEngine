//
//  LocalitySensitiveHashing.h
//  LSH_Color
//
//  Created by XuRui on 15-4-22.
//  Modified by XuRui on 15-4-28.
//  Copyright (c) 2015年 XuRui. All rights reserved.
//

#ifndef __LSH_Color__LocalitySensitiveHashing__
#define __LSH_Color__LocalitySensitiveHashing__

#include <opencv2/opencv.hpp>
#include "RandomNumGen.h"
#include <fstream>
#include <stdlib.h>
#include <iostream>

struct LSHFunction {
    std::vector<double> a;
    double b;
};

class LocalitySensitiveHashing {
public:
    LocalitySensitiveHashing();
    LocalitySensitiveHashing(int L, int K, double w, int D) : L(L), K(K), w(w), D(D) {};
    void initialLSHFunction(const std::string& LSH_file);
    void computeLSH(const std::vector<double>& feature, const int& l, const double& w,
                    const std::vector<std::vector<LSHFunction> >& g_lshfunctions,
                    std::vector<int>& lsh_vec);
    void readLSHFunctions(const std::string& LSH_file,
                          std::vector<std::vector<LSHFunction> >& g_lshfunctions);
private:
    int L;
    int K;
    int D;
    double w;
};

#endif /* defined(__LSH_Color__LocalitySensitiveHashing__) */
