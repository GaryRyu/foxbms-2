/* DOCX 4.1--4.11 PSTUnit; production unchanged. */
#include "application_contract.h"
#include "../../../../../../../src/app/application/algorithm/state_estimation/soe/debug/soe_debug.c"
PST_SUITE(algorithm_state_estimation_soe_debug_soe_debug);
/* F2-LLR-ALG-023-TC-01-01: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soe_debug_soe_debug,F2_LLR_ALG_023_TC_01_01) {
    pst_reset_contract();
    PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfEnergy(NULL,true,0u),72);
}

/* F2-LLR-ALG-023-TC-01-02: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soe_debug_soe_debug,F2_LLR_ALG_023_TC_01_02) {
    pst_reset_contract();
    DATA_BLOCK_SOE_s se_tableSoeEstimation = {.header.uniqueId = DATA_BLOCK_ID_SOE};
    PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfEnergy(&se_tableSoeEstimation,true,1u),73);
}

/* F2-LLR-ALG-023-TC-01-03: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soe_debug_soe_debug,F2_LLR_ALG_023_TC_01_03) {
    pst_reset_contract();
    DATA_BLOCK_SOE_s se_tableSoeEstimation = {.header.uniqueId = DATA_BLOCK_ID_SOE};
    __typeof__(se_tableSoeEstimation) before=se_tableSoeEstimation;
    SE_InitializeStateOfEnergy(&se_tableSoeEstimation,true,0u);
    PST_EQ(memcmp(&before,&se_tableSoeEstimation,sizeof(before)),0);
}

/* F2-LLR-ALG-023-TC-02-01: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soe_debug_soe_debug,F2_LLR_ALG_023_TC_02_01) {
    pst_reset_contract();
    PST_EXPECT_SUT_ASSERT(SE_CalculateStateOfEnergy(NULL),77);
}

/* F2-LLR-ALG-023-TC-02-02: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soe_debug_soe_debug,F2_LLR_ALG_023_TC_02_02) {
    pst_reset_contract();
    DATA_BLOCK_SOE_s se_tableSoeEstimation = {.header.uniqueId = DATA_BLOCK_ID_SOE};
    __typeof__(se_tableSoeEstimation) before=se_tableSoeEstimation;
    SE_CalculateStateOfEnergy(&se_tableSoeEstimation);
    PST_EQ(memcmp(&before,&se_tableSoeEstimation,sizeof(before)),0);
}
