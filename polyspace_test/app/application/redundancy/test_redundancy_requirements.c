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

/* TC_01_01: Measurement history. Requirements [4]. */
PST_TEST(redundancy,TC_01_01) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EQ(MRC_MeasurementUpdatedAtLeastOnce(10u,0u),1);
}

/* TC_01_02: Measurement history. Requirements [4]. */
PST_TEST(redundancy,TC_01_02) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EQ(MRC_MeasurementUpdatedAtLeastOnce(60u,10u),1);
}

/* TC_01_03: Measurement history. Requirements [4]. */
PST_TEST(redundancy,TC_01_03) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EQ(MRC_MeasurementUpdatedAtLeastOnce(70u,60u),1);
}

/* TC_01_04: Measurement history. Requirements [4]. */
PST_TEST(redundancy,TC_01_04) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EQ(MRC_MeasurementUpdatedAtLeastOnce(0u,0u),0);
}

/* TC_02_01: Freshness and uint32 wrap. Requirements [5]. */
PST_TEST(redundancy,TC_02_01) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
test_tick=100u; EQ(MRC_MeasurementUpdatedRecently(50u,0u,100u),0);
}

/* TC_02_02: Freshness and uint32 wrap. Requirements [5]. */
PST_TEST(redundancy,TC_02_02) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
test_tick=100u; EQ(MRC_MeasurementUpdatedRecently(0u,0u,100u),1);
}

/* TC_02_03: Freshness and uint32 wrap. Requirements [5]. */
PST_TEST(redundancy,TC_02_03) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
test_tick=101u; EQ(MRC_MeasurementUpdatedRecently(0u,0u,100u),1);
}

/* TC_02_04: Freshness and uint32 wrap. Requirements [5]. */
PST_TEST(redundancy,TC_02_04) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
test_tick=5000u; EQ(MRC_MeasurementUpdatedRecently(4937u,0u,100u),0);
}

/* TC_02_05: Freshness and uint32 wrap. Requirements [5]. */
PST_TEST(redundancy,TC_02_05) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
test_tick=50u; EQ(MRC_MeasurementUpdatedRecently(UINT32_MAX,0u,100u),0);
}

/* TC_02_06: Freshness and uint32 wrap. Requirements [5]. */
PST_TEST(redundancy,TC_02_06) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
test_tick=49u; EQ(MRC_MeasurementUpdatedRecently(UINT32_MAX-50u,0u,100u),0);
}

/* TC_02_07: Freshness and uint32 wrap. Requirements [5]. */
PST_TEST(redundancy,TC_02_07) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
test_tick=50u; EQ(MRC_MeasurementUpdatedRecently(UINT32_MAX-50u,0u,100u),1);
}

/* TC_02_08: Freshness and uint32 wrap. Requirements [5]. */
PST_TEST(redundancy,TC_02_08) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
test_tick=UINT32_MAX; EQ(MRC_MeasurementUpdatedRecently(50u,0u,100u),1);
}

/* TC_03_01: MRC_CalculateCellVoltageMinMaxAverage parameter 1 NULL assert. Requirements [26]. */
PST_TEST(redundancy,TC_03_01) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EXPECT_ASSERT(MRC_CalculateCellVoltageMinMaxAverage(NULL_PTR,&mrc_tableMinimumMaximumValues),786);
}

/* TC_03_02: MRC_CalculateCellVoltageMinMaxAverage parameter 2 NULL assert. Requirements [26]. */
PST_TEST(redundancy,TC_03_02) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EXPECT_ASSERT(MRC_CalculateCellVoltageMinMaxAverage(&input_vb,NULL_PTR),787);
}

/* TC_04_01: MRC_CalculateCellTemperatureMinMaxAverage parameter 1 NULL assert. Requirements [26]. */
PST_TEST(redundancy,TC_04_01) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EXPECT_ASSERT(MRC_CalculateCellTemperatureMinMaxAverage(NULL_PTR,&mrc_tableMinimumMaximumValues),844);
}

/* TC_04_02: MRC_CalculateCellTemperatureMinMaxAverage parameter 2 NULL assert. Requirements [26]. */
PST_TEST(redundancy,TC_04_02) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EXPECT_ASSERT(MRC_CalculateCellTemperatureMinMaxAverage(&input_tb,NULL_PTR),845);
}

/* TC_05_01: MRC_ValidateCellVoltage parameter 1 NULL assert. Requirements [26]. */
PST_TEST(redundancy,TC_05_01) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EXPECT_ASSERT(MRC_ValidateCellVoltage(NULL_PTR,&input_vb,&input_vb),903);
}

/* TC_05_02: MRC_ValidateCellVoltage parameter 2 NULL assert. Requirements [26]. */
PST_TEST(redundancy,TC_05_02) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EXPECT_ASSERT(MRC_ValidateCellVoltage(&input_vb,NULL_PTR,&input_vb),904);
}

/* TC_05_03: MRC_ValidateCellVoltage parameter 3 NULL assert. Requirements [26]. */
PST_TEST(redundancy,TC_05_03) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EXPECT_ASSERT(MRC_ValidateCellVoltage(&input_vb,&input_vb,NULL_PTR),905);
}

/* TC_06_01: MRC_UpdateCellVoltageValidation parameter 1 NULL assert. Requirements [26]. */
PST_TEST(redundancy,TC_06_01) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EXPECT_ASSERT(MRC_UpdateCellVoltageValidation(NULL_PTR,&input_vb),976);
}

/* TC_06_02: MRC_UpdateCellVoltageValidation parameter 2 NULL assert. Requirements [26]. */
PST_TEST(redundancy,TC_06_02) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EXPECT_ASSERT(MRC_UpdateCellVoltageValidation(&input_vb,NULL_PTR),977);
}

/* TC_07_01: MRC_ValidateCellTemperature parameter 1 NULL assert. Requirements [26]. */
PST_TEST(redundancy,TC_07_01) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EXPECT_ASSERT(MRC_ValidateCellTemperature(NULL_PTR,&input_tb,&input_tb),994);
}

/* TC_07_02: MRC_ValidateCellTemperature parameter 2 NULL assert. Requirements [26]. */
PST_TEST(redundancy,TC_07_02) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EXPECT_ASSERT(MRC_ValidateCellTemperature(&input_tb,NULL_PTR,&input_tb),995);
}

/* TC_07_03: MRC_ValidateCellTemperature parameter 3 NULL assert. Requirements [26]. */
PST_TEST(redundancy,TC_07_03) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EXPECT_ASSERT(MRC_ValidateCellTemperature(&input_tb,&input_tb,NULL_PTR),996);
}

/* TC_08_01: MRC_UpdateCellTemperatureValidation parameter 1 NULL assert. Requirements [26]. */
PST_TEST(redundancy,TC_08_01) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EXPECT_ASSERT(MRC_UpdateCellTemperatureValidation(NULL_PTR,&input_tb),1068);
}

/* TC_08_02: MRC_UpdateCellTemperatureValidation parameter 2 NULL assert. Requirements [26]. */
PST_TEST(redundancy,TC_08_02) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EXPECT_ASSERT(MRC_UpdateCellTemperatureValidation(&input_tb,NULL_PTR),1069);
}

/* TC_10_01: MRC_ValidateCellVoltageMeasurement parameter 1 NULL assert. Requirements [26]. */
PST_TEST(redundancy,TC_10_01) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EXPECT_ASSERT(MRC_ValidateCellVoltageMeasurement(NULL_PTR,&input_vr),279);
}

/* TC_10_02: MRC_ValidateCellVoltageMeasurement parameter 2 NULL assert. Requirements [26]. */
PST_TEST(redundancy,TC_10_02) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EXPECT_ASSERT(MRC_ValidateCellVoltageMeasurement(&input_vb,NULL_PTR),280);
}

/* TC_09: Never measured AFE, preserve state and no writes. Requirements [4, 5, 6, 7, 15, 25]. */
PST_TEST(redundancy,TC_09) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */

test_tick=0;
DATA_BLOCK_CELL_VOLTAGE_s before_v=mrc_tableCellVoltages;
DATA_BLOCK_CELL_TEMPERATURE_s before_t=mrc_tableCellTemperatures;
DATA_BLOCK_MIN_MAX_s before_mm=mrc_tableMinimumMaximumValues;
MRC_STATE_s before_state=mrc_state;
EQ(MRC_ValidateAfeMeasurement(),STD_NOT_OK); EQ(write_calls,0); EQ(read_calls,1);
EQ(memcmp(&before_v,&mrc_tableCellVoltages,sizeof(before_v)),0);
EQ(memcmp(&before_t,&mrc_tableCellTemperatures,sizeof(before_t)),0);
EQ(memcmp(&before_mm,&mrc_tableMinimumMaximumValues,sizeof(before_mm)),0);
EQ(memcmp(&before_state,&mrc_state,sizeof(before_state)),0);
EQ(event_count,4);
EVENT(DIAG_ID_BASE_CELL_VOLTAGE_MEASUREMENT_TIMEOUT,DIAG_EVENT_NOT_OK,DIAG_SYSTEM,0);
EVENT(DIAG_ID_REDUNDANCY0_CELL_VOLTAGE_MEASUREMENT_TIMEOUT,DIAG_EVENT_OK,DIAG_SYSTEM,0);
EVENT(DIAG_ID_BASE_CELL_TEMPERATURE_MEASUREMENT_TIMEOUT,DIAG_EVENT_NOT_OK,DIAG_SYSTEM,0);
EVENT(DIAG_ID_REDUNDANCY0_CELL_TEMPERATURE_MEASUREMENT_TIMEOUT,DIAG_EVENT_OK,DIAG_SYSTEM,0);

}

/* ADD_NULL_ValidateCellTemperatureMeasurement_1: Additional required pointer assert. Requirements [26]. */
PST_TEST(redundancy,ADD_NULL_ValidateCellTemperatureMeasurement_1) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EXPECT_ASSERT(MRC_ValidateCellTemperatureMeasurement(NULL_PTR,&input_tr),408);
}

/* ADD_NULL_ValidateCellTemperatureMeasurement_2: Additional required pointer assert. Requirements [26]. */
PST_TEST(redundancy,ADD_NULL_ValidateCellTemperatureMeasurement_2) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EXPECT_ASSERT(MRC_ValidateCellTemperatureMeasurement(&input_tb,NULL_PTR),409);
}

/* ADD_NULL_ValidateCurrentMeasurement_1: Additional required pointer assert. Requirements [26]. */
PST_TEST(redundancy,ADD_NULL_ValidateCurrentMeasurement_1) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EXPECT_ASSERT(MRC_ValidateCurrentMeasurement(NULL_PTR),534);
}

/* ADD_NULL_ValidateStringVoltageMeasurement_1: Additional required pointer assert. Requirements [26]. */
PST_TEST(redundancy,ADD_NULL_ValidateStringVoltageMeasurement_1) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EXPECT_ASSERT(MRC_ValidateStringVoltageMeasurement(NULL_PTR,&input_vb),586);
}

/* ADD_NULL_ValidateStringVoltageMeasurement_2: Additional required pointer assert. Requirements [26]. */
PST_TEST(redundancy,ADD_NULL_ValidateStringVoltageMeasurement_2) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EXPECT_ASSERT(MRC_ValidateStringVoltageMeasurement(&input_v1,NULL_PTR),587);
}

