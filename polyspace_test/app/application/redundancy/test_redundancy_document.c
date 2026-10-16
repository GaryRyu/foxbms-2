/* Requirement-based unit tests. Static source access explicitly authorized. */
#include "application_contract.h"
#include "../../../../src/app/application/redundancy/redundancy.c"

PST_SUITE(redundancy_redundancy);
/* F2-LLR-ALG-080-TC-01-01 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_01_01) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

PST_EQ(MRC_MeasurementUpdatedAtLeastOnce(10u,0u),true);
}

/* F2-LLR-ALG-080-TC-01-02 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_01_02) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

PST_EQ(MRC_MeasurementUpdatedAtLeastOnce(60u,10u),true);
}

/* F2-LLR-ALG-080-TC-01-03 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_01_03) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

PST_EQ(MRC_MeasurementUpdatedAtLeastOnce(70u,60u),true);
}

/* F2-LLR-ALG-080-TC-01-04 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_01_04) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

PST_EQ(MRC_MeasurementUpdatedAtLeastOnce(0u,0u),false);
}

/* F2-LLR-ALG-080-TC-02-01 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_02_01) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

pst_tick=100u;
PST_EQ(MRC_MeasurementUpdatedRecently(50u,0u,100u),STD_OK);
}

/* F2-LLR-ALG-080-TC-02-02 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_02_02) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

pst_tick=100u;
PST_EQ(MRC_MeasurementUpdatedRecently(0u,0u,100u),STD_NOT_OK);
}

/* F2-LLR-ALG-080-TC-02-03 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_02_03) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

pst_tick=101u;
PST_EQ(MRC_MeasurementUpdatedRecently(0u,0u,100u),STD_NOT_OK);
}

/* F2-LLR-ALG-080-TC-02-04 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_02_04) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

pst_tick=5000u;
PST_EQ(MRC_MeasurementUpdatedRecently(4937u,0u,100u),STD_OK);
}

/* F2-LLR-ALG-080-TC-02-05 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_02_05) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

pst_tick=50u;
PST_EQ(MRC_MeasurementUpdatedRecently(4294967295u,0u,100u),STD_OK);
}

/* F2-LLR-ALG-080-TC-02-06 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_02_06) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

pst_tick=49u;
PST_EQ(MRC_MeasurementUpdatedRecently(4294967245u,0u,100u),STD_OK);
}

/* F2-LLR-ALG-080-TC-02-07 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_02_07) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

pst_tick=50u;
PST_EQ(MRC_MeasurementUpdatedRecently(4294967245u,0u,100u),STD_NOT_OK);
}

/* F2-LLR-ALG-080-TC-02-08 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_02_08) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

pst_tick=4294967295u;
PST_EQ(MRC_MeasurementUpdatedRecently(50u,0u,100u),STD_NOT_OK);
}

/* F2-LLR-ALG-080-TC-03-01 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_03_01) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

DATA_BLOCK_MIN_MAX_s dummy0={0};
PST_EXPECT_SUT_ASSERT(MRC_CalculateCellVoltageMinMaxAverage(NULL_PTR,&dummy0),786);
}

/* F2-LLR-ALG-080-TC-03-02 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_03_02) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

DATA_BLOCK_CELL_VOLTAGE_s dummy1={0};
PST_EXPECT_SUT_ASSERT(MRC_CalculateCellVoltageMinMaxAverage(&dummy1,NULL_PTR),787);
}

/* F2-LLR-ALG-080-TC-04-01 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_04_01) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

DATA_BLOCK_MIN_MAX_s dummy0={0};
PST_EXPECT_SUT_ASSERT(MRC_CalculateCellTemperatureMinMaxAverage(NULL_PTR,&dummy0),844);
}

/* F2-LLR-ALG-080-TC-04-02 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_04_02) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

DATA_BLOCK_CELL_TEMPERATURE_s dummy1={0};
PST_EXPECT_SUT_ASSERT(MRC_CalculateCellTemperatureMinMaxAverage(&dummy1,NULL_PTR),845);
}

/* F2-LLR-ALG-080-TC-05-01 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_05_01) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

DATA_BLOCK_CELL_VOLTAGE_s dummy={0};
PST_EXPECT_SUT_ASSERT(MRC_ValidateCellVoltage(NULL_PTR,&dummy,&dummy),903);
}

/* F2-LLR-ALG-080-TC-05-02 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_05_02) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

DATA_BLOCK_CELL_VOLTAGE_s dummy={0};
PST_EXPECT_SUT_ASSERT(MRC_ValidateCellVoltage(&dummy,NULL_PTR,&dummy),904);
}

/* F2-LLR-ALG-080-TC-05-03 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_05_03) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

DATA_BLOCK_CELL_VOLTAGE_s dummy={0};
PST_EXPECT_SUT_ASSERT(MRC_ValidateCellVoltage(&dummy,&dummy,NULL_PTR),905);
}

/* F2-LLR-ALG-080-TC-06-01 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_06_01) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

DATA_BLOCK_CELL_VOLTAGE_s dummy={0};
PST_EXPECT_SUT_ASSERT(MRC_UpdateCellVoltageValidation(NULL_PTR,&dummy),976);
}

/* F2-LLR-ALG-080-TC-06-02 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_06_02) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

DATA_BLOCK_CELL_VOLTAGE_s dummy={0};
PST_EXPECT_SUT_ASSERT(MRC_UpdateCellVoltageValidation(&dummy,NULL_PTR),977);
}

/* F2-LLR-ALG-080-TC-07-01 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_07_01) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

DATA_BLOCK_CELL_TEMPERATURE_s dummy={0};
PST_EXPECT_SUT_ASSERT(MRC_ValidateCellTemperature(NULL_PTR,&dummy,&dummy),994);
}

/* F2-LLR-ALG-080-TC-07-02 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_07_02) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

DATA_BLOCK_CELL_TEMPERATURE_s dummy={0};
PST_EXPECT_SUT_ASSERT(MRC_ValidateCellTemperature(&dummy,NULL_PTR,&dummy),995);
}

/* F2-LLR-ALG-080-TC-07-03 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_07_03) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

DATA_BLOCK_CELL_TEMPERATURE_s dummy={0};
PST_EXPECT_SUT_ASSERT(MRC_ValidateCellTemperature(&dummy,&dummy,NULL_PTR),996);
}

/* F2-LLR-ALG-080-TC-08-01 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_08_01) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

DATA_BLOCK_CELL_TEMPERATURE_s dummy={0};
PST_EXPECT_SUT_ASSERT(MRC_UpdateCellTemperatureValidation(NULL_PTR,&dummy),1068);
}

/* F2-LLR-ALG-080-TC-08-02 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_08_02) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

DATA_BLOCK_CELL_TEMPERATURE_s dummy={0};
PST_EXPECT_SUT_ASSERT(MRC_UpdateCellTemperatureValidation(&dummy,NULL_PTR),1069);
}

/* F2-LLR-ALG-080-TC-09 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_09) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

pst_tick=0u;
MRC_STATE_s state_before=mrc_state;DATA_BLOCK_CELL_VOLTAGE_s v_before=mrc_tableCellVoltages;DATA_BLOCK_CELL_TEMPERATURE_s t_before=mrc_tableCellTemperatures;DATA_BLOCK_MIN_MAX_s mm_before=mrc_tableMinimumMaximumValues;
PST_EQ(MRC_ValidateAfeMeasurement(),STD_NOT_OK);PST_EQ(pst_writes,0);PST_EQ(pst_reads,4);
PST_EQ(memcmp(&mrc_state,&state_before,sizeof(state_before)),0);PST_EQ(memcmp(&mrc_tableCellVoltages,&v_before,sizeof(v_before)),0);PST_EQ(memcmp(&mrc_tableCellTemperatures,&t_before,sizeof(t_before)),0);PST_EQ(memcmp(&mrc_tableMinimumMaximumValues,&mm_before,sizeof(mm_before)),0);
pst_check_event(0,DIAG_ID_BASE_CELL_VOLTAGE_MEASUREMENT_TIMEOUT,DIAG_EVENT_NOT_OK,DIAG_SYSTEM,0);
pst_check_event(1,DIAG_ID_REDUNDANCY0_CELL_VOLTAGE_MEASUREMENT_TIMEOUT,DIAG_EVENT_OK,DIAG_SYSTEM,0);
pst_check_event(2,DIAG_ID_BASE_CELL_TEMPERATURE_MEASUREMENT_TIMEOUT,DIAG_EVENT_NOT_OK,DIAG_SYSTEM,0);
pst_check_event(3,DIAG_ID_REDUNDANCY0_CELL_TEMPERATURE_MEASUREMENT_TIMEOUT,DIAG_EVENT_OK,DIAG_SYSTEM,0);PST_EQ(pst_event_count,4);
}

/* F2-LLR-ALG-080-TC-10-01 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_10_01) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

DATA_BLOCK_CELL_VOLTAGE_s testCellVoltageRedundancy0={0};
PST_EXPECT_SUT_ASSERT(MRC_ValidateCellVoltageMeasurement(NULL_PTR,&testCellVoltageRedundancy0),279);
}

/* F2-LLR-ALG-080-TC-10-02 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_TC_10_02) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

DATA_BLOCK_CELL_VOLTAGE_s testCellVoltageBase={0};
PST_EXPECT_SUT_ASSERT(MRC_ValidateCellVoltageMeasurement(&testCellVoltageBase,NULL_PTR),280);
}

/* F2-LLR-ALG-080-11-ADD-001: min2900/max3100/average3000; full valid count */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_11_ADD_001) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

