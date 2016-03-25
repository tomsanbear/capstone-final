//
//  myFilter.cpp
//  
//
//  Created by Captain Phie on 3/20/16.
//
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "myFilter.hpp"

//filter function. See DSP filters readme for usage
float* filter(const int numSamples, float* ekgData,const int sampleRate,const int order,const int centerF,const int bandWidth){
    
    Dsp::Filter* f = new Dsp::FilterDesign
    <Dsp::Butterworth::Design::BandPass <4>, 1> ;
    Dsp::Params params;
    params[0] = sampleRate; // sample rate
    params[1] = order; // order
    params[2] = centerF; // center frequency
    params[3] = bandWidth; // band width
    f->setParams (params);
    f->process (numSamples, &ekgData);
    return ekgData;
}

//parse text, modifies a vector value, returns size of, takes path as input
int textParser(std::string textInput, std::vector<float> &output){
    const char* temp = textInput.c_str();
	std::ifstream input(temp,std::ios::in); //create ifstream
    if (!input.is_open()){
        printf("cannot read file, exiting\n");
        exit(EXIT_FAILURE);
    }
    float number;//float to store numbers
    int num = 0;//counter for number of data points
    while (input >> number ){
        output.push_back(number);
        num++;
    }
    return num;
}

//return the mean of a float array
float getMean(const float* input,const int numSamples){
    float sum = 0;
    for (int i = 0; i<numSamples; i++) {
        sum += input[i];
    }
    float mean = sum/numSamples;
    return mean;
}

//function to get snr, noise is measures as original signal - filtered signal
void getSNR(const float* filtSig,const float origSig[],const int numSamples, float* snr){
    float noisePower;
    float noise[numSamples];
    float sigPower;
    for (int i =0; i<numSamples; i++){
        noise[i] = origSig[i] - filtSig[i];
        noisePower+=std::abs(noise[i]*noise[i])/numSamples;
        sigPower+=std::abs(filtSig[i]*filtSig[i])/numSamples;
    }
    printf("%f\n%f\n", sigPower, noisePower);
    *snr = sigPower/noisePower;
    printf("%f\n", *snr);
    return;
}


//main entry function, modifies ekgData array and snr
void myButterFilter(float* ekgData, float* snr,const int numSamples){
    float origSig[numSamples];
    
    // set filter parameters
    int sampleRate = 200;
    int order = 4;
    double centerF = 19.75;
    double bandWidth = 19.25;
    
    
    float mean = getMean(ekgData, numSamples);
    
    for (int i = 0; i<numSamples; i++) {
        ekgData[i] = ekgData[i] - mean;
        origSig[i] = ekgData[i];
    }
    
    ekgData = filter(numSamples, ekgData, sampleRate, order, centerF, bandWidth);
    getSNR(ekgData, origSig, numSamples, snr);
    return;
}

