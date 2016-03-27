// This file contains the implementation of the User class

#include "userClass.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>

// New User Declaration 
void User::initializeNewUser(std::string username, int sampleTime){
	name = username;
	// we now start the capture procedure
	int status = readEKG(sampleTime,ekgdata);
	if(status == 0){
		// Take the EKG vector and perform the filtering on it
		int numsamples = ekgdata.size();
		float *ekg_float = &ekgdata[0];
		float *snr = 0;
		myButterFilter(ekg_float,snr,numsamples); //TODO convert function to use vector
		// Window the signal now
		// We now find detailed coefs.
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
	// Predetermine sizes for this
	for(int i = 0; i<=ekgdata.size()-1;i=i+(slideby*freq)){ // TODO this is most likely wrong
		// check to see if we are outside array bounds, if so windowing is done

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
User::User(void){
	std::cout << "Empty User created" << std::endl;
}
