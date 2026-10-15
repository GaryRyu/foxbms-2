/* Requirements-based PSTUnit tests for unchanged production redundancy.c.
 * Generated from the approved plan. Each PST_TEST is an independent scenario.
 * Expected production asserts are observed; normative failures remain failures.
 */
#include "pstunit.h"
#include "stub_contract.h"
#include <string.h>
#include "../../../../src/app/application/redundancy/redundancy.c"
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
PST_SUITE(redundancy);

/* A fallback100, B sensor200 despite B fallback250; requirements [23, 29]. */
PST_TEST(redundancy,ADD_MULTI_power_independence_A0) {
reset_all();
power_inputs(1000,0,5000,50000,0,0,1);input_power.invalidMeasurement[0]=1;mrc_tablePackValues.stringCurrent_mA[0]=2000;MRC_ValidatePowerMeasurement(&input_power);EQ(mrc_tablePackValues.stringPower_W[0],100);EQ(mrc_tablePackValues.stringPower_W[1],200);EQ(mrc_tablePackValues.packPower_W,300);EQ(mrc_tablePackValues.invalidPackPower,0);
}

/* A fallback100, B sensor200 despite B fallback250; requirements [23, 29]. */
PST_TEST(redundancy,ADD_MULTI_power_independence_A1) {
reset_all();
power_inputs(1000,0,5000,50000,0,0,1);input_power.invalidMeasurement[1]=1;mrc_tablePackValues.stringCurrent_mA[1]=2000;MRC_ValidatePowerMeasurement(&input_power);EQ(mrc_tablePackValues.stringPower_W[1],100);EQ(mrc_tablePackValues.stringPower_W[0],200);EQ(mrc_tablePackValues.packPower_W,300);EQ(mrc_tablePackValues.invalidPackPower,0);
}

/* Valid-only sum independent of connection; requirements [21]. */
PST_TEST(redundancy,ADD_MULTI_current_validity_00) {
reset_all();
for(unsigned s=0;s<2;s++){input_current.timestamp[s]=1000;input_current.current_mA[s]=(s+1)*100;}input_current.invalidMeasurement[0]=0;input_current.invalidMeasurement[1]=0;MRC_ValidateCurrentMeasurement(&input_current);EQ(mrc_tablePackValues.packCurrent_mA,300);EQ(mrc_tablePackValues.invalidPackCurrent,0);
}

/* Valid-only sum independent of connection; requirements [23]. */
PST_TEST(redundancy,ADD_MULTI_power_validity_00) {
reset_all();
for(unsigned s=0;s<2;s++){input_power.timestamp[s]=1000;input_power.power_W[s]=(s+1)*100;}input_power.invalidMeasurement[0]=0;input_power.invalidMeasurement[1]=0;for(unsigned s=0;s<2;s++){mrc_tablePackValues.invalidStringPower[s]=1;mrc_tablePackValues.invalidStringCurrent[s]=1;}MRC_ValidatePowerMeasurement(&input_power);EQ(mrc_tablePackValues.packPower_W,300);EQ(mrc_tablePackValues.invalidPackPower,0);
}

/* Valid-only sum independent of connection; requirements [21]. */
PST_TEST(redundancy,ADD_MULTI_current_validity_10) {
reset_all();
for(unsigned s=0;s<2;s++){input_current.timestamp[s]=1000;input_current.current_mA[s]=(s+1)*100;}input_current.invalidMeasurement[0]=1;input_current.invalidMeasurement[1]=0;MRC_ValidateCurrentMeasurement(&input_current);EQ(mrc_tablePackValues.packCurrent_mA,200);EQ(mrc_tablePackValues.invalidPackCurrent,1);
}

/* Valid-only sum independent of connection; requirements [23]. */
PST_TEST(redundancy,ADD_MULTI_power_validity_10) {
reset_all();
for(unsigned s=0;s<2;s++){input_power.timestamp[s]=1000;input_power.power_W[s]=(s+1)*100;}input_power.invalidMeasurement[0]=1;input_power.invalidMeasurement[1]=0;for(unsigned s=0;s<2;s++){mrc_tablePackValues.invalidStringPower[s]=1;mrc_tablePackValues.invalidStringCurrent[s]=1;}MRC_ValidatePowerMeasurement(&input_power);EQ(mrc_tablePackValues.packPower_W,200);EQ(mrc_tablePackValues.invalidPackPower,1);
}

/* Valid-only sum independent of connection; requirements [21]. */
PST_TEST(redundancy,ADD_MULTI_current_validity_01) {
reset_all();
for(unsigned s=0;s<2;s++){input_current.timestamp[s]=1000;input_current.current_mA[s]=(s+1)*100;}input_current.invalidMeasurement[0]=0;input_current.invalidMeasurement[1]=1;MRC_ValidateCurrentMeasurement(&input_current);EQ(mrc_tablePackValues.packCurrent_mA,100);EQ(mrc_tablePackValues.invalidPackCurrent,1);
}

