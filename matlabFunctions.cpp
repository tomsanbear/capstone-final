#include "matlabFunctions.hpp"

float distCompare(User *&challenge, std::vector<User> &masterList){
	//
	float distance = 1;
	return distance;
}

void ldaComputation(std::vector<User> &masterList){
	long int nvars = masterList[0].vectorCoefs[0].size();// Number of wavelet coefs for each trainig set
	long int nclasses = masterList.size(); // Number of users
	long int info = 0;
	long int M = masterList[0].vectorCoefs.size();
	long int npoints = M*nclasses;
	alglib::real_2d_array w;
	// We initilize this variable with the proper rows and columns
	alglib::real_2d_array xy;
	xy.setlength(nclasses*M, nvars+1);
	// Load masterlist into the xy array
	// we iterate through a for loop to mark off the classes in the
	// matrix, then we
	for(int i = 0; i < nclasses; i++){ // iterate through each class
		for(int j=0;j < M;j++){ // iterate through each class' rows
			xy(j+i*M,nvars) = i;
			for(int k=0; k < nvars;k++){ // iterate through each class' row elements
				xy(j+i*M,k)=masterList[i].vectorCoefs[j][k];
			}
		}
	}
	// Execute the algorithm to obtain training weights
	alglib::fisherldan(xy,npoints,nvars,nclasses,info,w);
	// Send weights back to original function
	// NxM
	for(int i = 0; i <= masterList[0].vectorCoefs.size()-1; i++){
		for(int j = 0; j <=  nvars; j++){
			for(int k =0; k<= masterList[1].vectorCoefs.size();k++)
				masterList[i].weights[j].push_back(w(i,k));
		}
	}
	//Apply the weights to the coefficients
	int n1 = masterList[0].vectorCoefs[0].size();
	int n2 = masterList[0].weights[0].size();
	int nCommon = masterList[0].vectorCoefs.size();
	for(int h =0; h<=nclasses;h++){
		assert(masterList[h].vectorCoefs[0].size() == nCommon);
		for (int i = 0; i < n1; i++) {
			for (int j = 0; j < n2; j++) {
				for (int k = 0; k < nCommon ; k++) {
					masterList[h].weightedCoefs[i][j] += masterList[h].vectorCoefs[i][k] * masterList[h].weightedCoefs[k][j];
				}
			}
		}
	}
	return;
}
