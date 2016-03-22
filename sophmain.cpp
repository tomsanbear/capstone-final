//
//  main.cpp
//  butterFilter
//
//  Created by Captain Phie on 3/10/16.
//  Copyright © 2016 Captain Phie. All rights reserved.
//

#include "myFilter.hpp"


int main(int argc, const char * argv[]) {

    //variable initialization
    float* ekgData;
    std::vector<float> vectordata;
    float snr;
    
    //output output file
    FILE* myFile = fopen("/Users/phie/Documents/CAPSTONE/C++/butterFilter/myfile.txt","w");
    
    //parse input
    int numSamples = textParser("/Users/phie/Documents/CAPSTONE/C++/butterFilter/ekgdata.txt", vectordata);
    
    //create data array
    ekgData = new float[numSamples];
    
    //copy data from vector into float array
    std::copy(&vectordata[0], &vectordata[numSamples-1], ekgData);
    
    //call filter function
    myButterFilter(ekgData, &snr, numSamples);
    
    
    //print ekg data to file
    for (int i = 0; i<numSamples; i++){
        fprintf(myFile, "%f\n", ekgData[i]);
    }
    
    //print snr to terminal
    printf("%f\n", snr);
    return 0;
}
