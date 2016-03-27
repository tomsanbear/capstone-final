#include "matlabFunctions.hpp"

float distCompare(User challenge, std::vector<User> masterList){
	// code here
	return 1;
}

void ldaComputation(std::vector<User> &masterList){
	long int npoints = masterList.size() * masterList[1].vectorCoefs.size(); // all sets are trained to the same size
	long int nvars = masterList[1].vectorCoefs[1].size(); // Number of wavelet coefs for each trainig set
	long int nclasses = masterList.size(); // Number of users
	long int info = 0;
	alglib::real_1d_array w;

	// We initilize this variable with the proper rows and columns
	alglib::real_2d_array xy;
	xy.setlength(nclasses*masterList[1].vectorCoefs.size(), nvars+1);
	// Load masterlist into the xy array
	// we iterate through a for loop to mark off the classes in the
	// matrix, then we
	for(int i = 0; i <= nclasses-1; i++){ // iterate through each class
		for(int j=0;j<= masterList[1].vectorCoefs.size();j++){ // iterate through each class' rows
			xy(j,nvars) = i;
			for(int k=0;k<=nvars-1;k++){ // iterate through each class' row elements
				xy(j,k)=masterList[i].vectorCoefs[j][k];
			}
		}
	}
	//Execute the algorithm to obtain training weights
	alglib::fisherlda(xy,npoints,nvars,nclasses,info,w);
	//Send weights back to original function
	for(int i = 0; i <= masterList[1].vectorCoefs.size(); i++){
		for(int j = 0; j <=  nvars; j++){
			masterList[i].weights[j] = w(i);
		}
	}
	//Apply the weights to the coefficients

	return;
}

// Takes input of windowed data, M, and upsample M
void autocorellation(int M,int upM, std::vector<float> windowSig,std::vector<float> &ac){
	int sizeOf = windowSig.size();
	for(int i= 0; i<= sizeOf;i++){
		for(int j=0;j<=M+1;j++){
			//insert ac code here TODO
		}
	}
}