DATA_BLOCK_CELL_VOLTAGE_s v={0};DATA_BLOCK_MIN_MAX_s m={0};
for(unsigned i=0;i<BS_NR_OF_CELL_BLOCKS_PER_MODULE;i++)v.cellVoltage_mV[0][0][i]=3000;
v.cellVoltage_mV[0][0][0]=2900;v.cellVoltage_mV[0][0][1]=3100;
PST_EQ(MRC_CalculateCellVoltageMinMaxAverage(&v,&m),STD_OK);PST_EQ(m.minimumCellVoltage_mV[0],2900);PST_EQ(m.maximumCellVoltage_mV[0],3100);PST_EQ(m.averageCellVoltage_mV[0],3000);PST_EQ(m.validMeasuredCellVoltages[0],BS_NR_OF_CELL_BLOCKS_PER_STRING);
}

/* F2-LLR-ALG-080-12-ADD-001: min100/max300/mean200 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_12_ADD_001) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

DATA_BLOCK_CELL_TEMPERATURE_s t={0};DATA_BLOCK_MIN_MAX_s m={0};
for(unsigned i=0;i<BS_NR_OF_TEMP_SENSORS_PER_MODULE;i++)t.cellTemperature_ddegC[0][0][i]=200;
t.cellTemperature_ddegC[0][0][0]=100;t.cellTemperature_ddegC[0][0][1]=300;
PST_EQ(MRC_CalculateCellTemperatureMinMaxAverage(&t,&m),STD_OK);PST_EQ(m.minimumTemperature_ddegC[0],100);PST_EQ(m.maximumTemperature_ddegC[0],300);PST_EQ(m.averageTemperature_ddegC[0],200);
}

/* F2-LLR-ALG-080-13-ADD-001: STD_NOT_OK; sentinel extrema; average/count0 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_13_ADD_001) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;
DATA_BLOCK_CELL_VOLTAGE_s input={0};memset(&input.invalidCellVoltage,1,sizeof(input.invalidCellVoltage));DATA_BLOCK_MIN_MAX_s output={0};
PST_EQ(MRC_CalculateCellVoltageMinMaxAverage(&input,&output),STD_NOT_OK);PST_EQ(output.minimumCellVoltage_mV[0],INT16_MAX);PST_EQ(output.maximumCellVoltage_mV[0],INT16_MIN);PST_EQ(output.averageCellVoltage_mV[0],0);PST_EQ(output.validMeasuredCellVoltages[0],0);
}

/* F2-LLR-ALG-080-13-ADD-002: STD_NOT_OK; sentinel extrema; average/count0 */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_13_ADD_002) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;
DATA_BLOCK_CELL_TEMPERATURE_s input={0};memset(&input.invalidCellTemperature,1,sizeof(input.invalidCellTemperature));DATA_BLOCK_MIN_MAX_s output={0};
PST_EQ(MRC_CalculateCellTemperatureMinMaxAverage(&input,&output),STD_NOT_OK);PST_EQ(output.minimumTemperature_ddegC[0],INT16_MAX);PST_EQ(output.maximumTemperature_ddegC[0],INT16_MIN);PST_EQ(output.averageTemperature_ddegC[0],0);PST_EQ(output.validMeasuredCellTemperatures[0],0);
}