/* ADD_NULL_ValidateHighVoltageBusMeasurement_1: Additional required pointer assert. Requirements [26]. */
PST_TEST(redundancy,ADD_NULL_ValidateHighVoltageBusMeasurement_1) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EXPECT_ASSERT(MRC_ValidateHighVoltageBusMeasurement(NULL_PTR),691);
}

/* ADD_NULL_ValidatePowerMeasurement_1: Additional required pointer assert. Requirements [26]. */
PST_TEST(redundancy,ADD_NULL_ValidatePowerMeasurement_1) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
EXPECT_ASSERT(MRC_ValidatePowerMeasurement(NULL_PTR),725);
}

/* ADD_INIT_0: Initialization invalid flags, DB block order and forwarded response. Requirements [1, 2, 3]. */
PST_TEST(redundancy,ADD_INIT_0) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */

write_result=(STD_RETURN_TYPE_e)0; EQ(MRC_Initialize(),0);
EQ(write_calls,1); EQ(written_count,3);
EQ(written_ids[0],DATA_BLOCK_ID_CELL_VOLTAGE); EQ(written_ids[1],DATA_BLOCK_ID_CELL_TEMPERATURE); EQ(written_ids[2],DATA_BLOCK_ID_PACK_VALUES);
for(unsigned s=0;s<BS_NR_OF_STRINGS;s++) {
 EQ(saved_voltage.invalidStringVoltage[s],1);
 for(unsigned m=0;m<BS_NR_OF_MODULES_PER_STRING;m++) {
  EQ(saved_voltage.invalidModuleVoltage[s][m],1);
  for(unsigned c=0;c<BS_NR_OF_CELL_BLOCKS_PER_MODULE;c++) EQ(saved_voltage.invalidCellVoltage[s][m][c],1);
  for(unsigned t=0;t<BS_NR_OF_TEMP_SENSORS_PER_MODULE;t++) EQ(saved_temperature.invalidCellTemperature[s][m][t],1);
 }
 EQ(saved_pack.invalidStringVoltage[s],1); EQ(saved_pack.invalidStringCurrent[s],1); EQ(saved_pack.invalidStringPower[s],1);
}
EQ(saved_pack.invalidPackCurrent,1); EQ(saved_pack.invalidPackPower,1); EQ(saved_pack.invalidBatteryVoltage,1); EQ(saved_pack.invalidHvBusVoltage,1);

}

/* ADD_INIT_1: Initialization invalid flags, DB block order and forwarded response. Requirements [1, 2, 3]. */
PST_TEST(redundancy,ADD_INIT_1) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */

write_result=(STD_RETURN_TYPE_e)1; EQ(MRC_Initialize(),1);
EQ(write_calls,1); EQ(written_count,3);
EQ(written_ids[0],DATA_BLOCK_ID_CELL_VOLTAGE); EQ(written_ids[1],DATA_BLOCK_ID_CELL_TEMPERATURE); EQ(written_ids[2],DATA_BLOCK_ID_PACK_VALUES);
for(unsigned s=0;s<BS_NR_OF_STRINGS;s++) {
 EQ(saved_voltage.invalidStringVoltage[s],1);
 for(unsigned m=0;m<BS_NR_OF_MODULES_PER_STRING;m++) {
  EQ(saved_voltage.invalidModuleVoltage[s][m],1);
  for(unsigned c=0;c<BS_NR_OF_CELL_BLOCKS_PER_MODULE;c++) EQ(saved_voltage.invalidCellVoltage[s][m][c],1);
  for(unsigned t=0;t<BS_NR_OF_TEMP_SENSORS_PER_MODULE;t++) EQ(saved_temperature.invalidCellTemperature[s][m][t],1);
 }
 EQ(saved_pack.invalidStringVoltage[s],1); EQ(saved_pack.invalidStringCurrent[s],1); EQ(saved_pack.invalidStringPower[s],1);
}
EQ(saved_pack.invalidPackCurrent,1); EQ(saved_pack.invalidPackPower,1); EQ(saved_pack.invalidBatteryVoltage,1); EQ(saved_pack.invalidHvBusVoltage,1);

}

/* ADD_TIME_250_249: Actual timeout inclusive boundary. Requirements [5]. */
PST_TEST(redundancy,ADD_TIME_250_249) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
test_tick=1000u+249u; EQ(MRC_MeasurementUpdatedRecently(1000u,0u,250u),0);
}

/* ADD_TIME_250_250: Actual timeout inclusive boundary. Requirements [5]. */
PST_TEST(redundancy,ADD_TIME_250_250) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
test_tick=1000u+250u; EQ(MRC_MeasurementUpdatedRecently(1000u,0u,250u),0);
}

/* ADD_TIME_250_251: Actual timeout inclusive boundary. Requirements [5]. */
PST_TEST(redundancy,ADD_TIME_250_251) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
test_tick=1000u+251u; EQ(MRC_MeasurementUpdatedRecently(1000u,0u,250u),1);
}

/* ADD_TIME_WRAP_250: Timestamp zero with previous history. Requirements [4, 5]. */
PST_TEST(redundancy,ADD_TIME_WRAP_250) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
test_tick=250u; EQ(MRC_MeasurementUpdatedRecently(0u,UINT32_MAX,250u),STD_OK);
}

/* ADD_TIME_300_299: Actual timeout inclusive boundary. Requirements [5]. */
PST_TEST(redundancy,ADD_TIME_300_299) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
test_tick=1000u+299u; EQ(MRC_MeasurementUpdatedRecently(1000u,0u,300u),0);
}

/* ADD_TIME_300_300: Actual timeout inclusive boundary. Requirements [5]. */
PST_TEST(redundancy,ADD_TIME_300_300) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
test_tick=1000u+300u; EQ(MRC_MeasurementUpdatedRecently(1000u,0u,300u),0);
}

/* ADD_TIME_300_301: Actual timeout inclusive boundary. Requirements [5]. */
PST_TEST(redundancy,ADD_TIME_300_301) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
test_tick=1000u+301u; EQ(MRC_MeasurementUpdatedRecently(1000u,0u,300u),1);
}

/* ADD_TIME_WRAP_300: Timestamp zero with previous history. Requirements [4, 5]. */
PST_TEST(redundancy,ADD_TIME_WRAP_300) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
test_tick=300u; EQ(MRC_MeasurementUpdatedRecently(0u,UINT32_MAX,300u),STD_OK);
}

/* ADD_SELECT_V_base_only: AFE source selection base_only. Requirements [6, 7, 15, 25]. */
PST_TEST(redundancy,ADD_SELECT_V_base_only) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&input_vb,3500); fill_voltage(&input_vr,3510); fill_voltage(&mrc_tableCellVoltages,777); input_vb.header.timestamp=1000;input_vr.header.timestamp=0; mrc_state.lastBaseCellVoltageTimestamp=0;mrc_state.lastRedundancy0CellVoltageTimestamp=0;test_tick=1000; EQ(MRC_ValidateCellVoltageMeasurement(&input_vb,&input_vr),1);EQ(mrc_tableCellVoltages.cellVoltage_mV[0][0][0],3500);
}

/* ADD_SELECT_V_both_new: AFE source selection both_new. Requirements [6, 7, 15, 25]. */
PST_TEST(redundancy,ADD_SELECT_V_both_new) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&input_vb,3500); fill_voltage(&input_vr,3510); fill_voltage(&mrc_tableCellVoltages,777); input_vb.header.timestamp=1000;input_vr.header.timestamp=1000; mrc_state.lastBaseCellVoltageTimestamp=0;mrc_state.lastRedundancy0CellVoltageTimestamp=0;test_tick=1000; EQ(MRC_ValidateCellVoltageMeasurement(&input_vb,&input_vr),1);EQ(mrc_tableCellVoltages.cellVoltage_mV[0][0][0],3505);
}

/* ADD_SELECT_V_base_new_red_timeout: AFE source selection base_new_red_timeout. Requirements [6, 7, 15, 25]. */
PST_TEST(redundancy,ADD_SELECT_V_base_new_red_timeout) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&input_vb,3500); fill_voltage(&input_vr,3510); fill_voltage(&mrc_tableCellVoltages,777); input_vb.header.timestamp=1000;input_vr.header.timestamp=500; mrc_state.lastBaseCellVoltageTimestamp=0;mrc_state.lastRedundancy0CellVoltageTimestamp=500;test_tick=1000; EQ(MRC_ValidateCellVoltageMeasurement(&input_vb,&input_vr),1);EQ(mrc_tableCellVoltages.cellVoltage_mV[0][0][0],3500);
}

/* ADD_SELECT_V_red_new_base_timeout: AFE source selection red_new_base_timeout. Requirements [6, 7, 15, 25]. */
PST_TEST(redundancy,ADD_SELECT_V_red_new_base_timeout) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&input_vb,3500); fill_voltage(&input_vr,3510); fill_voltage(&mrc_tableCellVoltages,777); input_vb.header.timestamp=500;input_vr.header.timestamp=1000; mrc_state.lastBaseCellVoltageTimestamp=500;mrc_state.lastRedundancy0CellVoltageTimestamp=0;test_tick=1000; EQ(MRC_ValidateCellVoltageMeasurement(&input_vb,&input_vr),1);EQ(mrc_tableCellVoltages.cellVoltage_mV[0][0][0],3510);
}

/* ADD_SELECT_V_base_new_red_fresh: AFE source selection base_new_red_fresh. Requirements [6, 7, 15, 25]. */
PST_TEST(redundancy,ADD_SELECT_V_base_new_red_fresh) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&input_vb,3500); fill_voltage(&input_vr,3510); fill_voltage(&mrc_tableCellVoltages,777); input_vb.header.timestamp=1000;input_vr.header.timestamp=900; mrc_state.lastBaseCellVoltageTimestamp=0;mrc_state.lastRedundancy0CellVoltageTimestamp=900;test_tick=1000; EQ(MRC_ValidateCellVoltageMeasurement(&input_vb,&input_vr),0);EQ(mrc_tableCellVoltages.cellVoltage_mV[0][0][0],777);
}

/* ADD_SELECT_V_red_new_base_fresh: AFE source selection red_new_base_fresh. Requirements [6, 7, 15, 25]. */
PST_TEST(redundancy,ADD_SELECT_V_red_new_base_fresh) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&input_vb,3500); fill_voltage(&input_vr,3510); fill_voltage(&mrc_tableCellVoltages,777); input_vb.header.timestamp=900;input_vr.header.timestamp=1000; mrc_state.lastBaseCellVoltageTimestamp=900;mrc_state.lastRedundancy0CellVoltageTimestamp=0;test_tick=1000; EQ(MRC_ValidateCellVoltageMeasurement(&input_vb,&input_vr),0);EQ(mrc_tableCellVoltages.cellVoltage_mV[0][0][0],777);
}

/* ADD_SELECT_V_none_new: AFE source selection none_new. Requirements [6, 7, 15, 25]. */
PST_TEST(redundancy,ADD_SELECT_V_none_new) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&input_vb,3500); fill_voltage(&input_vr,3510); fill_voltage(&mrc_tableCellVoltages,777); input_vb.header.timestamp=900;input_vr.header.timestamp=900; mrc_state.lastBaseCellVoltageTimestamp=900;mrc_state.lastRedundancy0CellVoltageTimestamp=900;test_tick=1000; EQ(MRC_ValidateCellVoltageMeasurement(&input_vb,&input_vr),0);EQ(mrc_tableCellVoltages.cellVoltage_mV[0][0][0],777);
}

