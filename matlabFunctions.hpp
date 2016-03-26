// this header contains all the calls for functions created from the matlab script provided 
// from hatzinakos

#ifndef matlabFunctions
#define matlabFunctions

#include "userClass.hpp"
#include "alglib/dataanalysis.h"
#include "alglib/ap.h"
#include <math.h>

// Takes in two float arrays of wavelet coefs 
float distCompare(User first, User second);
// Takes autocorellation of the function
void autocorellation(User input,std::vector<float> &ac);
// Perform LDA on the set TODO
void ldaComputation(std::vector<User> &masterList);
// 

#endif
