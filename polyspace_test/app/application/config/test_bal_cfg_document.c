/* Requirement-based unit tests. Static source access explicitly authorized. */
#include "application_contract.h"
#include "../../../../src/app/application/config/bal_cfg.c"

PST_SUITE(config_bal_cfg);
/* F2-LLR-ALG-063-TC-01 */
PST_TEST(config_bal_cfg,F2_LLR_ALG_063_TC_01) {
pst_reset_contract();bal_threshold_mV=BAL_DEFAULT_THRESHOLD_mV;
BAL_SetBalancingThreshold(50);
PST_EQ(BAL_GetBalancingThreshold_mV(),50);
BAL_SetBalancingThreshold(150);
PST_EQ(BAL_GetBalancingThreshold_mV(),150);
PST_EQ(pst_enter_calls,2);PST_EQ(pst_exit_calls,2);
}

/* F2-LLR-ALG-063-TC-02 */
PST_TEST(config_bal_cfg,F2_LLR_ALG_063_TC_02) {
pst_reset_contract();bal_threshold_mV=BAL_DEFAULT_THRESHOLD_mV;
BAL_SetBalancingThreshold((5000 + 1));
PST_EQ(BAL_GetBalancingThreshold_mV(),(5000 + 1) - 1);
PST_EQ(pst_enter_calls,1);PST_EQ(pst_exit_calls,1);
}

/* F2-LLR-ALG-063-TC-03 */
PST_TEST(config_bal_cfg,F2_LLR_ALG_063_TC_03) {
pst_reset_contract();bal_threshold_mV=BAL_DEFAULT_THRESHOLD_mV;
BAL_SetBalancingThreshold(0 - 1);
PST_EQ(BAL_GetBalancingThreshold_mV(),0 - 1 + 1);
PST_EQ(pst_enter_calls,1);PST_EQ(pst_exit_calls,1);
}

/* F2-LLR-ALG-063-01-ADD-001: default threshold */
PST_TEST(config_bal_cfg,F2_LLR_ALG_063_01_ADD_001) {
pst_reset_contract();bal_threshold_mV=BAL_DEFAULT_THRESHOLD_mV;PST_EQ(BAL_GetBalancingThreshold_mV(),BAL_DEFAULT_THRESHOLD_mV);
}
