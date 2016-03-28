// 
// This file contains the user class
//
 
#ifndef userClass
#define userClass

#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include "myFilter.hpp"
#include "ekgRead.hpp"

class User{
		public:
		std::string name;
		int identifier;		// file name to save under for system startup
		std::vector<float> ekgdata; // not secure, therefore might bundle together into constructor
		std::vector< std::vector<float> > windowdata; // utility structure
		std::vector< std::vector<float> > vectorCoefs; // essentially a 2d matrix holding the coefs
		std::vector< std::vector<float> > weightedCoefs; // another place holder...inefficient meh
		std::vector<float> ac; //will be removed later, but here for testing
		std::vector< std::vector<double> > weights; // for conveninence weights are stored here, same for all users
		//functions
		int initializefromfile(int identifier);
		void initializeNewUser(std::string username, int sampleTime);
		void windowEkg(void);
		void flushUserToFile(void);
		void computeCoefs(void);
		User();
};

#endif
