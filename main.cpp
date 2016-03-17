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

using namespace std;

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
		cout << "Fingerprint not coherent, matching EKG" << endl;
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
//			Function to compare two different users				//
//////////////////////////////////////////////////////////////////////////////////////////

// Implements euclidean distance between two users returns the distance
float distCompare(User first, User second){
       // we first need to find the min number of coefs that we can compare and
       // downsample if necessary
       unsigned long  maxDim = first.vectorCoefs.size();
       if (maxDim < second.vectorCoefs.size())
	       maxDim = second.vectorCoefs.size();

       // We now calculate the distance
       float distanceOut = 0;
       float tempDif;
       for(unsigned long i = 0;i<maxDim;i++){
	       tempDif = first.vectorCoefs[i]-second.vectorCoefs[i];
	       distanceOut = distanceOut + pow(tempDif,2);
       }
       distanceOut = sqrt(distanceOut);
       // Return the calculated distance
       return distanceOut;
}

//////////////////////////////////////////////////////////////////////////////////////////
//                         MAIN FUNCTION BELOW HERE					//
//////////////////////////////////////////////////////////////////////////////////////////

int main(){
	// Load data from all files detected
	// Currently user needs to manually tell the program how many existing users there are
	// TODO
	vector<User> masterList;
	int numUsers,temp;
	float tempDist;
	float bestDist = 10000;
	cin >> numUsers;
	for (int i=0;i<numUsers;i++){
		cout << "Adding user " << i << " to the program" << endl;
	}

	// Start of program, let user make choice on function to perform
	int userChoice;
	User currentUser; // This will be the user currently accessing the system
	while(true){
		cin >> userChoice;
		if(userChoice == 1){
			// Identify/Authenticate the user
			currentUser.initializeNewUser("temp", 4);
			temp =0;
			for(int i=0;i<numUsers;i++){
				// Iterate through the coefficient lists, and keep the lowest distance, then calculate the probability
				tempDist= distCompare(currentUser,masterList[i]);
				if (tempDist<bestDist){
					temp = i; // set the current best user
				}
				//Fusion code goes in here
				cout << "You are user: " << masterList[temp].name << endl;
			}
		}
		else if(userChoice == 2){
			// Enrol User in the system
			// Create new User class
			string tempName;
			cout << "Please enter your name: ";
			cin >> tempName;
			numUsers += 1;
			masterList[numUsers].initializeNewUser(tempName,20);
			// Now we test to see if the user is recognized in the system
			
		}
		else if(userChoice == 3){
			// Delete User
			numUsers = numUsers -1;
			string tempName;
			cout << "Please enter the name of the user to delete." << endl;
			cin >> tempName;
		}
		else if(userChoice == 4){
			cout << "Exiting program" << endl;
			break;
		}
		else
			cout << "Invallid choice" << endl;
	}

	// Exit program
	return 0;
}
