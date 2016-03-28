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
	// Internal function to compute wavelet coefs
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
