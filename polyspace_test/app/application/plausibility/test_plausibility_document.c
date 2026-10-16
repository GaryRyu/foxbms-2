/* DOCX 4.1--4.11 PSTUnit; production unchanged. */
#include "application_contract.h"
#include "../../../../src/app/application/plausibility/plausibility.c"
PST_SUITE(plausibility_plausibility);
/* F2-LLR-ALG-070-TC-01: original Inputs/Expected, independent fixture. */
PST_TEST(plausibility_plausibility,F2_LLR_ALG_070_TC_01) {
    pst_reset_contract();
    int32_t packVoltage_mV = 0;
    int32_t highVoltage_mV = 0;
    PST_EQ(PL_CheckStringVoltage(0,0),STD_OK);
}

/* F2-LLR-ALG-070-TC-02: original Inputs/Expected, independent fixture. */
PST_TEST(plausibility_plausibility,F2_LLR_ALG_070_TC_02) {
    pst_reset_contract();
    int32_t packVoltage_mV = 2147483647;
    int32_t highVoltage_mV = 2147483647;
    PST_EQ(PL_CheckStringVoltage(2147483647,2147483647),STD_OK);
}

/* F2-LLR-ALG-070-TC-03: original Inputs/Expected, independent fixture. */
PST_TEST(plausibility_plausibility,F2_LLR_ALG_070_TC_03) {
    pst_reset_contract();
    int32_t packVoltage_mV = 0;
    int32_t highVoltage_mV = 3000;
    PST_EQ(PL_CheckStringVoltage(0,3000),STD_NOT_OK);
}

/* F2-LLR-ALG-070-TC-04: original Inputs/Expected, independent fixture. */
PST_TEST(plausibility_plausibility,F2_LLR_ALG_070_TC_04) {
    pst_reset_contract();
    int32_t packVoltage_mV = 0;
    int32_t highVoltage_mV = 3000 - 1;
    PST_EQ(PL_CheckStringVoltage(0,3000 - 1),STD_OK);
}

/* F2-LLR-ALG-070-TC-05: original Inputs/Expected, independent fixture. */
PST_TEST(plausibility_plausibility,F2_LLR_ALG_070_TC_05) {
    pst_reset_contract();
    int32_t packVoltage_mV = 0;
    int32_t highVoltage_mV = 3000 + 1;
    PST_EQ(PL_CheckStringVoltage(0,(3000 + 1)),STD_NOT_OK);
}

/* F2-LLR-ALG-070-TC-06: original Inputs/Expected, independent fixture. */
PST_TEST(plausibility_plausibility,F2_LLR_ALG_070_TC_06) {
    pst_reset_contract();
    int32_t packVoltage_mV = 4242;
    int32_t highVoltage_mV = 4242;
    PST_EQ(PL_CheckStringVoltage(4242,4242),STD_OK);
}

/* F2-LLR-ALG-070-TC-07: original Inputs/Expected, independent fixture. */
PST_TEST(plausibility_plausibility,F2_LLR_ALG_070_TC_07) {
    pst_reset_contract();
    int32_t packVoltage_mV = 0;
    int32_t highVoltage_mV = 2147483647;
    PST_EQ(PL_CheckStringVoltage(0,2147483647),STD_NOT_OK);
}

/* F2-LLR-ALG-070-TC-10: original Inputs/Expected, independent fixture. */
PST_TEST(plausibility_plausibility,F2_LLR_ALG_070_TC_10) {
    pst_reset_contract();
    int32_t packVoltage_mV = 2147483647;
    int32_t highVoltage_mV = 2147483647;
    PST_EQ(PL_CheckStringVoltage(2147483647,2147483647),STD_OK);
}

/* F2-LLR-ALG-070-02-ADD-001: STD_NOT_OK */
PST_TEST(plausibility_plausibility,F2_LLR_ALG_070_02_ADD_001) {
pst_reset_contract();PST_EQ(PL_CheckStringVoltage(INT32_MIN,INT32_MAX),STD_NOT_OK);
}

