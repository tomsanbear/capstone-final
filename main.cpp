// The following program is the main comilation of the final implementation of the 
// Biometric fusion method.
//
// This consists of 3 main components, EKG processing, fingerprint processing, and 
// score fusion. They work together to form a rigorous biometric security solution.
//
// The data is stored in text file, and read on initialization of the program. As 
// this is just a proof of concept device, we provide no proper security handling 
// of user data, or authentication when it comes to user credential management. 
//
// With this program you can:
// -delete a user
// -add a user
// -identify a user
// -authenticate a user
//
// Only the detailed coefs. are stored for each user, not actual biometric data

// Ordering of headers is important here.
#include <unistd.h>
#include <math.h>
#include <fstream>
#include "userClass.hpp"
#include "matlabFunctions.hpp"

//////////////////////////////////////////////////////////////////////////////////////////
//			Scoring algorithm						//
//////////////////////////////////////////////////////////////////////////////////////////

// returns 0 for accepted, 1 for rejected
int scoringFunction(float fp_weight, float ekg_weight, float fp_score, float ekg_score){
	float fp_limit = 0.9;
	float ekg_limit = 0.95;
	float fusion_limit = 0.8; // These values will be modified later on ~ SNR
	if(fp_score < fp_limit){
		// Fingerprint is not satisfactory, so we move on to the ekg
		std::cout << "Fingerprint not coherent, matching EKG" << std::endl;
		if(ekg_score < ekg_limit)
			return 1;
		else{
			// fusion HA
			float fusionScore = (fp_weight*fp_score)+(ekg_weight*ekg_score);
			if (fusionScore<fusion_limit)
				return 1;
			else
				return 0;
		}
	}
	else
		return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
//                         MAIN FUNCTION BELOW HERE					//
//////////////////////////////////////////////////////////////////////////////////////////

int main(){
	// Load data from all files detected
	// Currently user needs to manually tell the program how many existing users there are
	// TODO
	std::vector<User> masterList;
	int numUsers,temp;
	float tempDist;
	float bestDist = 10000;
	std::cout << "Importing any available users to the system." << std::endl;
	// Read in any available users.

	// Start of program, let user make choice on function to perform
	int userChoice;
	User currentUser; // This will be the user currently accessing the system
	while(true){
		std::cout << "Please choose an option" << std::endl;
		std::cin >> userChoice;
		if(userChoice == 1){
			// Identify/Authenticate the user
			currentUser.initializeNewUser("temp", 4);
			temp = 0;
			for(int i=0;i<numUsers;i++){
				// Iterate through the coefficient lists, and keep the lowest distance, then calculate the probability
				tempDist= distCompare(currentUser,masterList);
				if (tempDist<bestDist){
					temp = i; // set the current best user
				}
				//Fusion code goes in here
				std::cout << "You are user: " << masterList[temp].name << std::endl;
			}
		}
		else if(userChoice == 2){
			// Enrol User in the system
			// Create new User class
			std::string tempName;
			std::cout << "Please enter your name: ";
			std::cin >> tempName;
			numUsers += 1;
			masterList[numUsers].initializeNewUser(tempName,20);
			// Now we test to see if the user is recognized in the system
			
		}
		else if(userChoice == 4){
			std::cout << "Exiting program" << std::endl;
			break;
		}
		else
			std::cout << "Invalid choice" << std::endl;
	}

	// Exit program
	return 0;
}
