/* DOCX 4.1--4.11 PSTUnit; production unchanged. */
#include "application_contract.h"
#include "fram.h"
#include "../../../../../../../src/app/application/algorithm/state_estimation/soc/counting/soc_counting.c"
PST_SUITE(algorithm_state_estimation_soc_counting_soc_counting);
/* F2-LLR-ALG-008-TC-01: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_counting_soc_counting,F2_LLR_ALG_008_TC_01) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    int16_t test_voltage_mV = 3780;
    memset(&fram_soc,0,sizeof(fram_soc));
    PST_EQ(SE_GetStateOfChargeFromVoltage(3780),64.0f);
}

/* F2-LLR-ALG-008-TC-02-01: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_counting_soc_counting,F2_LLR_ALG_008_TC_02_01) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    DATA_BLOCK_SOC_s cp_pTableSoc = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    memset(&fram_soc,0,sizeof(fram_soc));
    PST_EXPECT_SUT_ASSERT(SOC_CheckDatabaseSocPercentageLimits(&cp_pTableSoc,1u),221);
}

/* F2-LLR-ALG-008-TC-02-02: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_counting_soc_counting,F2_LLR_ALG_008_TC_02_02) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    memset(&fram_soc,0,sizeof(fram_soc));
    PST_EXPECT_SUT_ASSERT(SOC_CheckDatabaseSocPercentageLimits(NULL,0u),220);
}

/* F2-LLR-ALG-008-TC-02-03: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_counting_soc_counting,F2_LLR_ALG_008_TC_02_03) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    DATA_BLOCK_SOC_s cp_pTableSoc = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    memset(&fram_soc,0,sizeof(fram_soc));
    DATA_BLOCK_SOC_s cp_pTableSoc_before=cp_pTableSoc;
    SOC_CheckDatabaseSocPercentageLimits(&cp_pTableSoc,0u);
    PST_EQ(cp_pTableSoc.averageSoc_perc[0],(cp_pTableSoc_before.averageSoc_perc[0]<0?0:(cp_pTableSoc_before.averageSoc_perc[0]>100?100:cp_pTableSoc_before.averageSoc_perc[0])));
    PST_EQ(cp_pTableSoc.minimumSoc_perc[0],(cp_pTableSoc_before.minimumSoc_perc[0]<0?0:(cp_pTableSoc_before.minimumSoc_perc[0]>100?100:cp_pTableSoc_before.minimumSoc_perc[0])));
    PST_EQ(cp_pTableSoc.maximumSoc_perc[0],(cp_pTableSoc_before.maximumSoc_perc[0]<0?0:(cp_pTableSoc_before.maximumSoc_perc[0]>100?100:cp_pTableSoc_before.maximumSoc_perc[0])));
    PST_EQ(cp_pTableSoc.chargeThroughput_As[0],cp_pTableSoc_before.chargeThroughput_As[0]);
    PST_EQ(cp_pTableSoc.dischargeThroughput_As[0],cp_pTableSoc_before.dischargeThroughput_As[0]);
}

/* F2-LLR-ALG-008-TC-02-04: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_counting_soc_counting,F2_LLR_ALG_008_TC_02_04) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    DATA_BLOCK_SOC_s cp_pTableSoc = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    memset(&fram_soc,0,sizeof(fram_soc));
    cp_pTableSoc.averageSoc_perc[0] = 101.0f;
    DATA_BLOCK_SOC_s cp_pTableSoc_before=cp_pTableSoc;
    SOC_CheckDatabaseSocPercentageLimits(&cp_pTableSoc,0u);
    PST_EQ(cp_pTableSoc.averageSoc_perc[0u],100.0f);
    PST_EQ(cp_pTableSoc.averageSoc_perc[0],(cp_pTableSoc_before.averageSoc_perc[0]<0?0:(cp_pTableSoc_before.averageSoc_perc[0]>100?100:cp_pTableSoc_before.averageSoc_perc[0])));
    PST_EQ(cp_pTableSoc.minimumSoc_perc[0],(cp_pTableSoc_before.minimumSoc_perc[0]<0?0:(cp_pTableSoc_before.minimumSoc_perc[0]>100?100:cp_pTableSoc_before.minimumSoc_perc[0])));
    PST_EQ(cp_pTableSoc.maximumSoc_perc[0],(cp_pTableSoc_before.maximumSoc_perc[0]<0?0:(cp_pTableSoc_before.maximumSoc_perc[0]>100?100:cp_pTableSoc_before.maximumSoc_perc[0])));
    PST_EQ(cp_pTableSoc.chargeThroughput_As[0],cp_pTableSoc_before.chargeThroughput_As[0]);
    PST_EQ(cp_pTableSoc.dischargeThroughput_As[0],cp_pTableSoc_before.dischargeThroughput_As[0]);
}

/* F2-LLR-ALG-008-TC-02-05: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_counting_soc_counting,F2_LLR_ALG_008_TC_02_05) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    DATA_BLOCK_SOC_s cp_pTableSoc = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    memset(&fram_soc,0,sizeof(fram_soc));
    cp_pTableSoc.averageSoc_perc[0] = -1.0f;
    DATA_BLOCK_SOC_s cp_pTableSoc_before=cp_pTableSoc;
    SOC_CheckDatabaseSocPercentageLimits(&cp_pTableSoc,0u);
    PST_EQ(cp_pTableSoc.averageSoc_perc[0u],0.0f);
    PST_EQ(cp_pTableSoc.averageSoc_perc[0],(cp_pTableSoc_before.averageSoc_perc[0]<0?0:(cp_pTableSoc_before.averageSoc_perc[0]>100?100:cp_pTableSoc_before.averageSoc_perc[0])));
    PST_EQ(cp_pTableSoc.minimumSoc_perc[0],(cp_pTableSoc_before.minimumSoc_perc[0]<0?0:(cp_pTableSoc_before.minimumSoc_perc[0]>100?100:cp_pTableSoc_before.minimumSoc_perc[0])));
    PST_EQ(cp_pTableSoc.maximumSoc_perc[0],(cp_pTableSoc_before.maximumSoc_perc[0]<0?0:(cp_pTableSoc_before.maximumSoc_perc[0]>100?100:cp_pTableSoc_before.maximumSoc_perc[0])));
    PST_EQ(cp_pTableSoc.chargeThroughput_As[0],cp_pTableSoc_before.chargeThroughput_As[0]);
    PST_EQ(cp_pTableSoc.dischargeThroughput_As[0],cp_pTableSoc_before.dischargeThroughput_As[0]);
}

/* F2-LLR-ALG-008-TC-02-06: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_counting_soc_counting,F2_LLR_ALG_008_TC_02_06) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    DATA_BLOCK_SOC_s cp_pTableSoc = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    memset(&fram_soc,0,sizeof(fram_soc));
    cp_pTableSoc.averageSoc_perc[0] = 0.0f;
    cp_pTableSoc.minimumSoc_perc[0] = 101.0f;
    DATA_BLOCK_SOC_s cp_pTableSoc_before=cp_pTableSoc;
    SOC_CheckDatabaseSocPercentageLimits(&cp_pTableSoc,0u);
    PST_EQ(cp_pTableSoc.minimumSoc_perc[0u],100.0f);
    PST_EQ(cp_pTableSoc.averageSoc_perc[0],(cp_pTableSoc_before.averageSoc_perc[0]<0?0:(cp_pTableSoc_before.averageSoc_perc[0]>100?100:cp_pTableSoc_before.averageSoc_perc[0])));
    PST_EQ(cp_pTableSoc.minimumSoc_perc[0],(cp_pTableSoc_before.minimumSoc_perc[0]<0?0:(cp_pTableSoc_before.minimumSoc_perc[0]>100?100:cp_pTableSoc_before.minimumSoc_perc[0])));
    PST_EQ(cp_pTableSoc.maximumSoc_perc[0],(cp_pTableSoc_before.maximumSoc_perc[0]<0?0:(cp_pTableSoc_before.maximumSoc_perc[0]>100?100:cp_pTableSoc_before.maximumSoc_perc[0])));
    PST_EQ(cp_pTableSoc.chargeThroughput_As[0],cp_pTableSoc_before.chargeThroughput_As[0]);
    PST_EQ(cp_pTableSoc.dischargeThroughput_As[0],cp_pTableSoc_before.dischargeThroughput_As[0]);
}

/* F2-LLR-ALG-008-TC-02-07: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_counting_soc_counting,F2_LLR_ALG_008_TC_02_07) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    DATA_BLOCK_SOC_s cp_pTableSoc = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    memset(&fram_soc,0,sizeof(fram_soc));
    cp_pTableSoc.averageSoc_perc[0] = 0.0f;
    cp_pTableSoc.minimumSoc_perc[0] = -1.0f;
    DATA_BLOCK_SOC_s cp_pTableSoc_before=cp_pTableSoc;
    SOC_CheckDatabaseSocPercentageLimits(&cp_pTableSoc,0u);
    PST_EQ(cp_pTableSoc.minimumSoc_perc[0u],0.0f);
    PST_EQ(cp_pTableSoc.averageSoc_perc[0],(cp_pTableSoc_before.averageSoc_perc[0]<0?0:(cp_pTableSoc_before.averageSoc_perc[0]>100?100:cp_pTableSoc_before.averageSoc_perc[0])));
    PST_EQ(cp_pTableSoc.minimumSoc_perc[0],(cp_pTableSoc_before.minimumSoc_perc[0]<0?0:(cp_pTableSoc_before.minimumSoc_perc[0]>100?100:cp_pTableSoc_before.minimumSoc_perc[0])));
    PST_EQ(cp_pTableSoc.maximumSoc_perc[0],(cp_pTableSoc_before.maximumSoc_perc[0]<0?0:(cp_pTableSoc_before.maximumSoc_perc[0]>100?100:cp_pTableSoc_before.maximumSoc_perc[0])));
    PST_EQ(cp_pTableSoc.chargeThroughput_As[0],cp_pTableSoc_before.chargeThroughput_As[0]);
    PST_EQ(cp_pTableSoc.dischargeThroughput_As[0],cp_pTableSoc_before.dischargeThroughput_As[0]);
}

/* F2-LLR-ALG-008-TC-02-08: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_counting_soc_counting,F2_LLR_ALG_008_TC_02_08) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    DATA_BLOCK_SOC_s cp_pTableSoc = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    memset(&fram_soc,0,sizeof(fram_soc));
    cp_pTableSoc.averageSoc_perc[0] = 0.0f;
    cp_pTableSoc.minimumSoc_perc[0] = 0.0f;
    cp_pTableSoc.maximumSoc_perc[0] = 101.0f;
    DATA_BLOCK_SOC_s cp_pTableSoc_before=cp_pTableSoc;
    SOC_CheckDatabaseSocPercentageLimits(&cp_pTableSoc,0u);
    PST_EQ(cp_pTableSoc.maximumSoc_perc[0u],100.0f);
    PST_EQ(cp_pTableSoc.averageSoc_perc[0],(cp_pTableSoc_before.averageSoc_perc[0]<0?0:(cp_pTableSoc_before.averageSoc_perc[0]>100?100:cp_pTableSoc_before.averageSoc_perc[0])));
    PST_EQ(cp_pTableSoc.minimumSoc_perc[0],(cp_pTableSoc_before.minimumSoc_perc[0]<0?0:(cp_pTableSoc_before.minimumSoc_perc[0]>100?100:cp_pTableSoc_before.minimumSoc_perc[0])));
    PST_EQ(cp_pTableSoc.maximumSoc_perc[0],(cp_pTableSoc_before.maximumSoc_perc[0]<0?0:(cp_pTableSoc_before.maximumSoc_perc[0]>100?100:cp_pTableSoc_before.maximumSoc_perc[0])));
    PST_EQ(cp_pTableSoc.chargeThroughput_As[0],cp_pTableSoc_before.chargeThroughput_As[0]);
    PST_EQ(cp_pTableSoc.dischargeThroughput_As[0],cp_pTableSoc_before.dischargeThroughput_As[0]);
}

/* F2-LLR-ALG-008-TC-02-09: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_counting_soc_counting,F2_LLR_ALG_008_TC_02_09) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    DATA_BLOCK_SOC_s cp_pTableSoc = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    memset(&fram_soc,0,sizeof(fram_soc));
    cp_pTableSoc.averageSoc_perc[0] = 0.0f;
    cp_pTableSoc.minimumSoc_perc[0] = 0.0f;
    cp_pTableSoc.maximumSoc_perc[0] = -1.0f;
    DATA_BLOCK_SOC_s cp_pTableSoc_before=cp_pTableSoc;
    SOC_CheckDatabaseSocPercentageLimits(&cp_pTableSoc,0u);
    PST_EQ(cp_pTableSoc.maximumSoc_perc[0u],0.0f);
    PST_EQ(cp_pTableSoc.averageSoc_perc[0],(cp_pTableSoc_before.averageSoc_perc[0]<0?0:(cp_pTableSoc_before.averageSoc_perc[0]>100?100:cp_pTableSoc_before.averageSoc_perc[0])));
    PST_EQ(cp_pTableSoc.minimumSoc_perc[0],(cp_pTableSoc_before.minimumSoc_perc[0]<0?0:(cp_pTableSoc_before.minimumSoc_perc[0]>100?100:cp_pTableSoc_before.minimumSoc_perc[0])));
    PST_EQ(cp_pTableSoc.maximumSoc_perc[0],(cp_pTableSoc_before.maximumSoc_perc[0]<0?0:(cp_pTableSoc_before.maximumSoc_perc[0]>100?100:cp_pTableSoc_before.maximumSoc_perc[0])));
    PST_EQ(cp_pTableSoc.chargeThroughput_As[0],cp_pTableSoc_before.chargeThroughput_As[0]);
    PST_EQ(cp_pTableSoc.dischargeThroughput_As[0],cp_pTableSoc_before.dischargeThroughput_As[0]);
}

/* F2-LLR-ALG-008-TC-03-01: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_counting_soc_counting,F2_LLR_ALG_008_TC_03_01) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    DATA_BLOCK_SOC_s cp_pTableSoc = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    memset(&fram_soc,0,sizeof(fram_soc));
    PST_EXPECT_SUT_ASSERT(SOC_UpdateNvmValues(&cp_pTableSoc,1u),245);
}

/* F2-LLR-ALG-008-TC-03-02: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_counting_soc_counting,F2_LLR_ALG_008_TC_03_02) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    memset(&fram_soc,0,sizeof(fram_soc));
    PST_EXPECT_SUT_ASSERT(SOC_UpdateNvmValues(NULL,0u),244);
}

/* F2-LLR-ALG-008-TC-03-03: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_counting_soc_counting,F2_LLR_ALG_008_TC_03_03) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    DATA_BLOCK_SOC_s cp_pTableSoc = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    memset(&fram_soc,0,sizeof(fram_soc));
    SOC_UpdateNvmValues(&cp_pTableSoc,0u);
    PST_EQ(fram_soc.averageSoc_perc[0],cp_pTableSoc.averageSoc_perc[0]);
    PST_EQ(fram_soc.minimumSoc_perc[0],cp_pTableSoc.minimumSoc_perc[0]);
    PST_EQ(fram_soc.maximumSoc_perc[0],cp_pTableSoc.maximumSoc_perc[0]);
    PST_EQ(fram_soc.chargeThroughput_As[0],cp_pTableSoc.chargeThroughput_As[0]);
    PST_EQ(fram_soc.dischargeThroughput_As[0],cp_pTableSoc.dischargeThroughput_As[0]);
}

/* F2-LLR-ALG-008-TC-03-04: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_counting_soc_counting,F2_LLR_ALG_008_TC_03_04) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    DATA_BLOCK_SOC_s cp_pTableSoc = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    memset(&fram_soc,0,sizeof(fram_soc));
    cp_pTableSoc.averageSoc_perc[0] = 1.0f;
    SOC_UpdateNvmValues(&cp_pTableSoc,0u);
    PST_EQ(fram_soc.averageSoc_perc[0u],1.0f);
    PST_EQ(fram_soc.averageSoc_perc[0],cp_pTableSoc.averageSoc_perc[0]);
    PST_EQ(fram_soc.minimumSoc_perc[0],cp_pTableSoc.minimumSoc_perc[0]);
    PST_EQ(fram_soc.maximumSoc_perc[0],cp_pTableSoc.maximumSoc_perc[0]);
    PST_EQ(fram_soc.chargeThroughput_As[0],cp_pTableSoc.chargeThroughput_As[0]);
    PST_EQ(fram_soc.dischargeThroughput_As[0],cp_pTableSoc.dischargeThroughput_As[0]);
}

/* F2-LLR-ALG-008-TC-03-05: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_counting_soc_counting,F2_LLR_ALG_008_TC_03_05) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    DATA_BLOCK_SOC_s cp_pTableSoc = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    memset(&fram_soc,0,sizeof(fram_soc));
    cp_pTableSoc.averageSoc_perc[0] = 1.0f;
    fram_soc.averageSoc_perc[0] = 1.0f;
    cp_pTableSoc.minimumSoc_perc[0] = 1.0f;
    SOC_UpdateNvmValues(&cp_pTableSoc,0u);
    PST_EQ(fram_soc.minimumSoc_perc[0u],1.0f);
    PST_EQ(fram_soc.averageSoc_perc[0],cp_pTableSoc.averageSoc_perc[0]);
    PST_EQ(fram_soc.minimumSoc_perc[0],cp_pTableSoc.minimumSoc_perc[0]);
    PST_EQ(fram_soc.maximumSoc_perc[0],cp_pTableSoc.maximumSoc_perc[0]);
    PST_EQ(fram_soc.chargeThroughput_As[0],cp_pTableSoc.chargeThroughput_As[0]);
    PST_EQ(fram_soc.dischargeThroughput_As[0],cp_pTableSoc.dischargeThroughput_As[0]);
}

/* F2-LLR-ALG-008-TC-03-06: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_counting_soc_counting,F2_LLR_ALG_008_TC_03_06) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    DATA_BLOCK_SOC_s cp_pTableSoc = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    memset(&fram_soc,0,sizeof(fram_soc));
    cp_pTableSoc.averageSoc_perc[0] = 1.0f;
    fram_soc.averageSoc_perc[0] = 1.0f;
    cp_pTableSoc.minimumSoc_perc[0] = 1.0f;
    fram_soc.minimumSoc_perc[0] = 1.0f;
    cp_pTableSoc.maximumSoc_perc[0] = 1.0f;
    SOC_UpdateNvmValues(&cp_pTableSoc,0u);
    PST_EQ(fram_soc.maximumSoc_perc[0u],1.0f);
    PST_EQ(fram_soc.averageSoc_perc[0],cp_pTableSoc.averageSoc_perc[0]);
    PST_EQ(fram_soc.minimumSoc_perc[0],cp_pTableSoc.minimumSoc_perc[0]);
    PST_EQ(fram_soc.maximumSoc_perc[0],cp_pTableSoc.maximumSoc_perc[0]);
    PST_EQ(fram_soc.chargeThroughput_As[0],cp_pTableSoc.chargeThroughput_As[0]);
    PST_EQ(fram_soc.dischargeThroughput_As[0],cp_pTableSoc.dischargeThroughput_As[0]);
}

/* F2-LLR-ALG-008-TC-03-07: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_counting_soc_counting,F2_LLR_ALG_008_TC_03_07) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    DATA_BLOCK_SOC_s cp_pTableSoc = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    memset(&fram_soc,0,sizeof(fram_soc));
    cp_pTableSoc.averageSoc_perc[0] = 1.0f;
    fram_soc.averageSoc_perc[0] = 1.0f;
    cp_pTableSoc.minimumSoc_perc[0] = 1.0f;
    fram_soc.minimumSoc_perc[0] = 1.0f;
    cp_pTableSoc.maximumSoc_perc[0] = 1.0f;
    fram_soc.maximumSoc_perc[0] = 1.0f;
    cp_pTableSoc.chargeThroughput_As[0] = 1.0f;
    SOC_UpdateNvmValues(&cp_pTableSoc,0u);
    PST_EQ(fram_soc.chargeThroughput_As[0u],1.0f);
    PST_EQ(fram_soc.averageSoc_perc[0],cp_pTableSoc.averageSoc_perc[0]);
    PST_EQ(fram_soc.minimumSoc_perc[0],cp_pTableSoc.minimumSoc_perc[0]);
    PST_EQ(fram_soc.maximumSoc_perc[0],cp_pTableSoc.maximumSoc_perc[0]);
    PST_EQ(fram_soc.chargeThroughput_As[0],cp_pTableSoc.chargeThroughput_As[0]);
    PST_EQ(fram_soc.dischargeThroughput_As[0],cp_pTableSoc.dischargeThroughput_As[0]);
}

/* F2-LLR-ALG-008-TC-03-08: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_counting_soc_counting,F2_LLR_ALG_008_TC_03_08) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    DATA_BLOCK_SOC_s cp_pTableSoc = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    memset(&fram_soc,0,sizeof(fram_soc));
    cp_pTableSoc.averageSoc_perc[0] = 1.0f;
    fram_soc.averageSoc_perc[0] = 1.0f;
    cp_pTableSoc.minimumSoc_perc[0] = 1.0f;
    fram_soc.minimumSoc_perc[0] = 1.0f;
    cp_pTableSoc.maximumSoc_perc[0] = 1.0f;
    fram_soc.maximumSoc_perc[0] = 1.0f;
    cp_pTableSoc.chargeThroughput_As[0] = 1.0f;
    fram_soc.chargeThroughput_As[0] = 1.0f;
    cp_pTableSoc.dischargeThroughput_As[0] = 1.0f;
    SOC_UpdateNvmValues(&cp_pTableSoc,0u);
    PST_EQ(fram_soc.dischargeThroughput_As[0u],1.0f);
    PST_EQ(fram_soc.averageSoc_perc[0],cp_pTableSoc.averageSoc_perc[0]);
    PST_EQ(fram_soc.minimumSoc_perc[0],cp_pTableSoc.minimumSoc_perc[0]);
    PST_EQ(fram_soc.maximumSoc_perc[0],cp_pTableSoc.maximumSoc_perc[0]);
    PST_EQ(fram_soc.chargeThroughput_As[0],cp_pTableSoc.chargeThroughput_As[0]);
    PST_EQ(fram_soc.dischargeThroughput_As[0],cp_pTableSoc.dischargeThroughput_As[0]);
}

/* F2-LLR-ALG-008-06-ADD-001: 50 - (1000/SOC_STRING_CAPACITY_mAs)*100; discharge1As */
PST_TEST(algorithm_state_estimation_soc_counting_soc_counting,F2_LLR_ALG_008_06_ADD_001) {

pst_reset_contract();memset(&soc_state,0,sizeof(soc_state));soc_state.socInitialized=true;memset(&fram_soc,0,sizeof(fram_soc));
extern DATA_BLOCK_CURRENT_s pst_current;memset(&pst_current,0,sizeof(pst_current));pst_current.timestamp[0]=1000;pst_current.current_mA[0]=1000;pst_direction=BMS_DISCHARGING;
DATA_BLOCK_SOC_s s={0};s.averageSoc_perc[0]=s.minimumSoc_perc[0]=s.maximumSoc_perc[0]=50;
float_t expected=50-(1000.0f/SOC_STRING_CAPACITY_mAs)*100.0f*BS_CURRENT_DIRECTION_FLOAT;
SE_CalculateStateOfCharge(&s);PST_EQ(s.averageSoc_perc[0],expected);PST_EQ(s.minimumSoc_perc[0],expected);PST_EQ(s.maximumSoc_perc[0],expected);PST_EQ(s.dischargeThroughput_As[0],1.0f);PST_EQ(fram_soc.dischargeThroughput_As[0],1.0f);
}

