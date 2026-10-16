/* DOCX 4.1--4.11 PSTUnit; production unchanged. */
#include "application_contract.h"
#include "../../../../../../../src/app/application/algorithm/state_estimation/soh/none/soh_none.c"
PST_SUITE(algorithm_state_estimation_soh_none_soh_none);
/* F2-LLR-ALG-029-TC-01-01: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soh_none_soh_none,F2_LLR_ALG_029_TC_01_01) {
    pst_reset_contract();
    PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfHealth(NULL,1u - 1u),72);
}

/* F2-LLR-ALG-029-TC-01-02: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soh_none_soh_none,F2_LLR_ALG_029_TC_01_02) {
    pst_reset_contract();
    DATA_BLOCK_SOH_s table_testSoh = {.header.uniqueId = DATA_BLOCK_ID_SOH};
    PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfHealth(&table_testSoh,1u),73);
}

/* F2-LLR-ALG-029-TC-01-03: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soh_none_soh_none,F2_LLR_ALG_029_TC_01_03) {
    pst_reset_contract();
    DATA_BLOCK_SOH_s table_testSoh = {.header.uniqueId = DATA_BLOCK_ID_SOH};
    __typeof__(table_testSoh) before=table_testSoh;
    SE_InitializeStateOfHealth(&table_testSoh,1u - 1u);
    PST_EQ(memcmp(&before,&table_testSoh,sizeof(before)),0);
}

/* F2-LLR-ALG-029-TC-02-01: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soh_none_soh_none,F2_LLR_ALG_029_TC_02_01) {
    pst_reset_contract();
    PST_EXPECT_SUT_ASSERT(SE_CalculateStateOfHealth(NULL),77);
}

/* F2-LLR-ALG-029-TC-02-02: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soh_none_soh_none,F2_LLR_ALG_029_TC_02_02) {
    pst_reset_contract();
    DATA_BLOCK_SOH_s table_testSoh = {.header.uniqueId = DATA_BLOCK_ID_SOH};
    __typeof__(table_testSoh) before=table_testSoh;
    SE_CalculateStateOfHealth(&table_testSoh);
    PST_EQ(memcmp(&before,&table_testSoh,sizeof(before)),0);
}