/* ADD_SELECT_V_base_only_not_new: AFE source selection base_only_not_new. Requirements [6, 7, 15, 25]. */
PST_TEST(redundancy,ADD_SELECT_V_base_only_not_new) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&input_vb,3500); fill_voltage(&input_vr,3510); fill_voltage(&mrc_tableCellVoltages,777); input_vb.header.timestamp=900;input_vr.header.timestamp=0; mrc_state.lastBaseCellVoltageTimestamp=900;mrc_state.lastRedundancy0CellVoltageTimestamp=0;test_tick=1000; EQ(MRC_ValidateCellVoltageMeasurement(&input_vb,&input_vr),0);EQ(mrc_tableCellVoltages.cellVoltage_mV[0][0][0],777);
}

/* ADD_SELECT_T_base_only: AFE source selection base_only. Requirements [6, 7, 15, 25]. */
PST_TEST(redundancy,ADD_SELECT_T_base_only) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,210);fill_temperature(&mrc_tableCellTemperatures,777);input_tb.header.timestamp=1000;input_tr.header.timestamp=0;mrc_state.lastBaseCellTemperatureTimestamp=0;mrc_state.lastRedundancy0CellTemperatureTimestamp=0;test_tick=1000; EQ(MRC_ValidateCellTemperatureMeasurement(&input_tb,&input_tr),1);EQ(mrc_tableCellTemperatures.cellTemperature_ddegC[0][0][0],200);
}

/* ADD_SELECT_T_both_new: AFE source selection both_new. Requirements [6, 7, 15, 25]. */
PST_TEST(redundancy,ADD_SELECT_T_both_new) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,210);fill_temperature(&mrc_tableCellTemperatures,777);input_tb.header.timestamp=1000;input_tr.header.timestamp=1000;mrc_state.lastBaseCellTemperatureTimestamp=0;mrc_state.lastRedundancy0CellTemperatureTimestamp=0;test_tick=1000; EQ(MRC_ValidateCellTemperatureMeasurement(&input_tb,&input_tr),1);EQ(mrc_tableCellTemperatures.cellTemperature_ddegC[0][0][0],205);
}

/* ADD_SELECT_T_base_new_red_timeout: AFE source selection base_new_red_timeout. Requirements [6, 7, 15, 25]. */
PST_TEST(redundancy,ADD_SELECT_T_base_new_red_timeout) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,210);fill_temperature(&mrc_tableCellTemperatures,777);input_tb.header.timestamp=1000;input_tr.header.timestamp=500;mrc_state.lastBaseCellTemperatureTimestamp=0;mrc_state.lastRedundancy0CellTemperatureTimestamp=500;test_tick=1000; EQ(MRC_ValidateCellTemperatureMeasurement(&input_tb,&input_tr),1);EQ(mrc_tableCellTemperatures.cellTemperature_ddegC[0][0][0],200);
}

/* ADD_SELECT_T_red_new_base_timeout: AFE source selection red_new_base_timeout. Requirements [6, 7, 15, 25]. */
PST_TEST(redundancy,ADD_SELECT_T_red_new_base_timeout) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,210);fill_temperature(&mrc_tableCellTemperatures,777);input_tb.header.timestamp=500;input_tr.header.timestamp=1000;mrc_state.lastBaseCellTemperatureTimestamp=500;mrc_state.lastRedundancy0CellTemperatureTimestamp=0;test_tick=1000; EQ(MRC_ValidateCellTemperatureMeasurement(&input_tb,&input_tr),1);EQ(mrc_tableCellTemperatures.cellTemperature_ddegC[0][0][0],210);
}

/* ADD_SELECT_T_base_new_red_fresh: AFE source selection base_new_red_fresh. Requirements [6, 7, 15, 25]. */
PST_TEST(redundancy,ADD_SELECT_T_base_new_red_fresh) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,210);fill_temperature(&mrc_tableCellTemperatures,777);input_tb.header.timestamp=1000;input_tr.header.timestamp=900;mrc_state.lastBaseCellTemperatureTimestamp=0;mrc_state.lastRedundancy0CellTemperatureTimestamp=900;test_tick=1000; EQ(MRC_ValidateCellTemperatureMeasurement(&input_tb,&input_tr),0);EQ(mrc_tableCellTemperatures.cellTemperature_ddegC[0][0][0],777);
}

/* ADD_SELECT_T_red_new_base_fresh: AFE source selection red_new_base_fresh. Requirements [6, 7, 15, 25]. */
PST_TEST(redundancy,ADD_SELECT_T_red_new_base_fresh) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,210);fill_temperature(&mrc_tableCellTemperatures,777);input_tb.header.timestamp=900;input_tr.header.timestamp=1000;mrc_state.lastBaseCellTemperatureTimestamp=900;mrc_state.lastRedundancy0CellTemperatureTimestamp=0;test_tick=1000; EQ(MRC_ValidateCellTemperatureMeasurement(&input_tb,&input_tr),0);EQ(mrc_tableCellTemperatures.cellTemperature_ddegC[0][0][0],777);
}

/* ADD_SELECT_T_none_new: AFE source selection none_new. Requirements [6, 7, 15, 25]. */
PST_TEST(redundancy,ADD_SELECT_T_none_new) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,210);fill_temperature(&mrc_tableCellTemperatures,777);input_tb.header.timestamp=900;input_tr.header.timestamp=900;mrc_state.lastBaseCellTemperatureTimestamp=900;mrc_state.lastRedundancy0CellTemperatureTimestamp=900;test_tick=1000; EQ(MRC_ValidateCellTemperatureMeasurement(&input_tb,&input_tr),0);EQ(mrc_tableCellTemperatures.cellTemperature_ddegC[0][0][0],777);
}

/* ADD_SELECT_T_base_only_not_new: AFE source selection base_only_not_new. Requirements [6, 7, 15, 25]. */
PST_TEST(redundancy,ADD_SELECT_T_base_only_not_new) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,210);fill_temperature(&mrc_tableCellTemperatures,777);input_tb.header.timestamp=900;input_tr.header.timestamp=0;mrc_state.lastBaseCellTemperatureTimestamp=900;mrc_state.lastRedundancy0CellTemperatureTimestamp=0;test_tick=1000; EQ(MRC_ValidateCellTemperatureMeasurement(&input_tb,&input_tr),0);EQ(mrc_tableCellTemperatures.cellTemperature_ddegC[0][0][0],777);
}

/* ADD_COPY_V: Copy body while preserving complete output header. Requirements [7]. */
PST_TEST(redundancy,ADD_COPY_V) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&input_vb,123);input_vb.header.timestamp=900;mrc_tableCellVoltages.header.timestamp=81;mrc_tableCellVoltages.header.previousTimestamp=80;DATA_BLOCK_HEADER_s h=mrc_tableCellVoltages.header;DATA_BLOCK_CELL_VOLTAGE_s expected=input_vb;expected.header=h;EQ(MRC_UpdateCellVoltageValidation(&input_vb,&mrc_tableCellVoltages),STD_OK);EQ(memcmp(&expected,&mrc_tableCellVoltages,sizeof(expected)),0);
}

/* ADD_COPY_T: Copy body while preserving complete output header. Requirements [7]. */
PST_TEST(redundancy,ADD_COPY_T) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,123);input_tb.header.timestamp=900;mrc_tableCellTemperatures.header.timestamp=81;mrc_tableCellTemperatures.header.previousTimestamp=80;DATA_BLOCK_HEADER_s h=mrc_tableCellTemperatures.header;DATA_BLOCK_CELL_TEMPERATURE_s expected=input_tb;expected.header=h;EQ(MRC_UpdateCellTemperatureValidation(&input_tb,&mrc_tableCellTemperatures),STD_OK);EQ(memcmp(&expected,&mrc_tableCellTemperatures,sizeof(expected)),0);
}

/* ADD_COMPARE_V_threshold: threshold. Requirements [8, 10, 25]. */
PST_TEST(redundancy,ADD_COMPARE_V_threshold) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&input_vb,3500);fill_voltage(&input_vr,3500);input_vb.invalidCellVoltage[0][0][0]=0;input_vr.invalidCellVoltage[0][0][0]=0;input_vr.cellVoltage_mV[0][0][0]=3510; EQ(MRC_ValidateCellVoltage(&input_vb,&input_vr,&mrc_tableCellVoltages),0);EQ(mrc_tableCellVoltages.invalidCellVoltage[0][0][0],0);EQ(mrc_tableCellVoltages.cellVoltage_mV[0][0][0],3505);EQ(mrc_tableCellVoltages.nrValidCellVoltages[0],18-0);EQ(mrc_tableCellVoltages.stringVoltage_mV[0],17*3500+3505);
}

/* ADD_COMPARE_V_over: over. Requirements [8, 10, 25]. */
PST_TEST(redundancy,ADD_COMPARE_V_over) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&input_vb,3500);fill_voltage(&input_vr,3500);input_vb.invalidCellVoltage[0][0][0]=0;input_vr.invalidCellVoltage[0][0][0]=0;input_vr.cellVoltage_mV[0][0][0]=3511; EQ(MRC_ValidateCellVoltage(&input_vb,&input_vr,&mrc_tableCellVoltages),1);EQ(mrc_tableCellVoltages.invalidCellVoltage[0][0][0],1);EQ(mrc_tableCellVoltages.cellVoltage_mV[0][0][0],3505);EQ(mrc_tableCellVoltages.nrValidCellVoltages[0],18-1);EQ(mrc_tableCellVoltages.stringVoltage_mV[0],17*3500+0);
}

/* ADD_COMPARE_V_base_only: base_only. Requirements [8, 10, 25]. */
PST_TEST(redundancy,ADD_COMPARE_V_base_only) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&input_vb,3500);fill_voltage(&input_vr,3500);input_vb.invalidCellVoltage[0][0][0]=0;input_vr.invalidCellVoltage[0][0][0]=1;input_vr.cellVoltage_mV[0][0][0]=3501; EQ(MRC_ValidateCellVoltage(&input_vb,&input_vr,&mrc_tableCellVoltages),0);EQ(mrc_tableCellVoltages.invalidCellVoltage[0][0][0],0);EQ(mrc_tableCellVoltages.cellVoltage_mV[0][0][0],3500);EQ(mrc_tableCellVoltages.nrValidCellVoltages[0],18-0);EQ(mrc_tableCellVoltages.stringVoltage_mV[0],17*3500+3500);
}

/* ADD_COMPARE_V_red_only: red_only. Requirements [8, 10, 25]. */
PST_TEST(redundancy,ADD_COMPARE_V_red_only) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&input_vb,3500);fill_voltage(&input_vr,3500);input_vb.invalidCellVoltage[0][0][0]=1;input_vr.invalidCellVoltage[0][0][0]=0;input_vr.cellVoltage_mV[0][0][0]=3501; EQ(MRC_ValidateCellVoltage(&input_vb,&input_vr,&mrc_tableCellVoltages),0);EQ(mrc_tableCellVoltages.invalidCellVoltage[0][0][0],0);EQ(mrc_tableCellVoltages.cellVoltage_mV[0][0][0],3501);EQ(mrc_tableCellVoltages.nrValidCellVoltages[0],18-0);EQ(mrc_tableCellVoltages.stringVoltage_mV[0],17*3500+3501);
}