/* F2-LLR-ALG-080-28-ADD-001: 77 retained; invalidStringPower1; packPower0 invalid */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_28_ADD_001) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

DATA_BLOCK_POWER_s p={0};p.timestamp[0]=1;p.invalidMeasurement[0]=1;pst_tick=1;mrc_tablePackValues.stringPower_W[0]=77;mrc_tablePackValues.invalidStringPower[0]=0;mrc_tablePackValues.invalidStringCurrent[0]=1;mrc_tablePackValues.invalidStringVoltage[0]=0;
MRC_ValidatePowerMeasurement(&p);PST_EQ(mrc_tablePackValues.stringPower_W[0],77);PST_EQ(mrc_tablePackValues.invalidStringPower[0],1);PST_EQ(mrc_tablePackValues.packPower_W,0);PST_EQ(mrc_tablePackValues.invalidPackPower,1);
}

/* F2-LLR-ALG-080-22-ADD-001: valid -6W */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_22_ADD_001) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;

DATA_BLOCK_POWER_s p={0};p.timestamp[0]=1;p.invalidMeasurement[0]=1;pst_tick=1;mrc_tablePackValues.stringCurrent_mA[0]=-2000;mrc_tablePackValues.stringVoltage_mV[0]=3000;
MRC_ValidatePowerMeasurement(&p);PST_EQ(mrc_tablePackValues.stringPower_W[0],-6);PST_EQ(mrc_tablePackValues.invalidStringPower[0],0);PST_EQ(mrc_tablePackValues.packPower_W,-6);
}