/* Valid-only sum independent of connection; requirements [23]. */
PST_TEST(redundancy,ADD_MULTI_power_validity_01) {
reset_all();
for(unsigned s=0;s<2;s++){input_power.timestamp[s]=1000;input_power.power_W[s]=(s+1)*100;}input_power.invalidMeasurement[0]=0;input_power.invalidMeasurement[1]=1;for(unsigned s=0;s<2;s++){mrc_tablePackValues.invalidStringPower[s]=1;mrc_tablePackValues.invalidStringCurrent[s]=1;}MRC_ValidatePowerMeasurement(&input_power);EQ(mrc_tablePackValues.packPower_W,100);EQ(mrc_tablePackValues.invalidPackPower,1);
}

/* Valid-only sum independent of connection; requirements [21]. */
PST_TEST(redundancy,ADD_MULTI_current_validity_11) {
reset_all();
for(unsigned s=0;s<2;s++){input_current.timestamp[s]=1000;input_current.current_mA[s]=(s+1)*100;}input_current.invalidMeasurement[0]=1;input_current.invalidMeasurement[1]=1;MRC_ValidateCurrentMeasurement(&input_current);EQ(mrc_tablePackValues.packCurrent_mA,0);EQ(mrc_tablePackValues.invalidPackCurrent,1);
}

/* Valid-only sum independent of connection; requirements [23]. */
PST_TEST(redundancy,ADD_MULTI_power_validity_11) {
reset_all();
for(unsigned s=0;s<2;s++){input_power.timestamp[s]=1000;input_power.power_W[s]=(s+1)*100;}input_power.invalidMeasurement[0]=1;input_power.invalidMeasurement[1]=1;for(unsigned s=0;s<2;s++){mrc_tablePackValues.invalidStringPower[s]=1;mrc_tablePackValues.invalidStringCurrent[s]=1;}MRC_ValidatePowerMeasurement(&input_power);EQ(mrc_tablePackValues.packPower_W,0);EQ(mrc_tablePackValues.invalidPackPower,1);
}

/* Two-string connected valid-only averaging; requirements [18]. */
PST_TEST(redundancy,ADD_MULTI_battery_average) {
reset_all();
mrc_tablePackValues.stringVoltage_mV[0]=50000;mrc_tablePackValues.stringVoltage_mV[1]=50001;closed[0]=0;closed[1]=0;mrc_tablePackValues.invalidStringVoltage[0]=0;mrc_tablePackValues.invalidStringVoltage[1]=0;MRC_ValidateBatteryVoltageMeasurement();EQ(mrc_tablePackValues.batteryVoltage_mV,50000);EQ(mrc_tablePackValues.invalidBatteryVoltage,0);
}

/* Two-string connected valid-only averaging; requirements [18]. */
PST_TEST(redundancy,ADD_MULTI_battery_connected_only) {
reset_all();
mrc_tablePackValues.stringVoltage_mV[0]=50000;mrc_tablePackValues.stringVoltage_mV[1]=50001;closed[0]=1;closed[1]=0;mrc_tablePackValues.invalidStringVoltage[0]=0;mrc_tablePackValues.invalidStringVoltage[1]=0;MRC_ValidateBatteryVoltageMeasurement();EQ(mrc_tablePackValues.batteryVoltage_mV,50000);EQ(mrc_tablePackValues.invalidBatteryVoltage,0);
}

/* Two-string connected valid-only averaging; requirements [18]. */
PST_TEST(redundancy,ADD_MULTI_battery_connected_invalid) {
reset_all();
mrc_tablePackValues.stringVoltage_mV[0]=50000;mrc_tablePackValues.stringVoltage_mV[1]=50001;closed[0]=1;closed[1]=0;mrc_tablePackValues.invalidStringVoltage[0]=1;mrc_tablePackValues.invalidStringVoltage[1]=0;MRC_ValidateBatteryVoltageMeasurement();EQ(mrc_tablePackValues.batteryVoltage_mV,INT32_MAX);EQ(mrc_tablePackValues.invalidBatteryVoltage,1);
}

/* Two-string connected valid-only averaging; requirements [18]. */
PST_TEST(redundancy,ADD_MULTI_battery_all_invalid) {
reset_all();
mrc_tablePackValues.stringVoltage_mV[0]=50000;mrc_tablePackValues.stringVoltage_mV[1]=50001;closed[0]=0;closed[1]=0;mrc_tablePackValues.invalidStringVoltage[0]=1;mrc_tablePackValues.invalidStringVoltage[1]=1;MRC_ValidateBatteryVoltageMeasurement();EQ(mrc_tablePackValues.batteryVoltage_mV,INT32_MAX);EQ(mrc_tablePackValues.invalidBatteryVoltage,1);
}

/* Two-string closed and precharging average truncates; requirements [19]. */
PST_TEST(redundancy,ADD_MULTI_hv_average) {
reset_all();
closed[0]=1;precharging[1]=1;input_v3.timestamp[0]=input_v3.timestamp[1]=1000;input_v3.highVoltage_mV[0]=50000;input_v3.highVoltage_mV[1]=50001;MRC_ValidateHighVoltageBusMeasurement(&input_v3);EQ(mrc_tablePackValues.highVoltageBusVoltage_mV,50000);EQ(mrc_tablePackValues.invalidHvBusVoltage,0);
}
