/* DOCX 4.1--4.11 PSTUnit; production unchanged. */
#include "application_contract.h"
#include "../../../../../../../src/app/application/algorithm/state_estimation/soc/debug/soc_debug.c"
PST_SUITE(algorithm_state_estimation_soc_debug_soc_debug);
/* F2-LLR-ALG-011-TC-01-01: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_debug_soc_debug,F2_LLR_ALG_011_TC_01_01) {
    pst_reset_contract();
    PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfCharge(NULL,true,0u),74);
}

/* F2-LLR-ALG-011-TC-01-02: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_debug_soc_debug,F2_LLR_ALG_011_TC_01_02) {
    pst_reset_contract();
    DATA_BLOCK_SOC_s se_tableSocEstimation = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfCharge(&se_tableSocEstimation,true,1u),75);
}

/* F2-LLR-ALG-011-TC-01-03: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_debug_soc_debug,F2_LLR_ALG_011_TC_01_03) {
    pst_reset_contract();
    DATA_BLOCK_SOC_s se_tableSocEstimation = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    __typeof__(se_tableSocEstimation) before=se_tableSocEstimation;
    SE_InitializeStateOfCharge(&se_tableSocEstimation,true,0u);
    PST_EQ(memcmp(&before,&se_tableSocEstimation,sizeof(before)),0);
}

/* F2-LLR-ALG-011-TC-02-01: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_debug_soc_debug,F2_LLR_ALG_011_TC_02_01) {
    pst_reset_contract();
    PST_EXPECT_SUT_ASSERT(SE_CalculateStateOfCharge(NULL),79);
}

/* F2-LLR-ALG-011-TC-02-02: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_debug_soc_debug,F2_LLR_ALG_011_TC_02_02) {
    pst_reset_contract();
    DATA_BLOCK_SOC_s se_tableSocEstimation = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    __typeof__(se_tableSocEstimation) before=se_tableSocEstimation;
    SE_CalculateStateOfCharge(&se_tableSocEstimation);
    PST_EQ(memcmp(&before,&se_tableSocEstimation,sizeof(before)),0);
}

/* F2-LLR-ALG-011-TC-03: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_debug_soc_debug,F2_LLR_ALG_011_TC_03) {
    pst_reset_contract();
    PST_EQ(SE_GetStateOfChargeFromVoltage(0u),0.50f);
}
