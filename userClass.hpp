// This file contains the user class
// Contains all necessary includes for the GoSDK libraries
#ifndef userClass
#define userClass

#include <string>
#include <iostream>
#include <stdlib.h>
#include "matlabFunctions.hpp"
#define MAX_COEF_SIZE 100

using namespace std;
class User{
		public:
		string name;
		int numCoefs;
		float detCoefs [MAX_COEF_SIZE];
		//functions
		void initializefromfile(string filename);
		void initializeNewUser(string username, int sampleTime);
		User(void);
};

#endif
