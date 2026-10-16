/* Requirement-based unit tests. Static source access explicitly authorized. */
#include "application_contract.h"
#include "../../../../../src/app/application/bal/none/bal_strategy_none.c"

PST_SUITE(bal_none_bal_strategy_none);
/* F2-LLR-ALG-046-TC-25 */
PST_TEST(bal_none_bal_strategy_none,F2_LLR_ALG_046_TC_25) {
pst_reset_contract();PST_EQ(BAL_GetInitializationState(),STD_OK);PST_EQ(BAL_SetStateRequest(BAL_STATE_INIT_REQUEST),BAL_OK);BAL_Trigger();PST_EQ(pst_reads,0);PST_EQ(pst_writes,0);
}
