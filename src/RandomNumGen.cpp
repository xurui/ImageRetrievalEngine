//
//  RandomNumGen.cpp
//  LSH_Color
//
//  Created by XuRui on 15-4-27.
//  Copyright (c) 2015年 XuRui. All rights reserved.
//

#include "RandomNumGen.h"

double RandomNumGen::genGaussRand(const double& mean, const double& var)
{
    static double V1, V2, S;
    static int phase = 0;
    double X;
    
    if ( phase == 0 ) {
        do {
            double U1 = (double)rand() / RAND_MAX;
            double U2 = (double)rand() / RAND_MAX;
            
            V1 = 2 * U1 - 1;
            V2 = 2 * U2 - 1;
            S = V1 * V1 + V2 * V2;
        } while(S >= 1 || S == 0);
        
        X = V1 * sqrt(-2 * log(S) / S);
    } else
        X = V2 * sqrt(-2 * log(S) / S);
    
    phase = 1 - phase;
    
    X = X * var + mean;
    
    return X;
}

//生成均匀分布随机数
double RandomNumGen::genUniformRand(const double& min, const double& max) {
    double random = (double)rand()/RAND_MAX;
    random = random * (max - min) + min;
    return random;
}
