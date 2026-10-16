/* External algorithm callback must not run in configuration API tests. */
#include "pstunit.h"
void ALGO_MovingAverage(void){PST_VERIFY_TRUE_MSG(0,"Unexpected algorithm callback");PST_ABORT();}
