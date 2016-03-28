// This file contains the implementation of the User class

#include "userClass.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>

// New User Declaration 
void User::initializeNewUser(std::string username, int sampleTime){
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
		// We now find detailed coefs.
		this->computeCoefs();
	}
	else
		std::cout << "Failed to initialize the new user." << std::endl;
	return;
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
	return 1;
}

void User::flushUserToFile(){
	// Convert the user data to specified import/export format
	return;
}

//Define the default constructor class
User::User(int input){
	std::cout << "Empty User created" << std::endl;
	this->identifier = input;
}