/* ADD_COMPARE_V_both_invalid: both_invalid. Requirements [8, 10, 25]. */
PST_TEST(redundancy,ADD_COMPARE_V_both_invalid) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&input_vb,3500);fill_voltage(&input_vr,3500);input_vb.invalidCellVoltage[0][0][0]=1;input_vr.invalidCellVoltage[0][0][0]=1;input_vr.cellVoltage_mV[0][0][0]=3501; EQ(MRC_ValidateCellVoltage(&input_vb,&input_vr,&mrc_tableCellVoltages),1);EQ(mrc_tableCellVoltages.invalidCellVoltage[0][0][0],1);EQ(mrc_tableCellVoltages.cellVoltage_mV[0][0][0],3500);EQ(mrc_tableCellVoltages.nrValidCellVoltages[0],18-1);EQ(mrc_tableCellVoltages.stringVoltage_mV[0],17*3500+0);
}

/* ADD_COMPARE_T_threshold: threshold. Requirements [9, 10, 25]. */
PST_TEST(redundancy,ADD_COMPARE_T_threshold) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,200);input_tb.invalidCellTemperature[0][0][0]=0;input_tr.invalidCellTemperature[0][0][0]=0;input_tr.cellTemperature_ddegC[0][0][0]=250; EQ(MRC_ValidateCellTemperature(&input_tb,&input_tr,&mrc_tableCellTemperatures),0);EQ(mrc_tableCellTemperatures.invalidCellTemperature[0][0][0],0);EQ(mrc_tableCellTemperatures.cellTemperature_ddegC[0][0][0],225);EQ(mrc_tableCellTemperatures.nrValidTemperatures[0],8-0);
}

/* ADD_COMPARE_T_over: over. Requirements [9, 10, 25]. */
PST_TEST(redundancy,ADD_COMPARE_T_over) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,200);input_tb.invalidCellTemperature[0][0][0]=0;input_tr.invalidCellTemperature[0][0][0]=0;input_tr.cellTemperature_ddegC[0][0][0]=251; EQ(MRC_ValidateCellTemperature(&input_tb,&input_tr,&mrc_tableCellTemperatures),1);EQ(mrc_tableCellTemperatures.invalidCellTemperature[0][0][0],1);EQ(mrc_tableCellTemperatures.cellTemperature_ddegC[0][0][0],225);EQ(mrc_tableCellTemperatures.nrValidTemperatures[0],8-1);
}

/* ADD_COMPARE_T_base_only: base_only. Requirements [9, 10, 25]. */
PST_TEST(redundancy,ADD_COMPARE_T_base_only) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,200);input_tb.invalidCellTemperature[0][0][0]=0;input_tr.invalidCellTemperature[0][0][0]=1;input_tr.cellTemperature_ddegC[0][0][0]=201; EQ(MRC_ValidateCellTemperature(&input_tb,&input_tr,&mrc_tableCellTemperatures),0);EQ(mrc_tableCellTemperatures.invalidCellTemperature[0][0][0],0);EQ(mrc_tableCellTemperatures.cellTemperature_ddegC[0][0][0],200);EQ(mrc_tableCellTemperatures.nrValidTemperatures[0],8-0);
}

/* ADD_COMPARE_T_red_only: red_only. Requirements [9, 10, 25]. */
PST_TEST(redundancy,ADD_COMPARE_T_red_only) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,200);input_tb.invalidCellTemperature[0][0][0]=1;input_tr.invalidCellTemperature[0][0][0]=0;input_tr.cellTemperature_ddegC[0][0][0]=201; EQ(MRC_ValidateCellTemperature(&input_tb,&input_tr,&mrc_tableCellTemperatures),0);EQ(mrc_tableCellTemperatures.invalidCellTemperature[0][0][0],0);EQ(mrc_tableCellTemperatures.cellTemperature_ddegC[0][0][0],201);EQ(mrc_tableCellTemperatures.nrValidTemperatures[0],8-0);
}

/* ADD_COMPARE_T_both_invalid: both_invalid. Requirements [9, 10, 25]. */
PST_TEST(redundancy,ADD_COMPARE_T_both_invalid) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,200);input_tb.invalidCellTemperature[0][0][0]=1;input_tr.invalidCellTemperature[0][0][0]=1;input_tr.cellTemperature_ddegC[0][0][0]=201; EQ(MRC_ValidateCellTemperature(&input_tb,&input_tr,&mrc_tableCellTemperatures),1);EQ(mrc_tableCellTemperatures.invalidCellTemperature[0][0][0],1);EQ(mrc_tableCellTemperatures.cellTemperature_ddegC[0][0][0],200);EQ(mrc_tableCellTemperatures.nrValidTemperatures[0],8-1);
}

/* ADD_COMPARE_T_negative: Negative average truncates toward zero. Requirements [9]. */
PST_TEST(redundancy,ADD_COMPARE_T_negative) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,-201);fill_temperature(&input_tr,-200);EQ(MRC_ValidateCellTemperature(&input_tb,&input_tr,&mrc_tableCellTemperatures),STD_OK);EQ(mrc_tableCellTemperatures.cellTemperature_ddegC[0][0][0],-200);
}

/* ADD_STATS_V_valid_ties: Valid-only extrema, average, count and first ties. Requirements [11, 13]. */
PST_TEST(redundancy,ADD_STATS_V_valid_ties) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&mrc_tableCellVoltages,3500);for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){for(unsigned c=0;c<18;c++) mrc_tableCellVoltages.invalidCellVoltage[s][0][c]=1;mrc_tableCellVoltages.invalidCellVoltage[s][0][0]=0;mrc_tableCellVoltages.invalidCellVoltage[s][0][1]=0;mrc_tableCellVoltages.invalidCellVoltage[s][0][2]=0;mrc_tableCellVoltages.cellVoltage_mV[s][0][1]=3501;}EQ(MRC_CalculateCellVoltageMinMaxAverage(&mrc_tableCellVoltages,&mrc_tableMinimumMaximumValues),0);EQ(mrc_tableMinimumMaximumValues.minimumCellVoltage_mV[0],3500);EQ(mrc_tableMinimumMaximumValues.maximumCellVoltage_mV[0],3501);EQ(mrc_tableMinimumMaximumValues.validMeasuredCellVoltages[0],3);EQ(mrc_tableMinimumMaximumValues.nrCellMinimumCellVoltage[0],0);EQ(mrc_tableMinimumMaximumValues.nrCellMaximumCellVoltage[0],1);PST_VERIFY_EQ_APPROX_FLT(mrc_tableMinimumMaximumValues.averageCellVoltage_mV[0],3500,0.0001);
}

/* ADD_STATS_V_empty: Valid-only extrema, average, count and first ties. Requirements [11, 13]. */
PST_TEST(redundancy,ADD_STATS_V_empty) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&mrc_tableCellVoltages,3500);for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){for(unsigned c=0;c<18;c++) mrc_tableCellVoltages.invalidCellVoltage[s][0][c]=1;}EQ(MRC_CalculateCellVoltageMinMaxAverage(&mrc_tableCellVoltages,&mrc_tableMinimumMaximumValues),1);EQ(mrc_tableMinimumMaximumValues.minimumCellVoltage_mV[0],INT16_MAX);EQ(mrc_tableMinimumMaximumValues.maximumCellVoltage_mV[0],INT16_MIN);EQ(mrc_tableMinimumMaximumValues.validMeasuredCellVoltages[0],0);EQ(mrc_tableMinimumMaximumValues.nrCellMinimumCellVoltage[0],0);EQ(mrc_tableMinimumMaximumValues.nrCellMaximumCellVoltage[0],0);PST_VERIFY_EQ_APPROX_FLT(mrc_tableMinimumMaximumValues.averageCellVoltage_mV[0],0,0.0001);
}

/* ADD_STATS_T_valid_ties: Valid-only extrema, average, count and first ties. Requirements [12, 13]. */
PST_TEST(redundancy,ADD_STATS_T_valid_ties) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&mrc_tableCellTemperatures,200);for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){for(unsigned c=0;c<8;c++) mrc_tableCellTemperatures.invalidCellTemperature[s][0][c]=1;mrc_tableCellTemperatures.invalidCellTemperature[s][0][0]=0;mrc_tableCellTemperatures.invalidCellTemperature[s][0][1]=0;mrc_tableCellTemperatures.invalidCellTemperature[s][0][2]=0;mrc_tableCellTemperatures.cellTemperature_ddegC[s][0][1]=201;}EQ(MRC_CalculateCellTemperatureMinMaxAverage(&mrc_tableCellTemperatures,&mrc_tableMinimumMaximumValues),0);EQ(mrc_tableMinimumMaximumValues.minimumTemperature_ddegC[0],200);EQ(mrc_tableMinimumMaximumValues.maximumTemperature_ddegC[0],201);EQ(mrc_tableMinimumMaximumValues.validMeasuredCellTemperatures[0],3);EQ(mrc_tableMinimumMaximumValues.nrSensorMinimumTemperature[0],0);EQ(mrc_tableMinimumMaximumValues.nrSensorMaximumTemperature[0],1);PST_VERIFY_EQ_APPROX_FLT(mrc_tableMinimumMaximumValues.averageTemperature_ddegC[0],200.33333333333334,0.0001);
}

/* ADD_STATS_T_empty: Valid-only extrema, average, count and first ties. Requirements [12, 13]. */
PST_TEST(redundancy,ADD_STATS_T_empty) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&mrc_tableCellTemperatures,200);for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){for(unsigned c=0;c<8;c++) mrc_tableCellTemperatures.invalidCellTemperature[s][0][c]=1;}EQ(MRC_CalculateCellTemperatureMinMaxAverage(&mrc_tableCellTemperatures,&mrc_tableMinimumMaximumValues),1);EQ(mrc_tableMinimumMaximumValues.minimumTemperature_ddegC[0],INT16_MAX);EQ(mrc_tableMinimumMaximumValues.maximumTemperature_ddegC[0],INT16_MIN);EQ(mrc_tableMinimumMaximumValues.validMeasuredCellTemperatures[0],0);EQ(mrc_tableMinimumMaximumValues.nrSensorMinimumTemperature[0],0);EQ(mrc_tableMinimumMaximumValues.nrSensorMaximumTemperature[0],0);PST_VERIFY_EQ_APPROX_FLT(mrc_tableMinimumMaximumValues.averageTemperature_ddegC[0],0,0.0001);
}

/* ADD_AFE_WRITE_0: AFE processed block selection. Requirements [15]. */
PST_TEST(redundancy,ADD_AFE_WRITE_0) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&input_vb,3500);fill_temperature(&input_tb,200);input_vb.header.timestamp=0;input_tb.header.timestamp=0;EQ(MRC_ValidateAfeMeasurement(),1);EQ(write_calls,0);EQ(written_count,0);
}

