#ifndef ekgRead
#define ekgRead

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include <vector>
#include <sys/time.h>
#include "ekgLib/GoIO_DLL_interface.h"

void readEKG(int sampleTime,std::vector<float> &newUser);

#endif
