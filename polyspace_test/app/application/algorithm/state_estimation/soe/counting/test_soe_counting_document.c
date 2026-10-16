/* Requirement-based unit tests. Static source access explicitly authorized. */
#include "application_contract.h"
#include "../../../../../../../src/app/application/algorithm/state_estimation/soe/counting/soe_counting.c"
#include "fram.h"
PST_SUITE(algorithm_state_estimation_soe_counting_soe_counting);
/* F2-LLR-APP-SOE-001-01-ADD-001 */
PST_TEST(algorithm_state_estimation_soe_counting_soe_counting,F2_LLR_APP_SOE_001_01_ADD_001) {
pst_reset_contract();PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfEnergy(NULL,false,0),321);
}

/* F2-LLR-APP-SOE-001-01-ADD-002 */
PST_TEST(algorithm_state_estimation_soe_counting_soe_counting,F2_LLR_APP_SOE_001_01_ADD_002) {
pst_reset_contract();DATA_BLOCK_SOE_s s={0};PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfEnergy(&s,false,BS_NR_OF_STRINGS),322);
}

/* F2-LLR-APP-SOE-001-02-ADD-003 */
PST_TEST(algorithm_state_estimation_soe_counting_soe_counting,F2_LLR_APP_SOE_001_02_ADD_003) {
pst_reset_contract();memset(&soe_state,0,sizeof(soe_state));DATA_BLOCK_SOE_s s={0},before=s;SE_CalculateStateOfEnergy(&s);PST_EQ(memcmp(&s,&before,sizeof(s)),0);PST_EQ(pst_reads,0);
}

/* F2-LLR-APP-SOE-001-04-ADD-004 */
PST_TEST(algorithm_state_estimation_soe_counting_soe_counting,F2_LLR_APP_SOE_001_04_ADD_004) {
pst_reset_contract();DATA_BLOCK_SOE_s s={0};s.averageSoe_perc[0]=-1;s.minimumSoe_perc[0]=50;s.maximumSoe_perc[0]=101;SOE_CheckDatabaseSoePercentageLimits(&s,0);PST_EQ(s.averageSoe_perc[0],0);PST_EQ(s.minimumSoe_perc[0],50);PST_EQ(s.maximumSoe_perc[0],100);
}

/* F2-LLR-APP-SOE-001-05-ADD-005 */
PST_TEST(algorithm_state_estimation_soe_counting_soe_counting,F2_LLR_APP_SOE_001_05_ADD_005) {
pst_reset_contract();memset(&soe_state,0,sizeof(soe_state));soe_state.soeInitialized=true;
extern DATA_BLOCK_CURRENT_s pst_current;extern DATA_BLOCK_SYSTEM_VOLTAGE_1_s pst_voltage1;
memset(&pst_current,0,sizeof(pst_current));memset(&pst_voltage1,0,sizeof(pst_voltage1));pst_current.timestamp[0]=3600000;pst_current.current_mA[0]=-1000;pst_voltage1.highVoltage_mV[0]=1000;pst_direction=BMS_CHARGING;
DATA_BLOCK_SOE_s s={0};s.averageSoe_Wh[0]=s.minimumSoe_Wh[0]=s.maximumSoe_Wh[0]=10;SE_CalculateStateOfEnergy(&s);
PST_EQ(s.averageSoe_Wh[0],11);PST_EQ(s.minimumSoe_Wh[0],11);PST_EQ(s.maximumSoe_Wh[0],11);PST_EQ(s.chargeEnergyThroughput_Wh[0],1);
}

/* F2-LLR-APP-SOE-001-03-ADD-001: 9Wh;discharge1Wh */
PST_TEST(algorithm_state_estimation_soe_counting_soe_counting,F2_LLR_APP_SOE_001_03_ADD_001) {
pst_reset_contract();memset(&soe_state,0,sizeof(soe_state));soe_state.soeInitialized=true;extern DATA_BLOCK_CURRENT_s pst_current;extern DATA_BLOCK_SYSTEM_VOLTAGE_1_s pst_voltage1;memset(&pst_current,0,sizeof(pst_current));memset(&pst_voltage1,0,sizeof(pst_voltage1));pst_current.timestamp[0]=3600000;pst_current.current_mA[0]=1000;pst_voltage1.highVoltage_mV[0]=1000;pst_direction=BMS_DISCHARGING;DATA_BLOCK_SOE_s s={0};s.averageSoe_Wh[0]=s.minimumSoe_Wh[0]=s.maximumSoe_Wh[0]=10;SE_CalculateStateOfEnergy(&s);PST_EQ(s.averageSoe_Wh[0],9);PST_EQ(s.dischargeEnergyThroughput_Wh[0],1);
}
