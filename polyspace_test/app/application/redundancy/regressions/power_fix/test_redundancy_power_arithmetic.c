/* Requirements-based PSTUnit tests for unchanged production redundancy.c.
 * Generated from the approved plan. Each PST_TEST is an independent scenario.
 * Expected production asserts are observed; normative failures remain failures.
 */
#include "pstunit.h"
#include "stub_contract.h"
#include <string.h>
#include "../../../../../../src/app/application/redundancy/redundancy.c"
#define EQ(a,b) PST_VERIFY_EQ_INT((int64_t)(a),(int64_t)(b))
#define EVENT(id,e,impact,s) PST_VERIFY_TRUE(event_is(id,e,impact,s))
#define EXPECT_ASSERT(call,line) do { assert_expected=1; if(setjmp(assert_jump)==0) { (void)(call);PST_VERIFY_TRUE_MSG(0,"Expected SUT assert did not occur"); } else {EQ(assert_line,line);} assert_expected=0; } while(0)
static void reset_all(void) {
 reset_stubs();memset(&mrc_state,0,sizeof(mrc_state));
 memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
 memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
 memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
 memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;
}
static void fill_voltage(DATA_BLOCK_CELL_VOLTAGE_s *p,int value) {
 for(unsigned s=0;s<BS_NR_OF_STRINGS;s++) {p->nrValidCellVoltages[s]=BS_NR_OF_CELL_BLOCKS_PER_STRING;p->stringVoltage_mV[s]=value*BS_NR_OF_CELL_BLOCKS_PER_STRING;
 for(unsigned m=0;m<BS_NR_OF_MODULES_PER_STRING;m++) for(unsigned c=0;c<BS_NR_OF_CELL_BLOCKS_PER_MODULE;c++){p->cellVoltage_mV[s][m][c]=value;p->invalidCellVoltage[s][m][c]=0;}}
}
static void fill_temperature(DATA_BLOCK_CELL_TEMPERATURE_s *p,int value) {
 for(unsigned s=0;s<BS_NR_OF_STRINGS;s++) {p->nrValidTemperatures[s]=BS_NR_OF_TEMP_SENSORS_PER_STRING;
 for(unsigned m=0;m<BS_NR_OF_MODULES_PER_STRING;m++) for(unsigned t=0;t<BS_NR_OF_TEMP_SENSORS_PER_MODULE;t++){p->cellTemperature_ddegC[s][m][t]=value;p->invalidCellTemperature[s][m][t]=0;}}
}
static void check_final_temperature_count(void) {
 for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){unsigned n=0;for(unsigned m=0;m<BS_NR_OF_MODULES_PER_STRING;m++)for(unsigned t=0;t<BS_NR_OF_TEMP_SENSORS_PER_MODULE;t++)n+=!mrc_tableCellTemperatures.invalidCellTemperature[s][m][t];
 EQ(mrc_tableCellTemperatures.nrValidTemperatures[s],n);EQ(mrc_tableMinimumMaximumValues.validMeasuredCellTemperatures[s],n);PST_VERIFY_LE_UINT(mrc_tableCellTemperatures.nrValidTemperatures[s],BS_NR_OF_TEMP_SENSORS_PER_STRING);}
}
static void power_inputs(unsigned timestamp,unsigned invalid,int current,int voltage,unsigned invalidCurrent,unsigned invalidVoltage,unsigned oldInvalid) {
 for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){input_power.timestamp[s]=timestamp;input_power.invalidMeasurement[s]=invalid;input_power.power_W[s]=200;mrc_tablePackValues.stringPower_W[s]=100;mrc_tablePackValues.invalidStringPower[s]=oldInvalid;mrc_tablePackValues.stringCurrent_mA[s]=current;mrc_tablePackValues.stringVoltage_mV[s]=voltage;mrc_tablePackValues.invalidStringCurrent[s]=invalidCurrent;mrc_tablePackValues.invalidStringVoltage[s]=invalidVoltage;}
}
PST_SUITE(power_fix);
/* positive: validate arithmetic, validity and pack exclusion. */
PST_TEST(power_fix,positive) {
 reset_all();
 power_inputs(1000,1,2400,90000,0,0,0);
 MRC_ValidatePowerMeasurement(&input_power);
 EQ(mrc_tablePackValues.stringPower_W[0],216);
 EQ(mrc_tablePackValues.invalidStringPower[0],0);
 EQ(mrc_tablePackValues.invalidPackPower,0);
 EQ(mrc_tablePackValues.packPower_W,216);
}
/* negative: validate arithmetic, validity and pack exclusion. */
PST_TEST(power_fix,negative) {
 reset_all();
 power_inputs(1000,1,-2400,90000,0,0,0);
 MRC_ValidatePowerMeasurement(&input_power);
 EQ(mrc_tablePackValues.stringPower_W[0],-216);
 EQ(mrc_tablePackValues.invalidStringPower[0],0);
 EQ(mrc_tablePackValues.invalidPackPower,0);
 EQ(mrc_tablePackValues.packPower_W,-216);
}
/* zero: validate arithmetic, validity and pack exclusion. */
PST_TEST(power_fix,zero) {
 reset_all();
 power_inputs(1000,1,0,2147483647,0,0,0);
 MRC_ValidatePowerMeasurement(&input_power);
 EQ(mrc_tablePackValues.stringPower_W[0],0);
 EQ(mrc_tablePackValues.invalidStringPower[0],0);
 EQ(mrc_tablePackValues.invalidPackPower,0);
 EQ(mrc_tablePackValues.packPower_W,0);
}
/* truncate_positive: validate arithmetic, validity and pack exclusion. */
PST_TEST(power_fix,truncate_positive) {
 reset_all();
 power_inputs(1000,1,1999,1000,0,0,0);
 MRC_ValidatePowerMeasurement(&input_power);
 EQ(mrc_tablePackValues.stringPower_W[0],1);
 EQ(mrc_tablePackValues.invalidStringPower[0],0);
 EQ(mrc_tablePackValues.invalidPackPower,0);
 EQ(mrc_tablePackValues.packPower_W,1);
}
/* truncate_negative: validate arithmetic, validity and pack exclusion. */
PST_TEST(power_fix,truncate_negative) {
 reset_all();
 power_inputs(1000,1,-1999,1000,0,0,0);
 MRC_ValidatePowerMeasurement(&input_power);
 EQ(mrc_tablePackValues.stringPower_W[0],-1);
 EQ(mrc_tablePackValues.invalidStringPower[0],0);
 EQ(mrc_tablePackValues.invalidPackPower,0);
 EQ(mrc_tablePackValues.packPower_W,-1);
}
/* max_exact: validate arithmetic, validity and pack exclusion. */
PST_TEST(power_fix,max_exact) {
 reset_all();
 power_inputs(1000,1,2147483647,1000000,0,0,0);
 MRC_ValidatePowerMeasurement(&input_power);
 EQ(mrc_tablePackValues.stringPower_W[0],2147483647);
 EQ(mrc_tablePackValues.invalidStringPower[0],0);
 EQ(mrc_tablePackValues.invalidPackPower,0);
 EQ(mrc_tablePackValues.packPower_W,2147483647);
}
/* min_exact: validate arithmetic, validity and pack exclusion. */
PST_TEST(power_fix,min_exact) {
 reset_all();
 power_inputs(1000,1,-2147483648,1000000,0,0,0);
 MRC_ValidatePowerMeasurement(&input_power);
 EQ(mrc_tablePackValues.stringPower_W[0],-2147483648);
 EQ(mrc_tablePackValues.invalidStringPower[0],0);
 EQ(mrc_tablePackValues.invalidPackPower,0);
 EQ(mrc_tablePackValues.packPower_W,-2147483648);
}
/* positive_overflow: validate arithmetic, validity and pack exclusion. */
PST_TEST(power_fix,positive_overflow) {
 reset_all();
 power_inputs(1000,1,2147483647,1000001,0,0,0);
 MRC_ValidatePowerMeasurement(&input_power);
 EQ(mrc_tablePackValues.stringPower_W[0],100);
 EQ(mrc_tablePackValues.invalidStringPower[0],1);
 EQ(mrc_tablePackValues.invalidPackPower,1);
 EQ(mrc_tablePackValues.packPower_W,0);
}
/* negative_overflow: validate arithmetic, validity and pack exclusion. */
PST_TEST(power_fix,negative_overflow) {
 reset_all();
 power_inputs(1000,1,-2147483648,1000001,0,0,0);
 MRC_ValidatePowerMeasurement(&input_power);
 EQ(mrc_tablePackValues.stringPower_W[0],100);
 EQ(mrc_tablePackValues.invalidStringPower[0],1);
 EQ(mrc_tablePackValues.invalidPackPower,1);
 EQ(mrc_tablePackValues.packPower_W,0);
}
/* full_positive: validate arithmetic, validity and pack exclusion. */
PST_TEST(power_fix,full_positive) {
 reset_all();
 power_inputs(1000,1,-2147483648,-2147483648,0,0,0);
 MRC_ValidatePowerMeasurement(&input_power);
 EQ(mrc_tablePackValues.stringPower_W[0],100);
 EQ(mrc_tablePackValues.invalidStringPower[0],1);
 EQ(mrc_tablePackValues.invalidPackPower,1);
 EQ(mrc_tablePackValues.packPower_W,0);
}
/* full_negative: validate arithmetic, validity and pack exclusion. */
PST_TEST(power_fix,full_negative) {
 reset_all();
 power_inputs(1000,1,-2147483648,2147483647,0,0,0);
 MRC_ValidatePowerMeasurement(&input_power);
 EQ(mrc_tablePackValues.stringPower_W[0],100);
 EQ(mrc_tablePackValues.invalidStringPower[0],1);
 EQ(mrc_tablePackValues.invalidPackPower,1);
 EQ(mrc_tablePackValues.packPower_W,0);
}
/* voltage_negative: validate arithmetic, validity and pack exclusion. */
PST_TEST(power_fix,voltage_negative) {
 reset_all();
 power_inputs(1000,1,2400,-90000,0,0,0);
 MRC_ValidatePowerMeasurement(&input_power);
 EQ(mrc_tablePackValues.stringPower_W[0],-216);
 EQ(mrc_tablePackValues.invalidStringPower[0],0);
 EQ(mrc_tablePackValues.invalidPackPower,0);
 EQ(mrc_tablePackValues.packPower_W,-216);
}
/* both_negative: validate arithmetic, validity and pack exclusion. */
PST_TEST(power_fix,both_negative) {
 reset_all();
 power_inputs(1000,1,-2400,-90000,0,0,0);
 MRC_ValidatePowerMeasurement(&input_power);
 EQ(mrc_tablePackValues.stringPower_W[0],216);
 EQ(mrc_tablePackValues.invalidStringPower[0],0);
 EQ(mrc_tablePackValues.invalidPackPower,0);
 EQ(mrc_tablePackValues.packPower_W,216);
}
