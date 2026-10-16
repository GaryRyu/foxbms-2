/* DOCX 4.1--4.11 PSTUnit; production unchanged. */
#include "application_contract.h"
#include "../../../../../src/app/application/algorithm/state_estimation/state_estimation.c"
PST_SUITE(algorithm_state_estimation_state_estimation);
/* F2-LLR-ALG-031-TC-01-01: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_state_estimation,F2_LLR_ALG_031_TC_01_01) {
    pst_reset_contract();
    memset(&se_tableSocEstimation,0,sizeof(se_tableSocEstimation));se_tableSocEstimation.header.uniqueId=DATA_BLOCK_ID_SOC;
    memset(&se_tableSoeEstimation,0,sizeof(se_tableSoeEstimation));se_tableSoeEstimation.header.uniqueId=DATA_BLOCK_ID_SOE;
    memset(&se_tableSohEstimation,0,sizeof(se_tableSohEstimation));se_tableSohEstimation.header.uniqueId=DATA_BLOCK_ID_SOH;
    PST_EXPECT_SUT_ASSERT(SE_InitializeSoc(true,1u),78);
}

/* F2-LLR-ALG-031-TC-01-02: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_state_estimation,F2_LLR_ALG_031_TC_01_02) {
    pst_reset_contract();
    memset(&se_tableSocEstimation,0,sizeof(se_tableSocEstimation));se_tableSocEstimation.header.uniqueId=DATA_BLOCK_ID_SOC;
    memset(&se_tableSoeEstimation,0,sizeof(se_tableSoeEstimation));se_tableSoeEstimation.header.uniqueId=DATA_BLOCK_ID_SOE;
    memset(&se_tableSohEstimation,0,sizeof(se_tableSohEstimation));se_tableSohEstimation.header.uniqueId=DATA_BLOCK_ID_SOH;
    PST_EXPECT_SUT_ASSERT(SE_InitializeSoe(true,1u),84);
}

/* F2-LLR-ALG-031-TC-01-03: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_state_estimation,F2_LLR_ALG_031_TC_01_03) {
    pst_reset_contract();
    memset(&se_tableSocEstimation,0,sizeof(se_tableSocEstimation));se_tableSocEstimation.header.uniqueId=DATA_BLOCK_ID_SOC;
    memset(&se_tableSoeEstimation,0,sizeof(se_tableSoeEstimation));se_tableSoeEstimation.header.uniqueId=DATA_BLOCK_ID_SOE;
    memset(&se_tableSohEstimation,0,sizeof(se_tableSohEstimation));se_tableSohEstimation.header.uniqueId=DATA_BLOCK_ID_SOH;
    PST_EXPECT_SUT_ASSERT(SE_InitializeSoh(1u),90);
}

/* F2-LLR-ALG-031-TC-01-04: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_state_estimation,F2_LLR_ALG_031_TC_01_04) {
    pst_reset_contract();
    memset(&se_tableSocEstimation,0,sizeof(se_tableSocEstimation));se_tableSocEstimation.header.uniqueId=DATA_BLOCK_ID_SOC;
    memset(&se_tableSoeEstimation,0,sizeof(se_tableSoeEstimation));se_tableSoeEstimation.header.uniqueId=DATA_BLOCK_ID_SOE;
    memset(&se_tableSohEstimation,0,sizeof(se_tableSohEstimation));se_tableSohEstimation.header.uniqueId=DATA_BLOCK_ID_SOH;
    PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfCharge(NULL,true,1u - 1u),73);
}

/* F2-LLR-ALG-031-TC-01-05: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_state_estimation,F2_LLR_ALG_031_TC_01_05) {
    pst_reset_contract();
    DATA_BLOCK_SOC_s table_testSoc = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    memset(&se_tableSocEstimation,0,sizeof(se_tableSocEstimation));se_tableSocEstimation.header.uniqueId=DATA_BLOCK_ID_SOC;
    memset(&se_tableSoeEstimation,0,sizeof(se_tableSoeEstimation));se_tableSoeEstimation.header.uniqueId=DATA_BLOCK_ID_SOE;
    memset(&se_tableSohEstimation,0,sizeof(se_tableSohEstimation));se_tableSohEstimation.header.uniqueId=DATA_BLOCK_ID_SOH;
    PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfCharge(&table_testSoc,true,1u),75);
}

/* F2-LLR-ALG-031-TC-01-06: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_state_estimation,F2_LLR_ALG_031_TC_01_06) {
    pst_reset_contract();
    memset(&se_tableSocEstimation,0,sizeof(se_tableSocEstimation));se_tableSocEstimation.header.uniqueId=DATA_BLOCK_ID_SOC;
    memset(&se_tableSoeEstimation,0,sizeof(se_tableSoeEstimation));se_tableSoeEstimation.header.uniqueId=DATA_BLOCK_ID_SOE;
    memset(&se_tableSohEstimation,0,sizeof(se_tableSohEstimation));se_tableSohEstimation.header.uniqueId=DATA_BLOCK_ID_SOH;
    PST_EXPECT_SUT_ASSERT(SE_CalculateStateOfCharge(NULL),79);
}

/* F2-LLR-ALG-031-TC-01-07: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_state_estimation,F2_LLR_ALG_031_TC_01_07) {
    pst_reset_contract();
    memset(&se_tableSocEstimation,0,sizeof(se_tableSocEstimation));se_tableSocEstimation.header.uniqueId=DATA_BLOCK_ID_SOC;
    memset(&se_tableSoeEstimation,0,sizeof(se_tableSoeEstimation));se_tableSoeEstimation.header.uniqueId=DATA_BLOCK_ID_SOE;
    memset(&se_tableSohEstimation,0,sizeof(se_tableSohEstimation));se_tableSohEstimation.header.uniqueId=DATA_BLOCK_ID_SOH;
    PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfEnergy(NULL,true,1u - 1u),72);
}

/* F2-LLR-ALG-031-TC-01-08: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_state_estimation,F2_LLR_ALG_031_TC_01_08) {
    pst_reset_contract();
    DATA_BLOCK_SOE_s table_testSoe = {.header.uniqueId = DATA_BLOCK_ID_SOE};
    memset(&se_tableSocEstimation,0,sizeof(se_tableSocEstimation));se_tableSocEstimation.header.uniqueId=DATA_BLOCK_ID_SOC;
    memset(&se_tableSoeEstimation,0,sizeof(se_tableSoeEstimation));se_tableSoeEstimation.header.uniqueId=DATA_BLOCK_ID_SOE;
    memset(&se_tableSohEstimation,0,sizeof(se_tableSohEstimation));se_tableSohEstimation.header.uniqueId=DATA_BLOCK_ID_SOH;
    PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfEnergy(&table_testSoe,true,1u),74);
}

/* F2-LLR-ALG-031-TC-01-09: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_state_estimation,F2_LLR_ALG_031_TC_01_09) {
    pst_reset_contract();
    memset(&se_tableSocEstimation,0,sizeof(se_tableSocEstimation));se_tableSocEstimation.header.uniqueId=DATA_BLOCK_ID_SOC;
    memset(&se_tableSoeEstimation,0,sizeof(se_tableSoeEstimation));se_tableSoeEstimation.header.uniqueId=DATA_BLOCK_ID_SOE;
    memset(&se_tableSohEstimation,0,sizeof(se_tableSohEstimation));se_tableSohEstimation.header.uniqueId=DATA_BLOCK_ID_SOH;
    PST_EXPECT_SUT_ASSERT(SE_CalculateStateOfEnergy(NULL),78);
}

/* F2-LLR-ALG-031-TC-01-10: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_state_estimation,F2_LLR_ALG_031_TC_01_10) {
    pst_reset_contract();
    memset(&se_tableSocEstimation,0,sizeof(se_tableSocEstimation));se_tableSocEstimation.header.uniqueId=DATA_BLOCK_ID_SOC;
    memset(&se_tableSoeEstimation,0,sizeof(se_tableSoeEstimation));se_tableSoeEstimation.header.uniqueId=DATA_BLOCK_ID_SOE;
    memset(&se_tableSohEstimation,0,sizeof(se_tableSohEstimation));se_tableSohEstimation.header.uniqueId=DATA_BLOCK_ID_SOH;
    PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfHealth(NULL,1u - 1u),72);
}

/* F2-LLR-ALG-031-TC-01-11: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_state_estimation,F2_LLR_ALG_031_TC_01_11) {
    pst_reset_contract();
    DATA_BLOCK_SOH_s table_testSoh = {.header.uniqueId = DATA_BLOCK_ID_SOH};
    memset(&se_tableSocEstimation,0,sizeof(se_tableSocEstimation));se_tableSocEstimation.header.uniqueId=DATA_BLOCK_ID_SOC;
    memset(&se_tableSoeEstimation,0,sizeof(se_tableSoeEstimation));se_tableSoeEstimation.header.uniqueId=DATA_BLOCK_ID_SOE;
    memset(&se_tableSohEstimation,0,sizeof(se_tableSohEstimation));se_tableSohEstimation.header.uniqueId=DATA_BLOCK_ID_SOH;
    PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfHealth(&table_testSoh,1u),73);
}

/* F2-LLR-ALG-031-TC-01-12: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_state_estimation,F2_LLR_ALG_031_TC_01_12) {
    pst_reset_contract();
    memset(&se_tableSocEstimation,0,sizeof(se_tableSocEstimation));se_tableSocEstimation.header.uniqueId=DATA_BLOCK_ID_SOC;
    memset(&se_tableSoeEstimation,0,sizeof(se_tableSoeEstimation));se_tableSoeEstimation.header.uniqueId=DATA_BLOCK_ID_SOE;
    memset(&se_tableSohEstimation,0,sizeof(se_tableSohEstimation));se_tableSohEstimation.header.uniqueId=DATA_BLOCK_ID_SOH;
    PST_EXPECT_SUT_ASSERT(SE_CalculateStateOfHealth(NULL),77);
}

/* F2-LLR-ALG-031-TC-02: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_state_estimation,F2_LLR_ALG_031_TC_02) {
    pst_reset_contract();
    DATA_BLOCK_SOC_s se_tableSocEstimation = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    bool ccPresent = true;
    uint8_t stringNumber = 0u;
    memset(&se_tableSocEstimation,0,sizeof(se_tableSocEstimation));se_tableSocEstimation.header.uniqueId=DATA_BLOCK_ID_SOC;
    memset(&se_tableSoeEstimation,0,sizeof(se_tableSoeEstimation));se_tableSoeEstimation.header.uniqueId=DATA_BLOCK_ID_SOE;
    memset(&se_tableSohEstimation,0,sizeof(se_tableSohEstimation));se_tableSohEstimation.header.uniqueId=DATA_BLOCK_ID_SOH;
    SE_InitializeSoc(true,0u);
    PST_EQ(pst_writes,1);
}

/* F2-LLR-ALG-031-TC-03: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_state_estimation,F2_LLR_ALG_031_TC_03) {
    pst_reset_contract();
    DATA_BLOCK_SOE_s se_tableSoeEstimation = {.header.uniqueId = DATA_BLOCK_ID_SOE};
    bool ecPresent = true;
    uint8_t stringNumber = 0u;
    memset(&se_tableSocEstimation,0,sizeof(se_tableSocEstimation));se_tableSocEstimation.header.uniqueId=DATA_BLOCK_ID_SOC;
    memset(&se_tableSoeEstimation,0,sizeof(se_tableSoeEstimation));se_tableSoeEstimation.header.uniqueId=DATA_BLOCK_ID_SOE;
    memset(&se_tableSohEstimation,0,sizeof(se_tableSohEstimation));se_tableSohEstimation.header.uniqueId=DATA_BLOCK_ID_SOH;
    SE_InitializeSoe(true,0u);
    PST_EQ(pst_writes,1);
}

/* F2-LLR-ALG-031-TC-04: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_state_estimation,F2_LLR_ALG_031_TC_04) {
    pst_reset_contract();
    DATA_BLOCK_SOH_s se_tableSohEstimation = {.header.uniqueId = DATA_BLOCK_ID_SOH};
    uint8_t stringNumber = 0u;
    memset(&se_tableSocEstimation,0,sizeof(se_tableSocEstimation));se_tableSocEstimation.header.uniqueId=DATA_BLOCK_ID_SOC;
    memset(&se_tableSoeEstimation,0,sizeof(se_tableSoeEstimation));se_tableSoeEstimation.header.uniqueId=DATA_BLOCK_ID_SOE;
    memset(&se_tableSohEstimation,0,sizeof(se_tableSohEstimation));se_tableSohEstimation.header.uniqueId=DATA_BLOCK_ID_SOH;
    SE_InitializeSoh(0u);
    PST_EQ(pst_writes,1);
}

/* F2-LLR-ALG-031-TC-05: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_state_estimation,F2_LLR_ALG_031_TC_05) {
    pst_reset_contract();
    DATA_BLOCK_SOC_s se_tableSocEstimation = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    DATA_BLOCK_SOH_s se_tableSohEstimation = {.header.uniqueId = DATA_BLOCK_ID_SOH};
    DATA_BLOCK_SOE_s se_tableSoeEstimation = {.header.uniqueId = DATA_BLOCK_ID_SOE};
    memset(&se_tableSocEstimation,0,sizeof(se_tableSocEstimation));se_tableSocEstimation.header.uniqueId=DATA_BLOCK_ID_SOC;
    memset(&se_tableSoeEstimation,0,sizeof(se_tableSoeEstimation));se_tableSoeEstimation.header.uniqueId=DATA_BLOCK_ID_SOE;
    memset(&se_tableSohEstimation,0,sizeof(se_tableSohEstimation));se_tableSohEstimation.header.uniqueId=DATA_BLOCK_ID_SOH;
    SE_RunStateEstimations();
    PST_EQ(pst_writes,3);
    PST_EQ(pst_written_ids[0],DATA_BLOCK_ID_SOC);
    PST_EQ(pst_written_ids[1],DATA_BLOCK_ID_SOH);
    PST_EQ(pst_written_ids[2],DATA_BLOCK_ID_SOE);
}