/* F2-LLR-ALG-070-02-ADD-002: STD_OK */
PST_TEST(plausibility_plausibility,F2_LLR_ALG_070_02_ADD_002) {
pst_reset_contract();PST_EQ(PL_CheckStringVoltage(INT32_MIN,INT32_MIN),STD_OK);
}

/* F2-LLR-ALG-070-02-ADD-003: STD_NOT_OK */
PST_TEST(plausibility_plausibility,F2_LLR_ALG_070_02_ADD_003) {
pst_reset_contract();PST_EQ(PL_CheckStringVoltage(-3000,0),STD_NOT_OK);
}

/* F2-LLR-ALG-070-02-ADD-004: STD_OK */
PST_TEST(plausibility_plausibility,F2_LLR_ALG_070_02_ADD_004) {
pst_reset_contract();PST_EQ(PL_CheckStringVoltage(-2999,0),STD_OK);
}

/* F2-LLR-ALG-070-03-ADD-001: STD_OK; average 3005 */
PST_TEST(plausibility_plausibility,F2_LLR_ALG_070_03_ADD_001) {
pst_reset_contract();int16_t out=0;PST_EQ(PL_CheckCellVoltage(3000,3010,&out),STD_OK);PST_EQ(out,3005);
}

/* F2-LLR-ALG-070-03-ADD-002: STD_NOT_OK; average 3005 */
PST_TEST(plausibility_plausibility,F2_LLR_ALG_070_03_ADD_002) {
pst_reset_contract();int16_t out=0;PST_EQ(PL_CheckCellVoltage(3000,3011,&out),STD_NOT_OK);PST_EQ(out,3005);
}

/* F2-LLR-ALG-070-03-ADD-003: STD_OK; average -100 */
PST_TEST(plausibility_plausibility,F2_LLR_ALG_070_03_ADD_003) {
pst_reset_contract();int16_t out=0;PST_EQ(PL_CheckCellTemperature(-100,-101,&out),STD_OK);PST_EQ(out,-100);
}

/* F2-LLR-ALG-070-05-ADD-001: valid count equals configured sensors on both calls */
PST_TEST(plausibility_plausibility,F2_LLR_ALG_070_05_ADD_001) {
pst_reset_contract();DATA_BLOCK_CELL_TEMPERATURE_s t={0};DATA_BLOCK_MIN_MAX_s m={0};m.averageTemperature_ddegC[0]=200;
for(unsigned i=0;i<BS_NR_OF_TEMP_SENSORS_PER_MODULE;i++)t.cellTemperature_ddegC[0][0][i]=200;
PST_EQ(PL_CheckTemperatureSpread(&t,&m),STD_OK);PST_EQ(t.nrValidTemperatures[0],BS_NR_OF_TEMP_SENSORS_PER_STRING);
PST_EQ(PL_CheckTemperatureSpread(&t,&m),STD_OK);PST_EQ(t.nrValidTemperatures[0],BS_NR_OF_TEMP_SENSORS_PER_STRING);
}

/* F2-LLR-ALG-070-04-ADD-001: cell0 invalid;others valid;NOT_OK */
PST_TEST(plausibility_plausibility,F2_LLR_ALG_070_04_ADD_001) {
pst_reset_contract();DATA_BLOCK_CELL_VOLTAGE_s v={0};DATA_BLOCK_MIN_MAX_s m={0};m.averageCellVoltage_mV[0]=3000;for(unsigned c=0;c<BS_NR_OF_CELL_BLOCKS_PER_MODULE;c++)v.cellVoltage_mV[0][0][c]=3000;v.cellVoltage_mV[0][0][0]=3400;PST_EQ(PL_CheckVoltageSpread(&v,&m),STD_NOT_OK);PST_EQ(v.invalidCellVoltage[0][0][0],true);PST_EQ(v.invalidCellVoltage[0][0][1],false);
}