/* ADD_AFE_WRITE_1: AFE processed block selection. Requirements [15]. */
PST_TEST(redundancy,ADD_AFE_WRITE_1) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&input_vb,3500);fill_temperature(&input_tb,200);input_vb.header.timestamp=1000;input_tb.header.timestamp=0;EQ(MRC_ValidateAfeMeasurement(),0);EQ(write_calls,1);EQ(written_count,2);EQ(written_ids[0],DATA_BLOCK_ID_CELL_VOLTAGE);EQ(written_ids[written_count-1],DATA_BLOCK_ID_MIN_MAX);
}

/* ADD_AFE_WRITE_2: AFE processed block selection. Requirements [15]. */
PST_TEST(redundancy,ADD_AFE_WRITE_2) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&input_vb,3500);fill_temperature(&input_tb,200);input_vb.header.timestamp=0;input_tb.header.timestamp=1000;EQ(MRC_ValidateAfeMeasurement(),0);EQ(write_calls,1);EQ(written_count,2);EQ(written_ids[0],DATA_BLOCK_ID_CELL_TEMPERATURE);EQ(written_ids[written_count-1],DATA_BLOCK_ID_MIN_MAX);
}

/* ADD_AFE_WRITE_3: AFE processed block selection. Requirements [15]. */
PST_TEST(redundancy,ADD_AFE_WRITE_3) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&input_vb,3500);fill_temperature(&input_tb,200);input_vb.header.timestamp=1000;input_tb.header.timestamp=1000;EQ(MRC_ValidateAfeMeasurement(),0);EQ(write_calls,1);EQ(written_count,3);EQ(written_ids[0],DATA_BLOCK_ID_CELL_VOLTAGE);EQ(written_ids[written_count-1],DATA_BLOCK_ID_MIN_MAX);
}

/* ADD_T_COUNT_single_8_repeat1: Final valid temperature count without accumulation. Requirements [10, 12, 14, 27]. */
PST_TEST(redundancy,ADD_T_COUNT_single_8_repeat1) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,200);input_tb.nrValidTemperatures[0]=8; for(unsigned call=0;call<1;call++){input_tb.header.timestamp=1000+call;input_tr.header.timestamp=0;test_tick=1000+call;EQ(MRC_ValidateCellTemperatureMeasurement(&input_tb,&input_tr),1);check_final_temperature_count();}EQ(mrc_tableCellTemperatures.nrValidTemperatures[0],8);EQ(mrc_tableMinimumMaximumValues.validMeasuredCellTemperatures[0],8);
}

/* ADD_T_COUNT_single_8_repeat2: Final valid temperature count without accumulation. Requirements [10, 12, 14, 27]. */
PST_TEST(redundancy,ADD_T_COUNT_single_8_repeat2) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,200);input_tb.nrValidTemperatures[0]=8; for(unsigned call=0;call<2;call++){input_tb.header.timestamp=1000+call;input_tr.header.timestamp=0;test_tick=1000+call;EQ(MRC_ValidateCellTemperatureMeasurement(&input_tb,&input_tr),1);check_final_temperature_count();}EQ(mrc_tableCellTemperatures.nrValidTemperatures[0],8);EQ(mrc_tableMinimumMaximumValues.validMeasuredCellTemperatures[0],8);
}

/* ADD_T_COUNT_single_7_repeat1: Final valid temperature count without accumulation. Requirements [10, 12, 14, 27]. */
PST_TEST(redundancy,ADD_T_COUNT_single_7_repeat1) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,200);input_tb.cellTemperature_ddegC[0][0][7]=400;input_tr.cellTemperature_ddegC[0][0][7]=400;input_tb.nrValidTemperatures[0]=8; for(unsigned call=0;call<1;call++){input_tb.header.timestamp=1000+call;input_tr.header.timestamp=0;test_tick=1000+call;EQ(MRC_ValidateCellTemperatureMeasurement(&input_tb,&input_tr),1);check_final_temperature_count();}EQ(mrc_tableCellTemperatures.nrValidTemperatures[0],7);EQ(mrc_tableMinimumMaximumValues.validMeasuredCellTemperatures[0],7);
}

/* ADD_T_COUNT_single_7_repeat2: Final valid temperature count without accumulation. Requirements [10, 12, 14, 27]. */
PST_TEST(redundancy,ADD_T_COUNT_single_7_repeat2) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,200);input_tb.cellTemperature_ddegC[0][0][7]=400;input_tr.cellTemperature_ddegC[0][0][7]=400;input_tb.nrValidTemperatures[0]=8; for(unsigned call=0;call<2;call++){input_tb.header.timestamp=1000+call;input_tr.header.timestamp=0;test_tick=1000+call;EQ(MRC_ValidateCellTemperatureMeasurement(&input_tb,&input_tr),1);check_final_temperature_count();}EQ(mrc_tableCellTemperatures.nrValidTemperatures[0],7);EQ(mrc_tableMinimumMaximumValues.validMeasuredCellTemperatures[0],7);
}

/* ADD_T_COUNT_single_0_repeat1: Final valid temperature count without accumulation. Requirements [10, 12, 14, 27]. */
PST_TEST(redundancy,ADD_T_COUNT_single_0_repeat1) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,200);for(unsigned s=0;s<BS_NR_OF_STRINGS;s++)for(unsigned t=0;t<8;t++){input_tb.invalidCellTemperature[s][0][t]=1;input_tr.invalidCellTemperature[s][0][t]=1;}input_tb.nrValidTemperatures[0]=0; for(unsigned call=0;call<1;call++){input_tb.header.timestamp=1000+call;input_tr.header.timestamp=0;test_tick=1000+call;EQ(MRC_ValidateCellTemperatureMeasurement(&input_tb,&input_tr),1);check_final_temperature_count();}EQ(mrc_tableCellTemperatures.nrValidTemperatures[0],0);EQ(mrc_tableMinimumMaximumValues.validMeasuredCellTemperatures[0],0);
}

/* ADD_T_COUNT_single_0_repeat2: Final valid temperature count without accumulation. Requirements [10, 12, 14, 27]. */
PST_TEST(redundancy,ADD_T_COUNT_single_0_repeat2) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,200);for(unsigned s=0;s<BS_NR_OF_STRINGS;s++)for(unsigned t=0;t<8;t++){input_tb.invalidCellTemperature[s][0][t]=1;input_tr.invalidCellTemperature[s][0][t]=1;}input_tb.nrValidTemperatures[0]=0; for(unsigned call=0;call<2;call++){input_tb.header.timestamp=1000+call;input_tr.header.timestamp=0;test_tick=1000+call;EQ(MRC_ValidateCellTemperatureMeasurement(&input_tb,&input_tr),1);check_final_temperature_count();}EQ(mrc_tableCellTemperatures.nrValidTemperatures[0],0);EQ(mrc_tableMinimumMaximumValues.validMeasuredCellTemperatures[0],0);
}

/* ADD_T_COUNT_dual_8_repeat1: Final valid temperature count without accumulation. Requirements [10, 12, 14, 27]. */
PST_TEST(redundancy,ADD_T_COUNT_dual_8_repeat1) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,200);input_tb.nrValidTemperatures[0]=8; for(unsigned call=0;call<1;call++){input_tb.header.timestamp=1000+call;input_tr.header.timestamp=1000+call;test_tick=1000+call;EQ(MRC_ValidateCellTemperatureMeasurement(&input_tb,&input_tr),1);check_final_temperature_count();}EQ(mrc_tableCellTemperatures.nrValidTemperatures[0],8);EQ(mrc_tableMinimumMaximumValues.validMeasuredCellTemperatures[0],8);
}

/* ADD_T_COUNT_dual_8_repeat2: Final valid temperature count without accumulation. Requirements [10, 12, 14, 27]. */
PST_TEST(redundancy,ADD_T_COUNT_dual_8_repeat2) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,200);input_tb.nrValidTemperatures[0]=8; for(unsigned call=0;call<2;call++){input_tb.header.timestamp=1000+call;input_tr.header.timestamp=1000+call;test_tick=1000+call;EQ(MRC_ValidateCellTemperatureMeasurement(&input_tb,&input_tr),1);check_final_temperature_count();}EQ(mrc_tableCellTemperatures.nrValidTemperatures[0],8);EQ(mrc_tableMinimumMaximumValues.validMeasuredCellTemperatures[0],8);
}

/* ADD_T_COUNT_dual_7_repeat1: Final valid temperature count without accumulation. Requirements [10, 12, 14, 27]. */
PST_TEST(redundancy,ADD_T_COUNT_dual_7_repeat1) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,200);input_tb.cellTemperature_ddegC[0][0][7]=400;input_tr.cellTemperature_ddegC[0][0][7]=400;input_tb.nrValidTemperatures[0]=8; for(unsigned call=0;call<1;call++){input_tb.header.timestamp=1000+call;input_tr.header.timestamp=1000+call;test_tick=1000+call;EQ(MRC_ValidateCellTemperatureMeasurement(&input_tb,&input_tr),1);check_final_temperature_count();}EQ(mrc_tableCellTemperatures.nrValidTemperatures[0],7);EQ(mrc_tableMinimumMaximumValues.validMeasuredCellTemperatures[0],7);
}

/* ADD_T_COUNT_dual_7_repeat2: Final valid temperature count without accumulation. Requirements [10, 12, 14, 27]. */
PST_TEST(redundancy,ADD_T_COUNT_dual_7_repeat2) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,200);input_tb.cellTemperature_ddegC[0][0][7]=400;input_tr.cellTemperature_ddegC[0][0][7]=400;input_tb.nrValidTemperatures[0]=8; for(unsigned call=0;call<2;call++){input_tb.header.timestamp=1000+call;input_tr.header.timestamp=1000+call;test_tick=1000+call;EQ(MRC_ValidateCellTemperatureMeasurement(&input_tb,&input_tr),1);check_final_temperature_count();}EQ(mrc_tableCellTemperatures.nrValidTemperatures[0],7);EQ(mrc_tableMinimumMaximumValues.validMeasuredCellTemperatures[0],7);
}

/* ADD_T_COUNT_dual_0_repeat1: Final valid temperature count without accumulation. Requirements [10, 12, 14, 27]. */
PST_TEST(redundancy,ADD_T_COUNT_dual_0_repeat1) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,200);for(unsigned s=0;s<BS_NR_OF_STRINGS;s++)for(unsigned t=0;t<8;t++){input_tb.invalidCellTemperature[s][0][t]=1;input_tr.invalidCellTemperature[s][0][t]=1;}input_tb.nrValidTemperatures[0]=0; for(unsigned call=0;call<1;call++){input_tb.header.timestamp=1000+call;input_tr.header.timestamp=1000+call;test_tick=1000+call;EQ(MRC_ValidateCellTemperatureMeasurement(&input_tb,&input_tr),1);check_final_temperature_count();}EQ(mrc_tableCellTemperatures.nrValidTemperatures[0],0);EQ(mrc_tableMinimumMaximumValues.validMeasuredCellTemperatures[0],0);
}

/* ADD_T_COUNT_dual_0_repeat2: Final valid temperature count without accumulation. Requirements [10, 12, 14, 27]. */
PST_TEST(redundancy,ADD_T_COUNT_dual_0_repeat2) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&input_tb,200);fill_temperature(&input_tr,200);for(unsigned s=0;s<BS_NR_OF_STRINGS;s++)for(unsigned t=0;t<8;t++){input_tb.invalidCellTemperature[s][0][t]=1;input_tr.invalidCellTemperature[s][0][t]=1;}input_tb.nrValidTemperatures[0]=0; for(unsigned call=0;call<2;call++){input_tb.header.timestamp=1000+call;input_tr.header.timestamp=1000+call;test_tick=1000+call;EQ(MRC_ValidateCellTemperatureMeasurement(&input_tb,&input_tr),1);check_final_temperature_count();}EQ(mrc_tableCellTemperatures.nrValidTemperatures[0],0);EQ(mrc_tableMinimumMaximumValues.validMeasuredCellTemperatures[0],0);
}