/* F2-LLR-ALG-080-01-ADD-001: all AFE/Pack invalid;3 DB writes;STD_OK */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_01_ADD_001) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));
extern STD_RETURN_TYPE_e pst_rdn_write_result;pst_rdn_write_result=STD_OK;PST_EQ(MRC_Initialize(),STD_OK);PST_EQ(pst_writes,3);
for(unsigned s=0;s<BS_NR_OF_STRINGS;s++) {PST_EQ(mrc_tableCellVoltages.invalidStringVoltage[s],true);PST_EQ(mrc_tablePackValues.invalidStringVoltage[s],1);PST_EQ(mrc_tablePackValues.invalidStringCurrent[s],1);PST_EQ(mrc_tablePackValues.invalidStringPower[s],1);
for(unsigned m=0;m<BS_NR_OF_MODULES_PER_STRING;m++){PST_EQ(mrc_tableCellVoltages.invalidModuleVoltage[s][m],true);for(unsigned c=0;c<BS_NR_OF_CELL_BLOCKS_PER_MODULE;c++)PST_EQ(mrc_tableCellVoltages.invalidCellVoltage[s][m][c],true);for(unsigned t=0;t<BS_NR_OF_TEMP_SENSORS_PER_MODULE;t++)PST_EQ(mrc_tableCellTemperatures.invalidCellTemperature[s][m][t],true);}}
PST_EQ(mrc_tablePackValues.invalidPackCurrent,1);PST_EQ(mrc_tablePackValues.invalidPackPower,1);PST_EQ(mrc_tablePackValues.invalidBatteryVoltage,1);PST_EQ(mrc_tablePackValues.invalidHvBusVoltage,1);
}

/* F2-LLR-ALG-080-03-ADD-001: STD_NOT_OK */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_03_ADD_001) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));extern STD_RETURN_TYPE_e pst_rdn_write_result;pst_rdn_write_result=STD_NOT_OK;PST_EQ(MRC_Initialize(),STD_NOT_OK);PST_EQ(pst_writes,3);pst_rdn_write_result=STD_OK;
}

/* F2-LLR-ALG-080-07-ADD-001: copy payload; preserve output header */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_07_ADD_001) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));DATA_BLOCK_CELL_VOLTAGE_s a={0},b={0};a.cellVoltage_mV[0][0][0]=123;a.header.timestamp=99;b.header.timestamp=42;DATA_BLOCK_HEADER_s old=b.header;PST_EQ(MRC_UpdateCellVoltageValidation(&a,&b),STD_OK);PST_EQ(b.cellVoltage_mV[0][0][0],123);PST_EQ(memcmp(&b.header,&old,sizeof(old)),0);
}

