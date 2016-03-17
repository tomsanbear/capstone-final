// 
// This file contains the user class
// Contains all necessary includes for the GoSDK libraries
// We store all the coefficients using the vector structure as it can handle dynamically 
// allocating any future coefficients
//
// File initilization:
// takes in the filename to read stored coefficients and sets up like that
//
// New User:
// Starts the EKG reading process, and processes into the detailed coefs.
//
// Constructor: 
// Empty as the two other functions deal with this.
//
 
#ifndef userClass
#define userClass

#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#define MAX_COEF_SIZE 100

using namespace std;
class User{
		public:
		string name;
		vector<float> vectorCoefs;
		//functions
		void initializefromfile(string filename);
		void initializeNewUser(string username, int sampleTime);
		User(void);
};

#endif
