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
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

// 
// Create the user class
// Contains the following data on each user:
// -name
// -size of data held
// -detailed coefs
//
// Functions:
// -Add user from data stored
// -Add user from data passed within the program
// -Delete user
//
class User{
	public:
		string name;
		int numCoefs;
		float [] detCoefs;

		// Member Functions
		void initializefromfile(string filename);
		void initializeNewUser(string username, float *[] coefs, int numEntries);
		User();
}

//
// Write the member functions of the User class
//

void User::initializefromfile(string filename){
	// TODO: Sophs code here
}

void User::initializeNewUser(string filename, float *[] coefs, int numEntries)
	// Enter in class member variables
	name = filename;
	numCoefs = numEntries;
	cout << "User info created." << endl;

	// Initialize the EKG detection
	// TODO: add my code to receive datahere
	

	// TODO: Window the data
	

	// TODO: Perform autocorellation
	

	// TODO: LDA algorithm
	

	// TODO: Obtain detailed coefficients, and populate the coefs array
	

	// TODO: add sophs code for saving to file here
	cout << "User info saved to file." << endl;
}

User::User(void){
	cout << "Empty user initialized." << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////
//			Function to compare two different users				//
//////////////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////////////////
//                         MAIN FUNCTION BELOW HERE					//
//////////////////////////////////////////////////////////////////////////////////////////

int main(){
	// Load data from all files detected
	// Currently user needs to manually tell the program how many existing users there are
	// TODO
	int numUsersToLoad;
	cin >> numUsersToLoad;
	for (int i=0,i<numUsersToLoad;i++){
		cout << "Adding user " << i << " to the program" << endl;
	}

	// Start of program, let user make choice on function to perform
	int userChoice;
	while(){
		cin >> userChoice;
		if(userChoice == 1){
			//Add from file
		}
		else if(userChoice == 2){
			// Enrol User in the system
		}
		else if(userChoice == 3){
			// Delete User
			numUsersToLoad = numUsersToLoad -1;
		}
		else if(userChoice == 4){
			cout << "Exiting program" << endl;
			break;
		else{
			cout << "Invallid choice" << endl;
		}
	}

	// Exit program
	return 0;
}