/* F2-LLR-ALG-080-07-ADD-002: copy payload; preserve output header */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_07_ADD_002) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));DATA_BLOCK_CELL_TEMPERATURE_s a={0},b={0};a.cellTemperature_ddegC[0][0][0]=123;a.header.timestamp=99;b.header.timestamp=42;DATA_BLOCK_HEADER_s old=b.header;PST_EQ(MRC_UpdateCellTemperatureValidation(&a,&b),STD_OK);PST_EQ(b.cellTemperature_ddegC[0][0][0],123);PST_EQ(memcmp(&b.header,&old,sizeof(old)),0);
}

/* F2-LLR-ALG-080-10-ADD-001: valid count=N; sum=N*3000;STD_OK */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_10_ADD_001) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));
DATA_BLOCK_CELL_VOLTAGE_s a={0},b={0},out={0};memset(&b.invalidCellVoltage,1,sizeof(b.invalidCellVoltage));for(unsigned s=0;s<BS_NR_OF_STRINGS;s++)for(unsigned m=0;m<BS_NR_OF_MODULES_PER_STRING;m++)for(unsigned c=0;c<BS_NR_OF_CELL_BLOCKS_PER_MODULE;c++)a.cellVoltage_mV[s][m][c]=3000;
PST_EQ(MRC_ValidateCellVoltage(&a,&b,&out),STD_OK);PST_EQ(out.nrValidCellVoltages[0],BS_NR_OF_CELL_BLOCKS_PER_STRING);PST_EQ(out.stringVoltage_mV[0],3000*BS_NR_OF_CELL_BLOCKS_PER_STRING);PST_EQ(out.cellVoltage_mV[0][0][0],3000);
}

/* F2-LLR-ALG-080-09-ADD-001: STD_OK;temperature200;countN */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_09_ADD_001) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));
DATA_BLOCK_CELL_TEMPERATURE_s a={0},b={0},out={0};memset(&a.invalidCellTemperature,1,sizeof(a.invalidCellTemperature));for(unsigned s=0;s<BS_NR_OF_STRINGS;s++)for(unsigned m=0;m<BS_NR_OF_MODULES_PER_STRING;m++)for(unsigned t=0;t<BS_NR_OF_TEMP_SENSORS_PER_MODULE;t++)b.cellTemperature_ddegC[s][m][t]=200;
PST_EQ(MRC_ValidateCellTemperature(&a,&b,&out),STD_OK);PST_EQ(out.nrValidTemperatures[0],BS_NR_OF_TEMP_SENSORS_PER_STRING);PST_EQ(out.cellTemperature_ddegC[0][0][0],200);
}

/* F2-LLR-ALG-080-20-ADD-001: string/pack1000mA valid */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_20_ADD_001) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));DATA_BLOCK_CURRENT_s c={0};c.timestamp[0]=1;c.current_mA[0]=1000;pst_tick=1;MRC_ValidateCurrentMeasurement(&c);PST_EQ(mrc_tablePackValues.stringCurrent_mA[0],1000);PST_EQ(mrc_tablePackValues.packCurrent_mA,1000);PST_EQ(mrc_tablePackValues.invalidPackCurrent,0);
}

/* F2-LLR-ALG-080-16-ADD-001: string54000 valid */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_16_ADD_001) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));DATA_BLOCK_SYSTEM_VOLTAGE_1_s v={0};DATA_BLOCK_CELL_VOLTAGE_s a={0};a.nrValidCellVoltages[0]=BS_NR_OF_CELL_BLOCKS_PER_STRING;a.stringVoltage_mV[0]=54000;MRC_ValidateStringVoltageMeasurement(&v,&a);PST_EQ(mrc_tablePackValues.stringVoltage_mV[0],54000);PST_EQ(mrc_tablePackValues.invalidStringVoltage[0],0);
}

/* F2-LLR-ALG-080-17-ADD-001: estimated54000 valid */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_17_ADD_001) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));DATA_BLOCK_SYSTEM_VOLTAGE_1_s v={0};DATA_BLOCK_CELL_VOLTAGE_s a={0};a.nrValidCellVoltages[0]=BS_NR_OF_CELL_BLOCKS_PER_STRING-5;a.stringVoltage_mV[0]=3000*(BS_NR_OF_CELL_BLOCKS_PER_STRING-5);mrc_tableMinimumMaximumValues.averageCellVoltage_mV[0]=3000;MRC_ValidateStringVoltageMeasurement(&v,&a);PST_EQ(mrc_tablePackValues.stringVoltage_mV[0],3000*BS_NR_OF_CELL_BLOCKS_PER_STRING);PST_EQ(mrc_tablePackValues.invalidStringVoltage[0],0);
}