/* ADD_V1_DIFF_2999: V1 tolerance is strict <3000. Requirements [16, 25]. */
PST_TEST(redundancy,ADD_V1_DIFF_2999) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&input_vb,3500); for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){input_v1.timestamp[s]=1000;input_v1.highVoltage_mV[s]=63000+2999;} MRC_ValidateStringVoltageMeasurement(&input_v1,&input_vb);EQ(mrc_tablePackValues.stringVoltage_mV[0],63000+2999);EQ(mrc_tablePackValues.invalidStringVoltage[0],0);EVENT(DIAG_ID_PLAUSIBILITY_PACK_VOLTAGE,DIAG_EVENT_OK,DIAG_STRING,0);
}

/* ADD_V1_DIFF_3000: V1 tolerance is strict <3000. Requirements [16, 25]. */
PST_TEST(redundancy,ADD_V1_DIFF_3000) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&input_vb,3500); for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){input_v1.timestamp[s]=1000;input_v1.highVoltage_mV[s]=63000+3000;} MRC_ValidateStringVoltageMeasurement(&input_v1,&input_vb);EQ(mrc_tablePackValues.stringVoltage_mV[0],63000+3000);EQ(mrc_tablePackValues.invalidStringVoltage[0],1);EVENT(DIAG_ID_PLAUSIBILITY_PACK_VOLTAGE,DIAG_EVENT_NOT_OK,DIAG_STRING,0);
}

/* ADD_V1_v1_only: v1_only. Requirements [16, 17]. */
PST_TEST(redundancy,ADD_V1_v1_only) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){input_v1.timestamp[s]=1000;input_v1.invalidMeasurement[s]=0;input_v1.highVoltage_mV[s]=50000;input_vb.nrValidCellVoltages[s]=0;input_vb.stringVoltage_mV[s]=0*3500;mrc_tableMinimumMaximumValues.averageCellVoltage_mV[s]=3500;}MRC_ValidateStringVoltageMeasurement(&input_v1,&input_vb);EQ(mrc_tablePackValues.stringVoltage_mV[0],50000);EQ(mrc_tablePackValues.invalidStringVoltage[0],0);
}

/* ADD_V1_afe_only_timeout: afe_only_timeout. Requirements [16, 17]. */
PST_TEST(redundancy,ADD_V1_afe_only_timeout) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){input_v1.timestamp[s]=699;input_v1.invalidMeasurement[s]=0;input_v1.highVoltage_mV[s]=50000;input_vb.nrValidCellVoltages[s]=18;input_vb.stringVoltage_mV[s]=18*3500;mrc_tableMinimumMaximumValues.averageCellVoltage_mV[s]=3500;}MRC_ValidateStringVoltageMeasurement(&input_v1,&input_vb);EQ(mrc_tablePackValues.stringVoltage_mV[0],63000);EQ(mrc_tablePackValues.invalidStringVoltage[0],0);
}

/* ADD_V1_afe_only_invalid: afe_only_invalid. Requirements [16, 17]. */
PST_TEST(redundancy,ADD_V1_afe_only_invalid) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){input_v1.timestamp[s]=1000;input_v1.invalidMeasurement[s]=1;input_v1.highVoltage_mV[s]=50000;input_vb.nrValidCellVoltages[s]=18;input_vb.stringVoltage_mV[s]=18*3500;mrc_tableMinimumMaximumValues.averageCellVoltage_mV[s]=3500;}MRC_ValidateStringVoltageMeasurement(&input_v1,&input_vb);EQ(mrc_tablePackValues.stringVoltage_mV[0],63000);EQ(mrc_tablePackValues.invalidStringVoltage[0],0);
}

/* ADD_V1_estimate5: estimate5. Requirements [16, 17]. */
PST_TEST(redundancy,ADD_V1_estimate5) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){input_v1.timestamp[s]=0;input_v1.invalidMeasurement[s]=1;input_v1.highVoltage_mV[s]=50000;input_vb.nrValidCellVoltages[s]=13;input_vb.stringVoltage_mV[s]=13*3500;mrc_tableMinimumMaximumValues.averageCellVoltage_mV[s]=3500;}MRC_ValidateStringVoltageMeasurement(&input_v1,&input_vb);EQ(mrc_tablePackValues.stringVoltage_mV[0],63000);EQ(mrc_tablePackValues.invalidStringVoltage[0],0);
}

/* ADD_V1_estimate6: estimate6. Requirements [16, 17]. */
PST_TEST(redundancy,ADD_V1_estimate6) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){input_v1.timestamp[s]=0;input_v1.invalidMeasurement[s]=1;input_v1.highVoltage_mV[s]=50000;input_vb.nrValidCellVoltages[s]=12;input_vb.stringVoltage_mV[s]=12*3500;mrc_tableMinimumMaximumValues.averageCellVoltage_mV[s]=3500;}MRC_ValidateStringVoltageMeasurement(&input_v1,&input_vb);EQ(mrc_tablePackValues.stringVoltage_mV[0],63000);EQ(mrc_tablePackValues.invalidStringVoltage[0],1);
}

/* ADD_CURRENT_new_valid: new_valid. Requirements [20, 21, 25]. */
PST_TEST(redundancy,ADD_CURRENT_new_valid) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){input_current.timestamp[s]=1000;input_current.current_mA[s]=1234;input_current.invalidMeasurement[s]=0;mrc_tablePackValues.stringCurrent_mA[s]=77;}MRC_ValidateCurrentMeasurement(&input_current);EQ(mrc_tablePackValues.stringCurrent_mA[0],1234);EQ(mrc_tablePackValues.invalidStringCurrent[0],0);EQ(mrc_tablePackValues.packCurrent_mA,1234*(int)BS_NR_OF_STRINGS);EQ(mrc_tablePackValues.invalidPackCurrent,0);
}

/* ADD_CURRENT_new_invalid: new_invalid. Requirements [20, 21, 25]. */
PST_TEST(redundancy,ADD_CURRENT_new_invalid) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){input_current.timestamp[s]=1000;input_current.current_mA[s]=1234;input_current.invalidMeasurement[s]=1;mrc_tablePackValues.stringCurrent_mA[s]=77;}MRC_ValidateCurrentMeasurement(&input_current);EQ(mrc_tablePackValues.stringCurrent_mA[0],1234);EQ(mrc_tablePackValues.invalidStringCurrent[0],1);EQ(mrc_tablePackValues.packCurrent_mA,0*(int)BS_NR_OF_STRINGS);EQ(mrc_tablePackValues.invalidPackCurrent,1);
}

/* ADD_CURRENT_same: same. Requirements [20, 21, 25]. */
PST_TEST(redundancy,ADD_CURRENT_same) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){input_current.timestamp[s]=1000;input_current.current_mA[s]=1234;input_current.invalidMeasurement[s]=0;mrc_tablePackValues.stringCurrent_mA[s]=77;mrc_state.lastStringCurrentTimestamp[s]=1000;}MRC_ValidateCurrentMeasurement(&input_current);EQ(mrc_tablePackValues.stringCurrent_mA[0],77);EQ(mrc_tablePackValues.invalidStringCurrent[0],0);EQ(mrc_tablePackValues.packCurrent_mA,77*(int)BS_NR_OF_STRINGS);EQ(mrc_tablePackValues.invalidPackCurrent,0);
}

/* ADD_CURRENT_timeout: timeout. Requirements [20, 21, 25]. */
PST_TEST(redundancy,ADD_CURRENT_timeout) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){input_current.timestamp[s]=749;input_current.current_mA[s]=1234;input_current.invalidMeasurement[s]=0;mrc_tablePackValues.stringCurrent_mA[s]=77;}MRC_ValidateCurrentMeasurement(&input_current);EQ(mrc_tablePackValues.stringCurrent_mA[0],77);EQ(mrc_tablePackValues.invalidStringCurrent[0],1);EQ(mrc_tablePackValues.packCurrent_mA,0*(int)BS_NR_OF_STRINGS);EQ(mrc_tablePackValues.invalidPackCurrent,1);
}

/* ADD_CURRENT_unmeasured: unmeasured. Requirements [20, 21, 25]. */
PST_TEST(redundancy,ADD_CURRENT_unmeasured) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){input_current.timestamp[s]=0;input_current.current_mA[s]=1234;input_current.invalidMeasurement[s]=0;mrc_tablePackValues.stringCurrent_mA[s]=77;}MRC_ValidateCurrentMeasurement(&input_current);EQ(mrc_tablePackValues.stringCurrent_mA[0],77);EQ(mrc_tablePackValues.invalidStringCurrent[0],1);EQ(mrc_tablePackValues.packCurrent_mA,0*(int)BS_NR_OF_STRINGS);EQ(mrc_tablePackValues.invalidPackCurrent,1);
}

/* ADD_POWER_sensor_priority: sensor_priority. Requirements [22, 23, 25, 28]. */
PST_TEST(redundancy,ADD_POWER_sensor_priority) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
power_inputs(1000,0,5000,50000,0,0,1);MRC_ValidatePowerMeasurement(&input_power);EQ(mrc_tablePackValues.stringPower_W[0],200);EQ(mrc_tablePackValues.invalidStringPower[0],0);EQ(mrc_tablePackValues.packPower_W,200*(int)BS_NR_OF_STRINGS);EQ(mrc_tablePackValues.invalidPackPower,0);EVENT(DIAG_ID_POWER_MEASUREMENT_ERROR,DIAG_EVENT_OK,DIAG_STRING,0);EVENT(DIAG_ID_CURRENT_SENSOR_POWER_MEASUREMENT_TIMEOUT,DIAG_EVENT_OK,DIAG_STRING,0);
}

/* ADD_POWER_fallback_positive: fallback_positive. Requirements [22, 23, 25, 28]. */
PST_TEST(redundancy,ADD_POWER_fallback_positive) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
power_inputs(1000,1,2000,50000,0,0,1);MRC_ValidatePowerMeasurement(&input_power);EQ(mrc_tablePackValues.stringPower_W[0],100);EQ(mrc_tablePackValues.invalidStringPower[0],0);EQ(mrc_tablePackValues.packPower_W,100*(int)BS_NR_OF_STRINGS);EQ(mrc_tablePackValues.invalidPackPower,0);EVENT(DIAG_ID_POWER_MEASUREMENT_ERROR,DIAG_EVENT_OK,DIAG_STRING,0);EVENT(DIAG_ID_CURRENT_SENSOR_POWER_MEASUREMENT_TIMEOUT,DIAG_EVENT_OK,DIAG_STRING,0);
}

