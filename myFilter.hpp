//
//  myFilter.hpp
//  butterFilter
//
//  Created by Captain Phie on 3/10/16.
//  Copyright © 2016 Captain Phie. All rights reserved.
//

#ifndef myFilter_hpp
#define myFilter_hpp

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "DspFilters/Dsp.h"
#include "DspFilters/Butterworth.cpp"
#include "DspFilters/Biquad.cpp"
#include "DspFilters/Cascade.cpp"
#include "DspFilters/Filter.cpp"
#include "DspFilters/PoleFilter.cpp"
#include "DspFilters/State.cpp"
#include "DspFilters/Param.cpp"


//filter function. See DSP filters readme for usage
float* filter(const int numSamples, float* ekgData,const int sampleRate,const int order,const int centerF,const int bandWidth)

//parse text, modifies a vector value, returns size of, takes path as input
int textParser(std::string textInput, std::vector<float> &output)

//return the mean of a float array
float getMean(const float* input,const int numSamples)

//function to get snr, noise is measures as original signal - filtered signal
void getSNR(const float* filtSig,const float origSig[],const int numSamples, float* snr)


//main entry function, modifies ekgData array and snr
void myButterFilter(float* ekgData, float* snr,const int numSamples)




#endif /* myFilter_hpp */
