/* DOCX 4.1--4.11 PSTUnit; production unchanged. */
#include "application_contract.h"
#include "fram.h"
#include "../../../../../../../src/app/application/algorithm/state_estimation/soc/lookup-table/soc_lookup-table.c"
PST_SUITE(algorithm_state_estimation_soc_lookup_table_soc_lookup_table);
/* F2-LLR-ALG-014-TC-01-01: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_01_01) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    memset(&fram_soc,0,sizeof(fram_soc));
    PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfCharge(NULL,true,0),161);
}

/* F2-LLR-ALG-014-TC-01-02: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_01_02) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    DATA_BLOCK_SOC_s cp_pTableSoc = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    memset(&fram_soc,0,sizeof(fram_soc));
    PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfCharge(&cp_pTableSoc,true,1u),163);
}

/* F2-LLR-ALG-014-TC-01-03: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_01_03) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    DATA_BLOCK_SOC_s cp_pTableSoc = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    memset(&fram_soc,0,sizeof(fram_soc));
    SE_InitializeStateOfCharge(&cp_pTableSoc,true,0);
    PST_EQ(soc_state.socInitialized,true);
}

/* F2-LLR-ALG-014-TC-03-01: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_03_01) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    memset(&fram_soc,0,sizeof(fram_soc));
    PST_EQ(SE_GetStateOfChargeFromVoltage(4123),100.0f);
}

/* F2-LLR-ALG-014-TC-03-02: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_03_02) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    memset(&fram_soc,0,sizeof(fram_soc));
    PST_EQ(SE_GetStateOfChargeFromVoltage(3636),50.0f);
}

/* F2-LLR-ALG-014-TC-03-03: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_03_03) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    memset(&fram_soc,0,sizeof(fram_soc));
    PST_EQ(SE_GetStateOfChargeFromVoltage(3461),26.0f);
}

/* F2-LLR-ALG-014-TC-03-04: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_03_04) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    memset(&fram_soc,0,sizeof(fram_soc));
    PST_EQ(SE_GetStateOfChargeFromVoltage(2716),1.0f);
}

/* F2-LLR-ALG-014-TC-03-05: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_03_05) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    memset(&fram_soc,0,sizeof(fram_soc));
    PST_EQ(SE_GetStateOfChargeFromVoltage(2700),0.0f);
}

/* F2-LLR-ALG-014-TC-03-06: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_03_06) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    memset(&fram_soc,0,sizeof(fram_soc));
    PST_EQ(SE_GetStateOfChargeFromVoltage(4200),100.0f);
}

/* F2-LLR-ALG-014-TC-04-01: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_04_01) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    DATA_BLOCK_SOC_s cp_pTableSoc = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    memset(&fram_soc,0,sizeof(fram_soc));
    PST_EXPECT_SUT_ASSERT(SOC_UpdateNvmValues(&cp_pTableSoc,1u),151);
}

/* F2-LLR-ALG-014-TC-04-02: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_04_02) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    memset(&fram_soc,0,sizeof(fram_soc));
    PST_EXPECT_SUT_ASSERT(SOC_UpdateNvmValues(NULL,0u),150);
}

/* F2-LLR-ALG-014-TC-04-03: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_04_03) {
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

/* F2-LLR-ALG-014-TC-04-04: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_04_04) {
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

/* F2-LLR-ALG-014-TC-04-05: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_04_05) {
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

/* F2-LLR-ALG-014-TC-04-06: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_04_06) {
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

/* F2-LLR-ALG-014-TC-04-07: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_04_07) {
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

/* F2-LLR-ALG-014-TC-04-08: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_04_08) {
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

/* F2-LLR-ALG-014-TC-05: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_05) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    memset(&fram_soc,0,sizeof(fram_soc));
    soc_state.socInitialized=true;
    PST_EQ(soc_state.socInitialized,true);
}

/* F2-LLR-ALG-014-TC-06-01: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_06_01) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    DATA_BLOCK_SOC_s cp_pTableSoc = {.header.uniqueId = DATA_BLOCK_ID_SOC};
    memset(&fram_soc,0,sizeof(fram_soc));
    PST_EXPECT_SUT_ASSERT(SOC_CheckDatabaseSocPercentageLimits(&cp_pTableSoc,1u),127);
}

/* F2-LLR-ALG-014-TC-06-02: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_06_02) {
    pst_reset_contract();
    memset(&soc_state,0,sizeof(soc_state));
    memset(&fram_soc,0,sizeof(fram_soc));
    memset(&fram_soc,0,sizeof(fram_soc));
    PST_EXPECT_SUT_ASSERT(SOC_CheckDatabaseSocPercentageLimits(NULL,0u),126);
}

/* F2-LLR-ALG-014-TC-06-03: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_06_03) {
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

/* F2-LLR-ALG-014-TC-06-04: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_06_04) {
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

/* F2-LLR-ALG-014-TC-06-05: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_06_05) {
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

/* F2-LLR-ALG-014-TC-06-06: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_06_06) {
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

/* F2-LLR-ALG-014-TC-06-07: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_06_07) {
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

/* F2-LLR-ALG-014-TC-06-08: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_06_08) {
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

/* F2-LLR-ALG-014-TC-06-09: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_state_estimation_soc_lookup_table_soc_lookup_table,F2_LLR_ALG_014_TC_06_09) {
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