/* ADD_POWER_fallback_negative: fallback_negative. Requirements [22, 23, 25, 28]. */
PST_TEST(redundancy,ADD_POWER_fallback_negative) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
power_inputs(1000,1,-2000,50000,0,0,1);MRC_ValidatePowerMeasurement(&input_power);EQ(mrc_tablePackValues.stringPower_W[0],-100);EQ(mrc_tablePackValues.invalidStringPower[0],0);EQ(mrc_tablePackValues.packPower_W,-100*(int)BS_NR_OF_STRINGS);EQ(mrc_tablePackValues.invalidPackPower,0);EVENT(DIAG_ID_POWER_MEASUREMENT_ERROR,DIAG_EVENT_OK,DIAG_STRING,0);EVENT(DIAG_ID_CURRENT_SENSOR_POWER_MEASUREMENT_TIMEOUT,DIAG_EVENT_OK,DIAG_STRING,0);
}

/* ADD_POWER_fallback_fraction: fallback_fraction. Requirements [22, 23, 25, 28]. */
PST_TEST(redundancy,ADD_POWER_fallback_fraction) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
power_inputs(1000,1,1234,12345,0,0,1);MRC_ValidatePowerMeasurement(&input_power);EQ(mrc_tablePackValues.stringPower_W[0],15);EQ(mrc_tablePackValues.invalidStringPower[0],0);EQ(mrc_tablePackValues.packPower_W,15*(int)BS_NR_OF_STRINGS);EQ(mrc_tablePackValues.invalidPackPower,0);EVENT(DIAG_ID_POWER_MEASUREMENT_ERROR,DIAG_EVENT_OK,DIAG_STRING,0);EVENT(DIAG_ID_CURRENT_SENSOR_POWER_MEASUREMENT_TIMEOUT,DIAG_EVENT_OK,DIAG_STRING,0);
}

/* ADD_POWER_fallback_fraction_negative: fallback_fraction_negative. Requirements [22, 23, 25, 28]. */
PST_TEST(redundancy,ADD_POWER_fallback_fraction_negative) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
power_inputs(1000,1,-1234,12345,0,0,1);MRC_ValidatePowerMeasurement(&input_power);EQ(mrc_tablePackValues.stringPower_W[0],-15);EQ(mrc_tablePackValues.invalidStringPower[0],0);EQ(mrc_tablePackValues.packPower_W,-15*(int)BS_NR_OF_STRINGS);EQ(mrc_tablePackValues.invalidPackPower,0);EVENT(DIAG_ID_POWER_MEASUREMENT_ERROR,DIAG_EVENT_OK,DIAG_STRING,0);EVENT(DIAG_ID_CURRENT_SENSOR_POWER_MEASUREMENT_TIMEOUT,DIAG_EVENT_OK,DIAG_STRING,0);
}

/* ADD_POWER_timeout_fallback: timeout_fallback. Requirements [22, 23, 25, 28]. */
PST_TEST(redundancy,ADD_POWER_timeout_fallback) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
power_inputs(699,0,2000,50000,0,0,1);MRC_ValidatePowerMeasurement(&input_power);EQ(mrc_tablePackValues.stringPower_W[0],100);EQ(mrc_tablePackValues.invalidStringPower[0],0);EQ(mrc_tablePackValues.packPower_W,100*(int)BS_NR_OF_STRINGS);EQ(mrc_tablePackValues.invalidPackPower,0);EVENT(DIAG_ID_POWER_MEASUREMENT_ERROR,DIAG_EVENT_OK,DIAG_STRING,0);EVENT(DIAG_ID_CURRENT_SENSOR_POWER_MEASUREMENT_TIMEOUT,DIAG_EVENT_NOT_OK,DIAG_STRING,0);
}

/* ADD_POWER_age300_sensor: age300_sensor. Requirements [22, 23, 25, 28]. */
PST_TEST(redundancy,ADD_POWER_age300_sensor) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
power_inputs(700,0,2000,50000,0,0,1);MRC_ValidatePowerMeasurement(&input_power);EQ(mrc_tablePackValues.stringPower_W[0],200);EQ(mrc_tablePackValues.invalidStringPower[0],0);EQ(mrc_tablePackValues.packPower_W,200*(int)BS_NR_OF_STRINGS);EQ(mrc_tablePackValues.invalidPackPower,0);EVENT(DIAG_ID_POWER_MEASUREMENT_ERROR,DIAG_EVENT_OK,DIAG_STRING,0);EVENT(DIAG_ID_CURRENT_SENSOR_POWER_MEASUREMENT_TIMEOUT,DIAG_EVENT_OK,DIAG_STRING,0);
}

/* ADD_POWER_unmeasured_fallback: unmeasured_fallback. Requirements [22, 23, 25, 28]. */
PST_TEST(redundancy,ADD_POWER_unmeasured_fallback) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
power_inputs(0,0,2000,50000,0,0,1);MRC_ValidatePowerMeasurement(&input_power);EQ(mrc_tablePackValues.stringPower_W[0],100);EQ(mrc_tablePackValues.invalidStringPower[0],0);EQ(mrc_tablePackValues.packPower_W,100*(int)BS_NR_OF_STRINGS);EQ(mrc_tablePackValues.invalidPackPower,0);EVENT(DIAG_ID_POWER_MEASUREMENT_ERROR,DIAG_EVENT_OK,DIAG_STRING,0);EVENT(DIAG_ID_CURRENT_SENSOR_POWER_MEASUREMENT_TIMEOUT,DIAG_EVENT_NOT_OK,DIAG_STRING,0);
}

/* ADD_POWER_invalid_no_current: invalid_no_current. Requirements [22, 23, 25, 28]. */
PST_TEST(redundancy,ADD_POWER_invalid_no_current) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
power_inputs(1000,1,2000,50000,1,0,0);MRC_ValidatePowerMeasurement(&input_power);EQ(mrc_tablePackValues.stringPower_W[0],100);EQ(mrc_tablePackValues.invalidStringPower[0],1);EQ(mrc_tablePackValues.packPower_W,0*(int)BS_NR_OF_STRINGS);EQ(mrc_tablePackValues.invalidPackPower,1);EVENT(DIAG_ID_POWER_MEASUREMENT_ERROR,DIAG_EVENT_NOT_OK,DIAG_STRING,0);EVENT(DIAG_ID_CURRENT_SENSOR_POWER_MEASUREMENT_TIMEOUT,DIAG_EVENT_OK,DIAG_STRING,0);
}

/* ADD_POWER_invalid_no_voltage: invalid_no_voltage. Requirements [22, 23, 25, 28]. */
PST_TEST(redundancy,ADD_POWER_invalid_no_voltage) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
power_inputs(1000,1,2000,50000,0,1,0);MRC_ValidatePowerMeasurement(&input_power);EQ(mrc_tablePackValues.stringPower_W[0],100);EQ(mrc_tablePackValues.invalidStringPower[0],1);EQ(mrc_tablePackValues.packPower_W,0*(int)BS_NR_OF_STRINGS);EQ(mrc_tablePackValues.invalidPackPower,1);EVENT(DIAG_ID_POWER_MEASUREMENT_ERROR,DIAG_EVENT_NOT_OK,DIAG_STRING,0);EVENT(DIAG_ID_CURRENT_SENSOR_POWER_MEASUREMENT_TIMEOUT,DIAG_EVENT_OK,DIAG_STRING,0);
}

/* ADD_POWER_timeout_no_fallback: timeout_no_fallback. Requirements [22, 23, 25, 28]. */
PST_TEST(redundancy,ADD_POWER_timeout_no_fallback) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
power_inputs(699,0,2000,50000,1,1,0);MRC_ValidatePowerMeasurement(&input_power);EQ(mrc_tablePackValues.stringPower_W[0],100);EQ(mrc_tablePackValues.invalidStringPower[0],1);EQ(mrc_tablePackValues.packPower_W,0*(int)BS_NR_OF_STRINGS);EQ(mrc_tablePackValues.invalidPackPower,1);EVENT(DIAG_ID_POWER_MEASUREMENT_ERROR,DIAG_EVENT_NOT_OK,DIAG_STRING,0);EVENT(DIAG_ID_CURRENT_SENSOR_POWER_MEASUREMENT_TIMEOUT,DIAG_EVENT_NOT_OK,DIAG_STRING,0);
}

/* ADD_POWER_same_invalid_recovery: Same invalid timestamp must reevaluate recovery. Requirements [28]. */
PST_TEST(redundancy,ADD_POWER_same_invalid_recovery) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */

power_inputs(1000,1,2000,50000,1,0,1);MRC_ValidatePowerMeasurement(&input_power);
for(unsigned s=0;s<BS_NR_OF_STRINGS;s++)mrc_tablePackValues.invalidStringCurrent[s]=0;
MRC_ValidatePowerMeasurement(&input_power);EQ(mrc_tablePackValues.stringPower_W[0],100);EQ(mrc_tablePackValues.invalidStringPower[0],0);EQ(mrc_tablePackValues.invalidPackPower,0);

}

/* ADD_POWER_same_invalid_loss: Same invalid timestamp must reevaluate loss of fallback. Requirements [28]. */
PST_TEST(redundancy,ADD_POWER_same_invalid_loss) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */

power_inputs(1000,1,2000,50000,0,0,1);MRC_ValidatePowerMeasurement(&input_power);
for(unsigned s=0;s<BS_NR_OF_STRINGS;s++)mrc_tablePackValues.invalidStringCurrent[s]=1;
MRC_ValidatePowerMeasurement(&input_power);EQ(mrc_tablePackValues.stringPower_W[0],100);EQ(mrc_tablePackValues.invalidStringPower[0],1);EQ(mrc_tablePackValues.packPower_W,0);EQ(mrc_tablePackValues.invalidPackPower,1);

}

/* ADD_BATTERY_none_connected: none_connected. Requirements [18]. */
PST_TEST(redundancy,ADD_BATTERY_none_connected) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){mrc_tablePackValues.stringVoltage_mV[s]=50000;mrc_tablePackValues.invalidStringVoltage[s]=0;closed[s]=0;}MRC_ValidateBatteryVoltageMeasurement();EQ(mrc_tablePackValues.batteryVoltage_mV,50000);EQ(mrc_tablePackValues.invalidBatteryVoltage,0);
}

/* ADD_BATTERY_connected: connected. Requirements [18]. */
PST_TEST(redundancy,ADD_BATTERY_connected) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){mrc_tablePackValues.stringVoltage_mV[s]=50000;mrc_tablePackValues.invalidStringVoltage[s]=0;closed[s]=1;}MRC_ValidateBatteryVoltageMeasurement();EQ(mrc_tablePackValues.batteryVoltage_mV,50000);EQ(mrc_tablePackValues.invalidBatteryVoltage,0);
}

/* ADD_BATTERY_no_valid: no_valid. Requirements [18]. */
PST_TEST(redundancy,ADD_BATTERY_no_valid) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){mrc_tablePackValues.stringVoltage_mV[s]=50000;mrc_tablePackValues.invalidStringVoltage[s]=1;closed[s]=0;}MRC_ValidateBatteryVoltageMeasurement();EQ(mrc_tablePackValues.batteryVoltage_mV,INT32_MAX);EQ(mrc_tablePackValues.invalidBatteryVoltage,1);
}

