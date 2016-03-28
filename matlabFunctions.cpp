#include "matlabFunctions.hpp"

void distCompare(User *&challenge, std::vector<User> &masterList, float *&distList){
	//

	return;
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
	for(int i = 0; i < nclasses; i++){ // store weights in each user
		masterList[i].weights.resize(nvars);
		for(int j = 0; j < nvars; j++){ // store each weight iteration
			for(int k =0; k< nvars;k++){
				std::cout << w(j,k) << " ";
				masterList[i].weights[j].push_back(w(j,k));
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	// Apply the weights to the coefficients TODO
	int n1 = masterList[0].vectorCoefs.size(); // rows of coefs
	int n2 = masterList[0].weights[0].size();	// cols of weights
	int nCommon = masterList[0].vectorCoefs[0].size();  // rows of coefs
	//setup size of weighted coef
	// Transpose the weight matrix for convenience in next loop set
	std::vector< std::vector<double> > temp;
	temp.resize(nCommon);
	for(int i = 0; i < nCommon ; i++){
		for(int j=0 ; j < n1; j++){
			temp[i].push_back(masterList[0].weights[j][i]);
		}
	}
	std::cout << "coefficients: " << std::endl;
	for(int h =0; h < nclasses;h++){ // iterate through each user to compute coefs
		//setup size of weighted coef
		masterList[h].weightedCoefs.resize(nCommon);
		//assert(masterList[h].vectorCoefs[0].size() == nCommon); // check for common dim
		for (int i = 0; i < n1; i++) {
			masterList[h].weightedCoefs[i].resize(n1);
			for (int j = 0; j < n2; j++) {
				for (int k = 0; k < nCommon ; k++) {
					masterList[h].weightedCoefs[i][j] += masterList[h].vectorCoefs[i][k] * temp[k][j];
				}
				std::cout << masterList[h].weightedCoefs[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	return;
}
