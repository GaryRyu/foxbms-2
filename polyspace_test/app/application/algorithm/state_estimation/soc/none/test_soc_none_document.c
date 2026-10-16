/* DOCX 4.1--4.11 PSTUnit; production unchanged. */
#include "application_contract.h"
#include "../../../../../../../src/app/application/algorithm/state_estimation/soc/none/soc_none.c"
PST_SUITE(algorithm_state_estimation_soc_none_soc_none);
/* F2-LLR-ALG-020-TC-01-01: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_none_soc_none,F2_LLR_ALG_020_TC_01_01) {
    pst_reset_contract();
    PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfCharge(NULL,true,1u - 1u),73);
}

/* F2-LLR-ALG-020-TC-01-02: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_none_soc_none,F2_LLR_ALG_020_TC_01_02) {
    pst_reset_contract();
    DATA_BLOCK_SOC_s table_testSoc = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfCharge(&table_testSoc,true,1u),75);
}

/* F2-LLR-ALG-020-TC-01-03: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_none_soc_none,F2_LLR_ALG_020_TC_01_03) {
    pst_reset_contract();
    DATA_BLOCK_SOC_s table_testSoc = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    __typeof__(table_testSoc) before=table_testSoc;
    SE_InitializeStateOfCharge(&table_testSoc,true,1u - 1u);
    PST_EQ(memcmp(&before,&table_testSoc,sizeof(before)),0);
}

/* F2-LLR-ALG-020-TC-02-01: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_none_soc_none,F2_LLR_ALG_020_TC_02_01) {
    pst_reset_contract();
    PST_EXPECT_SUT_ASSERT(SE_CalculateStateOfCharge(NULL),79);
}

/* F2-LLR-ALG-020-TC-02-02: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_none_soc_none,F2_LLR_ALG_020_TC_02_02) {
    pst_reset_contract();
    DATA_BLOCK_SOC_s table_testSoc = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    __typeof__(table_testSoc) before=table_testSoc;
    SE_CalculateStateOfCharge(&table_testSoc);
    PST_EQ(memcmp(&before,&table_testSoc,sizeof(before)),0);
}

/* F2-LLR-ALG-020-TC-03: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_none_soc_none,F2_LLR_ALG_020_TC_03) {
    pst_reset_contract();
    PST_EQ(SE_GetStateOfChargeFromVoltage(1),0.0f);
}
