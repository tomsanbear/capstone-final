// this header contains all the calls for functions created from the matlab script

#ifndef matlabFunctions
#define matlabFunctions

#include "userClass.hpp"
#include "alglib/dataanalysis.h"
#include "alglib/ap.h"
#include <math.h>

// Takes in user and masterlist, outputs score
float distCompare(User *&challenge, std::vector<User> &masterList);

// Perform LDA on the set
void ldaComputation(std::vector<User> &masterList);
// 

#endif
