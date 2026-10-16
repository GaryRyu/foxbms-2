/* DOCX 4.1--4.11 PSTUnit; production unchanged. */
#include "application_contract.h"
#include "../../../../../../../src/app/application/algorithm/state_estimation/soe/none/soe_none.c"
PST_SUITE(algorithm_state_estimation_soe_none_soe_none);
/* F2-LLR-ALG-025-TC-01-01: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soe_none_soe_none,F2_LLR_ALG_025_TC_01_01) {
    pst_reset_contract();
    PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfEnergy(NULL,true,1u - 1u),72);
}

/* F2-LLR-ALG-025-TC-01-02: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soe_none_soe_none,F2_LLR_ALG_025_TC_01_02) {
    pst_reset_contract();
    DATA_BLOCK_SOE_s table_testSoe = {.header.uniqueId = DATA_BLOCK_ID_SOE};
    PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfEnergy(&table_testSoe,true,1u),74);
}

/* F2-LLR-ALG-025-TC-01-03: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soe_none_soe_none,F2_LLR_ALG_025_TC_01_03) {
    pst_reset_contract();
    DATA_BLOCK_SOE_s table_testSoe = {.header.uniqueId = DATA_BLOCK_ID_SOE};
    __typeof__(table_testSoe) before=table_testSoe;
    SE_InitializeStateOfEnergy(&table_testSoe,true,1u - 1u);
    PST_EQ(memcmp(&before,&table_testSoe,sizeof(before)),0);
}

/* F2-LLR-ALG-025-TC-02-01: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soe_none_soe_none,F2_LLR_ALG_025_TC_02_01) {
    pst_reset_contract();
    PST_EXPECT_SUT_ASSERT(SE_CalculateStateOfEnergy(NULL),78);
}

/* F2-LLR-ALG-025-TC-02-02: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soe_none_soe_none,F2_LLR_ALG_025_TC_02_02) {
    pst_reset_contract();
    DATA_BLOCK_SOE_s table_testSoe = {.header.uniqueId = DATA_BLOCK_ID_SOE};
    __typeof__(table_testSoe) before=table_testSoe;
    SE_CalculateStateOfEnergy(&table_testSoe);
    PST_EQ(memcmp(&before,&table_testSoe,sizeof(before)),0);
}
