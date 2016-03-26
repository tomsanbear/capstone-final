#include "matlabFunctions.hpp"

float distCompare(float *first, float *second){
	// code here
	return 1;
}

void ldaComputation(std::vector<float> weights,std::vector<User> &masterList){
	long int npoints = masterList.size();
	long int nvars = masterList.size();
	long int nclasses = 3;
	long int info = 1;
	alglib::real_1d_array w;
	alglib::real_2d_array xy;
	// Load masterlist into the xy array
	alglib::fisherlda(&xy,npoints,nvars,nclasses,&info,&w);
	//Send weights back to original function
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
