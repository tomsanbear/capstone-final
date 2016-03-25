// This file contains the implementation of the User class

#include "userClass.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

// New User Declaration 
void User::initializeNewUser(string username, int sampleTime){
	name = username;
	// we now start the capture procedure
	readEKG(sampleTime,vectorCoefs);
	// Take the EKG vector and perform the filtering on it
	int numsamples = vectorCoefs.size();
	float* vectorCoefs_float = &vectorCoefs[0];
	float *snr;
	myButterFilter(vectorCoefs_float,snr,numsamples);
	return;
}

//Define the default constructor class
User::User(void){
	cout << "Empty User created" << endl;
}
