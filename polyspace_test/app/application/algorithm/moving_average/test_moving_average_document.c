/* Requirement-based unit tests. Static source access explicitly authorized. */
#include "application_contract.h"
#include "../../../../../src/app/application/algorithm/moving_average/moving_average.c"
extern DATA_BLOCK_CURRENT_s pst_current;extern DATA_BLOCK_POWER_s pst_power;extern DATA_BLOCK_MOVING_AVERAGE_s pst_moving_average;
PST_SUITE(algorithm_moving_average_moving_average);
/* F2-LLR-ALG-007-TC-01 */
PST_TEST(algorithm_moving_average_moving_average,F2_LLR_ALG_007_TC_01) {

pst_reset_contract();memset(&pst_current,0,sizeof(pst_current));memset(&pst_power,0,sizeof(pst_power));memset(&pst_moving_average,0,sizeof(pst_moving_average));
pst_current.header.uniqueId=DATA_BLOCK_ID_CURRENT;pst_power.header.uniqueId=DATA_BLOCK_ID_POWER;pst_moving_average.header.uniqueId=DATA_BLOCK_ID_MOVING_AVERAGE;
pst_current.newCurrent=1;pst_power.newPower=1;ALGO_MovingAverage();
PST_EQ(pst_reads,3);PST_EQ(pst_writes,1);
DATA_BLOCK_MOVING_AVERAGE_s expected={.header.uniqueId=DATA_BLOCK_ID_MOVING_AVERAGE};
PST_EQ(memcmp(&pst_moving_average,&expected,sizeof(expected)),0);

}

/* F2-LLR-ALG-007-05-ADD-001: write1 */
PST_TEST(algorithm_moving_average_moving_average,F2_LLR_ALG_007_05_ADD_001) {
pst_reset_contract();memset(&pst_current,0,sizeof(pst_current));memset(&pst_power,0,sizeof(pst_power));memset(&pst_moving_average,0,sizeof(pst_moving_average));pst_current.newCurrent=pst_power.newPower=1;
pst_current.invalidMeasurement[0]=pst_power.invalidMeasurement[0]=0;ALGO_MovingAverage();PST_EQ(pst_writes,1);ALGO_MovingAverage();PST_EQ(pst_writes,1);
}

/* F2-LLR-ALG-007-05-ADD-002: write0 */
PST_TEST(algorithm_moving_average_moving_average,F2_LLR_ALG_007_05_ADD_002) {
pst_reset_contract();memset(&pst_current,0,sizeof(pst_current));memset(&pst_power,0,sizeof(pst_power));memset(&pst_moving_average,0,sizeof(pst_moving_average));pst_current.newCurrent=pst_power.newPower=1;
pst_current.invalidMeasurement[0]=pst_power.invalidMeasurement[0]=1;ALGO_MovingAverage();PST_EQ(pst_writes,0);
}