/* F2-LLR-ALG-080-18-ADD-001: battery54000 valid */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_18_ADD_001) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tablePackValues.stringVoltage_mV[0]=54000;MRC_ValidateBatteryVoltageMeasurement();PST_EQ(mrc_tablePackValues.batteryVoltage_mV,54000);PST_EQ(mrc_tablePackValues.invalidBatteryVoltage,0);
}

/* F2-LLR-ALG-080-19-ADD-001: HV54000 valid */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_19_ADD_001) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));DATA_BLOCK_SYSTEM_VOLTAGE_3_s v={0};v.timestamp[0]=1;v.highVoltage_mV[0]=54000;pst_tick=1;pst_closed=true;MRC_ValidateHighVoltageBusMeasurement(&v);PST_EQ(mrc_tablePackValues.highVoltageBusVoltage_mV,54000);PST_EQ(mrc_tablePackValues.invalidHvBusVoltage,0);
}

/* F2-LLR-ALG-080-23-ADD-001: Pack includes valid disconnected power */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_23_ADD_001) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));DATA_BLOCK_POWER_s p={0};p.timestamp[0]=1;p.power_W[0]=100;pst_tick=1;pst_closed=false;MRC_ValidatePowerMeasurement(&p);PST_EQ(mrc_tablePackValues.packPower_W,100);PST_EQ(mrc_tablePackValues.invalidPackPower,0);
}

/* F2-LLR-ALG-080-27-ADD-001: final count matches statistics and configured limit */
PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_27_ADD_001) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));DATA_BLOCK_CELL_TEMPERATURE_s a={0},b={0},out={0};memset(&a.invalidCellTemperature,1,sizeof(a.invalidCellTemperature));for(unsigned t=0;t<BS_NR_OF_TEMP_SENSORS_PER_MODULE;t++)b.cellTemperature_ddegC[0][0][t]=200;PST_EQ(MRC_ValidateCellTemperature(&a,&b,&out),STD_OK);DATA_BLOCK_MIN_MAX_s m={0};PST_EQ(MRC_CalculateCellTemperatureMinMaxAverage(&out,&m),STD_OK);PST_EQ(out.nrValidTemperatures[0],m.validMeasuredCellTemperatures[0]);PST_EQ(out.nrValidTemperatures[0],BS_NR_OF_TEMP_SENSORS_PER_STRING);
}

PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_14_ADD_001) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));extern int pst_rdn_spread_fixture;extern unsigned pst_rdn_spread_calls;pst_rdn_spread_fixture=1;pst_rdn_spread_calls=0;
DATA_BLOCK_CELL_VOLTAGE_s a={0},b={0};a.header.timestamp=1;for(unsigned c=0;c<BS_NR_OF_CELL_BLOCKS_PER_MODULE;c++)a.cellVoltage_mV[0][0][c]=3000;a.cellVoltage_mV[0][0][0]=3400;pst_tick=1;
PST_EQ(MRC_ValidateCellVoltageMeasurement(&a,&b),true);PST_EQ(pst_rdn_spread_calls,1);PST_EQ(mrc_tableMinimumMaximumValues.averageCellVoltage_mV[0],3000);PST_EQ(mrc_tableMinimumMaximumValues.validMeasuredCellVoltages[0],BS_NR_OF_CELL_BLOCKS_PER_STRING-1);pst_rdn_spread_fixture=0;
}

PST_TEST(redundancy_redundancy,F2_LLR_ALG_080_24_ADD_001) {
pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));extern int pst_rdn_pack_fixture;pst_rdn_pack_fixture=1;PST_EQ(MRC_ValidatePackMeasurement(),STD_OK);PST_EQ(pst_reads,4);PST_EQ(pst_writes,1);PST_EQ(mrc_tablePackValues.invalidPackCurrent,1);PST_EQ(mrc_tablePackValues.invalidPackPower,1);pst_rdn_pack_fixture=0;
}
