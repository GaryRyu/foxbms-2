/* Verify installed C PST_ABORT unwinds a callback and runs the following test. */
#include "pstunit.h"
static int escaped=0;
static void callback(void) { PST_ABORT(); escaped=1; }
PST_SUITE(abort_probe);
PST_TEST(abort_probe, abort_in_callback) { callback(); escaped=2; }
PST_TEST(abort_probe, next_case_runs) { PST_VERIFY_EQ_INT(escaped,0); }
