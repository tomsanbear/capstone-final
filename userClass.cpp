// This file contains the implementation of the User class

#include "userClass.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>

// New User Declaration 
int User::initializeNewUser(std::string username, int sampleTime){
	this->name = username;
	// we now start the capture procedure
	int status = readEKG(sampleTime,ekgdata);
	if(status == 0){
		// Take the EKG vector and perform the filtering on it
		int numsamples = ekgdata.size();
		float ekg_float[numsamples];
		std::copy(ekgdata.begin(),ekgdata.end(),ekg_float);
		float snr = 0;
		myButterFilter(ekg_float,snr,numsamples);
		// Window the signal now
		this->windowEkg();
		return 1;
	}
	else
		std::cout << "Failed to initialize the new user." << std::endl;
	return 0;
}

void User::windowEkg(){
	// rows are individual windows
	int slideby = 4;
	int freq = 200;
	int windowsize = slideby*freq;
	int numwins = int(ekgdata.size()/windowsize);
	// initialize the memory
	this->windowdata.resize(numwins);
	for(int i = 0; i<=numwins-1;i++){
		for(int j = 0;j<=windowsize-1;j++){
			this->windowdata[i].push_back(this->ekgdata[j+i*windowsize]);
		}
	}
	return;
}

void User::computeCoefs(){
	std::cout << "Computing coefficients for user " << this->name << std::endl;
	// Internal function to compute wavelet coefs
	int M = 3; // Autocorrelation lags
	//initialize the coefs
	int numwins = this->windowdata.size();
	this->vectorCoefs.resize(M+1);
	for(int i = 0; i<M+1; i++)
		this->vectorCoefs[i].resize(this->windowdata.size()); // resize to number of windows
	// need mean values for each window
	float mean[numwins];
	int N = this->windowdata[0].size();
	for(int i = 0; i<numwins;i++){
		mean[i] = 0;
		for(int j = 0; j<windowdata[0].size();j++){
			mean[i] = mean[i]+windowdata[i][j];
		}
		mean[i] = mean[i]/windowdata[0].size();
	}
	//compute autocorrelation of the current signal
	float num = 0;
	float den = 0;
	for(int i = 0; i < M+1; i++){ // iterate through lags
		// now we calculate the autocorrelation, rows are windows, cols are lags
		for(int j = 0; j<numwins ; j++){
			//need another loop for numerator
			for(int k = 0; k<N-i; k++){
				num = num + (windowdata[j][k]-mean[i])*(windowdata[j][k+i]);
			}
			for(int k = 0; k<N-i; k++){
				den = den + (windowdata[j][k]-mean[i])*(windowdata[j][k]-mean[i]);
			}
			vectorCoefs[i][j]= num/den;
			num = 0;
			den = 0;
		}
	}
}

// returns 1 if successful, 0 if file doesent exist
int User::initializefromfile(int identifier){
	//
	std::ostringstream sstream;
	sstream << "user" << identifier;
	std::string filename = sstream.str();
	// we now start importing from file
	std::ifstream myfile(filename.c_str());
	std::string line;
	std::getline(myfile,line);
	int rows = atoi(line.c_str());
	std::getline(myfile,line);
	int cols = atoi(line.c_str());
	if(myfile.is_open()){
		for(int i = 0; i < rows; i++){
			for(int j = 0; j<cols;j++){
				std::getline(myfile,line);
				vectorCoefs[i][j] = atof(line.c_str());
			}
		}
	}
	else
		return 0;
	return 1;
}

void User::flushUserToFile(){
	// we first output the dimensions of the vectorcoefs for future read ins
	std::ostringstream sstream;
	sstream << "user" << identifier;
	std::string filename = sstream.str();
	std::ofstream myfile;
	myfile.open(filename.c_str());
	myfile << this->vectorCoefs.size() << std::endl;
	myfile << this->vectorCoefs[0].size() << std::endl;
	// now we output vector coefs
	for(int i = 0; i < this->vectorCoefs.size(); i++)
		for(int j=0; j < this->vectorCoefs[0].size();j++)
			myfile << this->vectorCoefs[i][j] << std::endl;
	myfile.close();
	return;
}

//Define the default constructor class
User::User(){
	std::cout << "Empty User created" << std::endl;
}
