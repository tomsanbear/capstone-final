// The following program is the main compilation of the final implementation of the
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
//			Scoring algorithm															//
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
	std::vector<User> masterList;
	int numUsers = 0;
	float tempDist;
	float bestDist = 10000;
	int status;
	std::cout << "Importing any available users to the system." << std::endl;
	// Read in any available users.
	for(int i = 0; i <= numUsers; i++){
		masterList.resize(numUsers+1);
		if(masterList[i].initializefromfile(i) == 1)
			numUsers += 1;
	}
	// Start of program, let user make choice on function to perform
	int userChoice;
	User *currentUser; // This will be the user currently accessing the system
	float *distList;
	float distsum;
	int tempint;
	std::vector< std::vector<double> > temp;
	while(true){
		std::cout << "Please choose an option:" << std::endl;
		std::cout << "1: Identify: must have registered users, and run LDA first." << std::endl;
		std::cout << "2: New user registration." << std::endl;
		std::cout << "3: Perform LDA weight analysis." << std::endl;
		std::cout << "4: Save database." << std::endl;
		std::cout << "5: Exit." << std::endl;
		std::cout << "Please choose an option" << std::endl;
		std::cin >> userChoice;
		std::cin.ignore(1);
		if(userChoice == 1){
			currentUser = new User();
			distList = new float[masterList.size()];
			std::cout << "Determining identity" << std::endl;
			// Identify/Authenticate the user
			currentUser->initializeNewUser("temp", 5); // We will upsample this user, to test against pregenerated weights
			// Upsample our signal, since we only have ~800 measurements = 1 window
			currentUser->windowdata.resize(masterList[0].windowdata.size());
			for(int i = 1; i < masterList[0].windowdata.size();i++){
				currentUser->windowdata[i]=currentUser->windowdata[0];
			}
			// compute the coefficients
			currentUser->computeCoefs();
			// setup for weights
			int nCommon = masterList[0].vectorCoefs[0].size();
			int n1 = masterList[0].vectorCoefs.size(); // rows of coefs
			int n2 = masterList[0].weights[0].size();	// cols of weights
			// create temp
			temp.resize(nCommon);
			for(int i = 0; i < nCommon ; i++){
				for(int j=0 ; j < n1; j++){
					temp[i].push_back(masterList[0].weights[j][i]);
				}
			}
			std::cout << "test user coefficients: " << std::endl;
			// Apply weights to the upsampled signal
			currentUser->weightedCoefs.resize(nCommon);
			for (int i = 0; i < n1; i++) {
				currentUser->weightedCoefs[i].resize(n1);
				for (int j = 0; j < n2; j++) {
					for (int k = 0; k < nCommon ; k++) {
						currentUser->weightedCoefs[i][j] += currentUser->vectorCoefs[i][k] * temp[k][j];
					}
					std::cout << currentUser->weightedCoefs[i][j] << " ";
				}
				std::cout << std::endl;
			}
			// Find the distances
			tempint = 0;
			distsum = 0;
			distCompare(currentUser,masterList,distList);
			for(int i=0;i<numUsers;i++){
				distsum += distList[i];
				if(distList[i]<distList[tempint])
					tempint = i;
			}
			distsum = distsum/numUsers;
			// clean up after the user is done
			delete distList;
			delete currentUser;
		}
		else if(userChoice == 2){
			std::cout << "Registering a new user." << std::endl;
			// Enrol User in the system
			// Create new User class
			std::string tempName;
			std::cout << "Please enter your name: " << std::endl;
			std::cin >> tempName;
			masterList.resize(numUsers+1);
			status = masterList[numUsers].initializeNewUser(tempName,22);
			masterList[numUsers].identifier = numUsers;
			masterList[numUsers].computeCoefs();
			if(status == 1)
				numUsers += 1;
		}
		else if(userChoice == 3){
			// Recompute weights, and update the coefficients
			ldaComputation(masterList);
		}
		else if(userChoice == 4){
			std::cout << "Saving users to the database." << std::endl;
			for(int i = 0; i < numUsers ; i++){
				masterList[i].flushUserToFile();
			}
		}
		else if(userChoice == 5){
			std::cout << "Exiting program" << std::endl;
			return 0;
		}
		else
			std::cout << "Invalid choice" << std::endl;
	}
}
