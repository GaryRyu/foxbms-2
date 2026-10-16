#include "application_contract.h"
#include "../../../../src/app/application/redundancy/redundancy.c"
PST_SUITE(redundancy_multistring_unit);

/* F2-LLR-ALG-080-29-ADD-001: independent6/123W;Pack129W */
PST_TEST(redundancy_multistring_unit,F2_LLR_ALG_080_29_ADD_001) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));DATA_BLOCK_POWER_s p={0};p.timestamp[0]=p.timestamp[1]=1;p.invalidMeasurement[0]=1;p.invalidMeasurement[1]=0;p.power_W[1]=123;pst_tick=1;mrc_tablePackValues.stringCurrent_mA[0]=2000;mrc_tablePackValues.stringVoltage_mV[0]=3000;mrc_tablePackValues.stringCurrent_mA[1]=1000;mrc_tablePackValues.stringVoltage_mV[1]=1000;MRC_ValidatePowerMeasurement(&p);PST_EQ(mrc_tablePackValues.stringPower_W[0],6);PST_EQ(mrc_tablePackValues.stringPower_W[1],123);PST_EQ(mrc_tablePackValues.packPower_W,129);
}