/* F2-LLR-ALG-008-05-ADD-001: restored five fields;initialized;current timestamp10 */
PST_TEST(algorithm_state_estimation_soc_counting_soc_counting,F2_LLR_ALG_008_05_ADD_001) {
pst_reset_contract();memset(&soc_state,0,sizeof(soc_state));memset(&fram_soc,0,sizeof(fram_soc));fram_soc.averageSoc_perc[0]=25;fram_soc.minimumSoc_perc[0]=20;fram_soc.maximumSoc_perc[0]=30;fram_soc.chargeThroughput_As[0]=2;fram_soc.dischargeThroughput_As[0]=3;extern DATA_BLOCK_CURRENT_s pst_current;memset(&pst_current,0,sizeof(pst_current));pst_current.timestamp[0]=10;DATA_BLOCK_SOC_s s={0};SE_InitializeStateOfCharge(&s,false,0);PST_EQ(s.averageSoc_perc[0],25);PST_EQ(s.minimumSoc_perc[0],20);PST_EQ(s.maximumSoc_perc[0],30);PST_EQ(s.chargeThroughput_As[0],2);PST_EQ(s.dischargeThroughput_As[0],3);PST_EQ(soc_state.socInitialized,true);PST_EQ(soc_state.previousTimestamp[0],10);
}
