//
//  RandomNumGen.h
//  ImageRetrievalEngine v2.0
//
//  Created by XuRui on 15-4-22.
//  Copyright (c) 2015Äê XuRui. All rights reserved.
//


#ifndef __ImageRetrievalEngine__RandomNumGen__
#define __ImageRetrievalEngine__RandomNumGen__
#include <stdlib.h>
#include <math.h>

class RandomNumGen {
public:
	double genGaussRand(const double& mean, const double& var);
	double genUniformRand(const double& min, const double& max);
};

#endif /* defined(__ImageRetrievalEngine__RandomNumGen__) */