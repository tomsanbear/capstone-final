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
	alglib::real_2d_array w;

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

// Takes input of windowed data, M, and upsample M
void autocorellation(int M,int upM, std::vector<float> windowSig,std::vector<float> &ac){
	int sizeOf = windowSig.size();
	for(int i= 0; i<= sizeOf;i++){
		for(int j=0;j<=M+1;j++){
			//insert ac code here TODO
		}
	}
}
