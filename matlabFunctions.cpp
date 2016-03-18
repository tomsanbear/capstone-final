#include "matlabFunctions.hpp"

float distCompare(float *first, float *second){
	// code here
	
}

void ldaComputation(vector<User> masterList){
	const alglib_impl::ae_int_t npoints;
	const alglib_impl::ae_int_t nvars = masterList.size();
	const alglib_impl::ae_int_t nclasses;
	alglib_impl::ae_int_t *info;
	alglib::real_1d_array *w;
	alglib::real_2d_array xy;
	alglib_impl::ae_state *_state;
	// Load masterlist into the xy array
	
	// Set proper setup variables
	alglib_impl::fisherlda(xy,npoints,nvars,nclasses,info,w,_state);
	return;
}
