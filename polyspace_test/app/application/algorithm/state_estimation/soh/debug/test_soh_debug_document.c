/* DOCX 4.1--4.11 PSTUnit; production unchanged. */
#include "application_contract.h"
#include "../../../../../../../src/app/application/algorithm/state_estimation/soh/debug/soh_debug.c"
PST_SUITE(algorithm_state_estimation_soh_debug_soh_debug);
/* F2-LLR-ALG-027-TC-01-01: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soh_debug_soh_debug,F2_LLR_ALG_027_TC_01_01) {
    pst_reset_contract();
    PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfHealth(NULL,0u),72);
}

/* F2-LLR-ALG-027-TC-01-02: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soh_debug_soh_debug,F2_LLR_ALG_027_TC_01_02) {
    pst_reset_contract();
    DATA_BLOCK_SOH_s se_tableSohEstimation = {.header.uniqueId = DATA_BLOCK_ID_SOH};
    PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfHealth(&se_tableSohEstimation,1u),73);
}

/* F2-LLR-ALG-027-TC-01-03: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soh_debug_soh_debug,F2_LLR_ALG_027_TC_01_03) {
    pst_reset_contract();
    DATA_BLOCK_SOH_s se_tableSohEstimation = {.header.uniqueId = DATA_BLOCK_ID_SOH};
    __typeof__(se_tableSohEstimation) before=se_tableSohEstimation;
    SE_InitializeStateOfHealth(&se_tableSohEstimation,0u);
    PST_EQ(se_tableSohEstimation.averageSoh_perc[0],0.0f);
    PST_EQ(se_tableSohEstimation.minimumSoh_perc[0],0.0f);
    PST_EQ(se_tableSohEstimation.maximumSoh_perc[0],0.0f);
    PST_EQ(se_tableSohEstimation.averageSoh_perc[0],0.0f);
    PST_EQ(se_tableSohEstimation.minimumSoh_perc[0],0.0f);
    PST_EQ(se_tableSohEstimation.maximumSoh_perc[0],0.0f);
}

/* F2-LLR-ALG-027-TC-02-01: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soh_debug_soh_debug,F2_LLR_ALG_027_TC_02_01) {
    pst_reset_contract();
    PST_EXPECT_SUT_ASSERT(SE_CalculateStateOfHealth(NULL),80);
}

/* F2-LLR-ALG-027-TC-02-02: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soh_debug_soh_debug,F2_LLR_ALG_027_TC_02_02) {
    pst_reset_contract();
    DATA_BLOCK_SOH_s se_tableSohEstimation = {.header.uniqueId = DATA_BLOCK_ID_SOH};
    __typeof__(se_tableSohEstimation) before=se_tableSohEstimation;
    SE_CalculateStateOfHealth(&se_tableSohEstimation);
    PST_EQ(se_tableSohEstimation.averageSoh_perc[0],50.0f);
    PST_EQ(se_tableSohEstimation.minimumSoh_perc[0],49.9f);
    PST_EQ(se_tableSohEstimation.maximumSoh_perc[0],50.1f);
    PST_EQ(se_tableSohEstimation.averageSoh_perc[0],50.0f);
    PST_EQ(se_tableSohEstimation.minimumSoh_perc[0],49.9f);
    PST_EQ(se_tableSohEstimation.maximumSoh_perc[0],50.1f);
}
