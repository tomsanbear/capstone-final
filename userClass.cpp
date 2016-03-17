// This file contains the implementation of the User class

#include "userClass.hpp"

//Define the default constructor class
User::User(void){
	cout << "Empty User created" << endl;
}

// Define the New user
void User::initializeNewUser(string username, int sampleTime){
	// Creating a new user, we need to measure the EKG for 30 seconds
	// then we perform the necessary operations to calculate the detailed 
	// wavelet coefficients.
	cout << "Creating new user" << endl;
	// We begin to fill in data we know of
	name = username;
}

void User::initializefromfile(string filename){
	// Input the database txt file so that it is parsed in as new users.
	cout << "Importing existing users from database" << endl;
	// Sophs code goes here TODO
	name = filename;
}