/* ADD_HV_closed: closed. Requirements [19]. */
PST_TEST(redundancy,ADD_HV_closed) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
mrc_tablePackValues.highVoltageBusVoltage_mV=77;for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){closed[s]=1;precharging[s]=0;input_v3.timestamp[s]=1000;input_v3.invalidMeasurement[s]=0;input_v3.highVoltage_mV[s]=50000;}MRC_ValidateHighVoltageBusMeasurement(&input_v3);EQ(mrc_tablePackValues.highVoltageBusVoltage_mV,50000);EQ(mrc_tablePackValues.invalidHvBusVoltage,0);
}

/* ADD_HV_precharge: precharge. Requirements [19]. */
PST_TEST(redundancy,ADD_HV_precharge) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
mrc_tablePackValues.highVoltageBusVoltage_mV=77;for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){closed[s]=0;precharging[s]=1;input_v3.timestamp[s]=1000;input_v3.invalidMeasurement[s]=0;input_v3.highVoltage_mV[s]=50000;}MRC_ValidateHighVoltageBusMeasurement(&input_v3);EQ(mrc_tablePackValues.highVoltageBusVoltage_mV,50000);EQ(mrc_tablePackValues.invalidHvBusVoltage,0);
}

/* ADD_HV_disconnected: disconnected. Requirements [19]. */
PST_TEST(redundancy,ADD_HV_disconnected) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
mrc_tablePackValues.highVoltageBusVoltage_mV=77;for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){closed[s]=0;precharging[s]=0;input_v3.timestamp[s]=1000;input_v3.invalidMeasurement[s]=0;input_v3.highVoltage_mV[s]=50000;}MRC_ValidateHighVoltageBusMeasurement(&input_v3);EQ(mrc_tablePackValues.highVoltageBusVoltage_mV,77);EQ(mrc_tablePackValues.invalidHvBusVoltage,1);
}

/* ADD_HV_timeout: timeout. Requirements [19]. */
PST_TEST(redundancy,ADD_HV_timeout) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
mrc_tablePackValues.highVoltageBusVoltage_mV=77;for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){closed[s]=1;precharging[s]=0;input_v3.timestamp[s]=699;input_v3.invalidMeasurement[s]=0;input_v3.highVoltage_mV[s]=50000;}MRC_ValidateHighVoltageBusMeasurement(&input_v3);EQ(mrc_tablePackValues.highVoltageBusVoltage_mV,77);EQ(mrc_tablePackValues.invalidHvBusVoltage,1);
}

/* ADD_HV_invalid: invalid. Requirements [19]. */
PST_TEST(redundancy,ADD_HV_invalid) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
mrc_tablePackValues.highVoltageBusVoltage_mV=77;for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){closed[s]=1;precharging[s]=0;input_v3.timestamp[s]=1000;input_v3.invalidMeasurement[s]=1;input_v3.highVoltage_mV[s]=50000;}MRC_ValidateHighVoltageBusMeasurement(&input_v3);EQ(mrc_tablePackValues.highVoltageBusVoltage_mV,77);EQ(mrc_tablePackValues.invalidHvBusVoltage,1);
}

/* ADD_PACK_current_voltage_before_power: Pack current and voltage precede fallback and DB write. Requirements [24, 25]. */
PST_TEST(redundancy,ADD_PACK_current_voltage_before_power) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */

for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){input_current.timestamp[s]=1000;input_current.current_mA[s]=2000;input_v1.timestamp[s]=1000;input_v1.highVoltage_mV[s]=50000;input_power.timestamp[s]=0;mrc_tablePackValues.stringCurrent_mA[s]=1;mrc_tablePackValues.stringVoltage_mV[s]=1;}
EQ(MRC_ValidatePackMeasurement(),STD_OK);EQ(read_calls,1);EQ(write_calls,1);EQ(written_ids[0],DATA_BLOCK_ID_PACK_VALUES);EQ(saved_pack.stringPower_W[0],100);EQ(saved_pack.packPower_W,100*BS_NR_OF_STRINGS);EQ(saved_pack.invalidPackPower,0);

}

/* ADD_PACK_invalid_returns_OK: Pack API returns OK with invalid measurements. Requirements [24]. */
PST_TEST(redundancy,ADD_PACK_invalid_returns_OK) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */

MRC_Initialize();write_calls=written_count=0;EQ(MRC_ValidatePackMeasurement(),STD_OK);EQ(write_calls,1);EQ(saved_pack.invalidPackCurrent,1);EQ(saved_pack.invalidPackPower,1);

}

/* ADD_SPREAD_V_300: Spread inclusive threshold around actual computed mean. Requirements [14, 25]. */
PST_TEST(redundancy,ADD_SPREAD_V_300) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&mrc_tableCellVoltages,3500);for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){mrc_tableCellVoltages.cellVoltage_mV[s][0][0]=3200;mrc_tableCellVoltages.cellVoltage_mV[s][0][1]=3800;}EQ(MRC_CalculateCellVoltageMinMaxAverage(&mrc_tableCellVoltages,&mrc_tableMinimumMaximumValues),STD_OK);EQ(PL_CheckVoltageSpread(&mrc_tableCellVoltages,&mrc_tableMinimumMaximumValues),0);EQ(mrc_tableCellVoltages.invalidCellVoltage[0][0][0],0);EQ(mrc_tableCellVoltages.invalidCellVoltage[0][0][1],0);
}

/* ADD_SPREAD_V_301: Spread inclusive threshold around actual computed mean. Requirements [14, 25]. */
PST_TEST(redundancy,ADD_SPREAD_V_301) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_voltage(&mrc_tableCellVoltages,3500);for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){mrc_tableCellVoltages.cellVoltage_mV[s][0][0]=3199;mrc_tableCellVoltages.cellVoltage_mV[s][0][1]=3801;}EQ(MRC_CalculateCellVoltageMinMaxAverage(&mrc_tableCellVoltages,&mrc_tableMinimumMaximumValues),STD_OK);EQ(PL_CheckVoltageSpread(&mrc_tableCellVoltages,&mrc_tableMinimumMaximumValues),1);EQ(mrc_tableCellVoltages.invalidCellVoltage[0][0][0],1);EQ(mrc_tableCellVoltages.invalidCellVoltage[0][0][1],1);
}

/* ADD_SPREAD_V_recompute_once: After removal statistics recalculate once, no repeated spread pass. Requirements [14]. */
PST_TEST(redundancy,ADD_SPREAD_V_recompute_once) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){for(unsigned c=0;c<18;c++){input_vb.invalidCellVoltage[s][0][c]=1;input_vr.invalidCellVoltage[s][0][c]=1;}int values[8]={0,540,900,900,900,900,900,900};for(unsigned c=0;c<8;c++){input_vb.invalidCellVoltage[s][0][c]=0;input_vr.invalidCellVoltage[s][0][c]=0;input_vb.cellVoltage_mV[s][0][c]=values[c];input_vr.cellVoltage_mV[s][0][c]=values[c];}}input_vb.header.timestamp=input_vr.header.timestamp=1000;EQ(MRC_ValidateCellVoltageMeasurement(&input_vb,&input_vr),1);EQ(mrc_tableCellVoltages.invalidCellVoltage[0][0][0],1);EQ(mrc_tableCellVoltages.invalidCellVoltage[0][0][1],0);PST_VERIFY_EQ_APPROX_FLT(mrc_tableMinimumMaximumValues.averageCellVoltage_mV[0],848,0.001);
}

/* ADD_SPREAD_T_100: Spread inclusive threshold around actual computed mean. Requirements [14, 25]. */
PST_TEST(redundancy,ADD_SPREAD_T_100) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&mrc_tableCellTemperatures,200);for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){mrc_tableCellTemperatures.cellTemperature_ddegC[s][0][0]=100;mrc_tableCellTemperatures.cellTemperature_ddegC[s][0][1]=300;}EQ(MRC_CalculateCellTemperatureMinMaxAverage(&mrc_tableCellTemperatures,&mrc_tableMinimumMaximumValues),STD_OK);EQ(PL_CheckTemperatureSpread(&mrc_tableCellTemperatures,&mrc_tableMinimumMaximumValues),0);EQ(mrc_tableCellTemperatures.invalidCellTemperature[0][0][0],0);EQ(mrc_tableCellTemperatures.invalidCellTemperature[0][0][1],0);
}

/* ADD_SPREAD_T_101: Spread inclusive threshold around actual computed mean. Requirements [14, 25]. */
PST_TEST(redundancy,ADD_SPREAD_T_101) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
fill_temperature(&mrc_tableCellTemperatures,200);for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){mrc_tableCellTemperatures.cellTemperature_ddegC[s][0][0]=99;mrc_tableCellTemperatures.cellTemperature_ddegC[s][0][1]=301;}EQ(MRC_CalculateCellTemperatureMinMaxAverage(&mrc_tableCellTemperatures,&mrc_tableMinimumMaximumValues),STD_OK);EQ(PL_CheckTemperatureSpread(&mrc_tableCellTemperatures,&mrc_tableMinimumMaximumValues),1);EQ(mrc_tableCellTemperatures.invalidCellTemperature[0][0][0],1);EQ(mrc_tableCellTemperatures.invalidCellTemperature[0][0][1],1);
}

/* ADD_SPREAD_T_recompute_once: After removal statistics recalculate once, no repeated spread pass. Requirements [14]. */
PST_TEST(redundancy,ADD_SPREAD_T_recompute_once) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */
for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){for(unsigned c=0;c<8;c++){input_tb.invalidCellTemperature[s][0][c]=1;input_tr.invalidCellTemperature[s][0][c]=1;}int values[8]={0,180,300,300,300,300,300,300};for(unsigned c=0;c<8;c++){input_tb.invalidCellTemperature[s][0][c]=0;input_tr.invalidCellTemperature[s][0][c]=0;input_tb.cellTemperature_ddegC[s][0][c]=values[c];input_tr.cellTemperature_ddegC[s][0][c]=values[c];}}input_tb.header.timestamp=input_tr.header.timestamp=1000;EQ(MRC_ValidateCellTemperatureMeasurement(&input_tb,&input_tr),1);EQ(mrc_tableCellTemperatures.invalidCellTemperature[0][0][0],1);EQ(mrc_tableCellTemperatures.invalidCellTemperature[0][0][1],0);PST_VERIFY_EQ_APPROX_FLT(mrc_tableMinimumMaximumValues.averageTemperature_ddegC[0],282.85714285714283,0.001);
}

/* ADD_STATS_T_fraction: Temperature float mean retains half unit. Requirements [12]. */
PST_TEST(redundancy,ADD_STATS_T_fraction) {
 /* Setup independent state. */ reset_all();
 /* Act on SUT and verify the requirement oracle. */

for(unsigned s=0;s<BS_NR_OF_STRINGS;s++){for(unsigned t=0;t<8;t++)mrc_tableCellTemperatures.invalidCellTemperature[s][0][t]=1;mrc_tableCellTemperatures.invalidCellTemperature[s][0][0]=mrc_tableCellTemperatures.invalidCellTemperature[s][0][1]=0;mrc_tableCellTemperatures.cellTemperature_ddegC[s][0][0]=200;mrc_tableCellTemperatures.cellTemperature_ddegC[s][0][1]=201;}
EQ(MRC_CalculateCellTemperatureMinMaxAverage(&mrc_tableCellTemperatures,&mrc_tableMinimumMaximumValues),STD_OK);PST_VERIFY_EQ_APPROX_FLT(mrc_tableMinimumMaximumValues.averageTemperature_ddegC[0],200.5,0.0001);

}
