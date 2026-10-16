/* DOCX 4.1--4.11 PSTUnit; production unchanged. */
#include "application_contract.h"
#include "../../../../src/app/application/soa/soa.c"
PST_SUITE(soa_soa);
/* F2-LLR-ALG-090-TC-01-01: original Inputs/Expected, independent fixture. */
PST_TEST(soa_soa,F2_LLR_ALG_090_TC_01_01) {
    pst_reset_contract();
    PST_EXPECT_SUT_ASSERT(SOA_CheckVoltages(NULL),82);
}

/* F2-LLR-ALG-090-TC-01-02: original Inputs/Expected, independent fixture. */
PST_TEST(soa_soa,F2_LLR_ALG_090_TC_01_02) {
    pst_reset_contract();
    DATA_BLOCK_MIN_MAX_s pMinimumMaximumCellVoltages = {.header.uniqueId = DATA_BLOCK_ID_MIN_MAX};
    SOA_CheckVoltages(&pMinimumMaximumCellVoltages);
    pst_check_event(0,DIAG_ID_CELL_VOLTAGE_OVERVOLTAGE_MSL, DIAG_EVENT_OK, DIAG_STRING, 0u);
    pst_check_event(1,DIAG_ID_CELL_VOLTAGE_OVERVOLTAGE_RSL, DIAG_EVENT_OK, DIAG_STRING, 0u);
    pst_check_event(2,DIAG_ID_CELL_VOLTAGE_OVERVOLTAGE_MOL, DIAG_EVENT_OK, DIAG_STRING, 0u);
    pst_check_event(3,DIAG_ID_CELL_VOLTAGE_UNDERVOLTAGE_MOL, DIAG_EVENT_NOT_OK, DIAG_STRING, 0u);
    pst_check_event(4,DIAG_ID_CELL_VOLTAGE_UNDERVOLTAGE_RSL, DIAG_EVENT_NOT_OK, DIAG_STRING, 0u);
    pst_check_event(5,DIAG_ID_CELL_VOLTAGE_UNDERVOLTAGE_MSL, DIAG_EVENT_NOT_OK, DIAG_STRING, 0u);
    PST_EQ(pst_event_count,6);
}

/* F2-LLR-ALG-090-TC-02-01: original Inputs/Expected, independent fixture. */
PST_TEST(soa_soa,F2_LLR_ALG_090_TC_02_01) {
    pst_reset_contract();
    DATA_BLOCK_PACK_VALUES_s pCurrent = {.header.uniqueId = DATA_BLOCK_ID_PACK_VALUES};
    PST_EXPECT_SUT_ASSERT(SOA_CheckTemperatures(NULL,&pCurrent),151);
}

/* F2-LLR-ALG-090-TC-02-02: original Inputs/Expected, independent fixture. */
PST_TEST(soa_soa,F2_LLR_ALG_090_TC_02_02) {
    pst_reset_contract();
    DATA_BLOCK_MIN_MAX_s pMinimumMaximumCellVoltages = {.header.uniqueId = DATA_BLOCK_ID_MIN_MAX};
    PST_EXPECT_SUT_ASSERT(SOA_CheckTemperatures(&pMinimumMaximumCellVoltages,NULL),152);
}

/* F2-LLR-ALG-090-TC-02-03: original Inputs/Expected, independent fixture. */
PST_TEST(soa_soa,F2_LLR_ALG_090_TC_02_03) {
    pst_reset_contract();
    DATA_BLOCK_MIN_MAX_s pMinimumMaximumCellVoltages = {.header.uniqueId = DATA_BLOCK_ID_MIN_MAX};
    DATA_BLOCK_PACK_VALUES_s pCurrent = {.header.uniqueId = DATA_BLOCK_ID_PACK_VALUES};
    pst_direction=BMS_AT_REST;
    pst_direction=BMS_AT_REST;
    SOA_CheckTemperatures(&pMinimumMaximumCellVoltages,&pCurrent);
    pst_check_event(0,DIAG_ID_TEMP_OVERTEMPERATURE_CHARGE_MSL, DIAG_EVENT_OK, DIAG_STRING, 0u);
    pst_check_event(1,DIAG_ID_TEMP_OVERTEMPERATURE_CHARGE_RSL, DIAG_EVENT_OK, DIAG_STRING, 0u);
    pst_check_event(2,DIAG_ID_TEMP_OVERTEMPERATURE_CHARGE_MOL, DIAG_EVENT_OK, DIAG_STRING, 0u);
    pst_check_event(3,DIAG_ID_TEMP_UNDERTEMPERATURE_CHARGE_MSL, DIAG_EVENT_OK, DIAG_STRING, 0u);
    pst_check_event(4,DIAG_ID_TEMP_UNDERTEMPERATURE_CHARGE_RSL, DIAG_EVENT_OK, DIAG_STRING, 0u);
    pst_check_event(5,DIAG_ID_TEMP_UNDERTEMPERATURE_CHARGE_MOL, DIAG_EVENT_OK, DIAG_STRING, 0u);
    PST_EQ(pst_event_count,6);
}

/* F2-LLR-ALG-090-04-ADD-001: invalid measurements excluded;no diagnostic */
PST_TEST(soa_soa,F2_LLR_ALG_090_04_ADD_001) {
pst_reset_contract();DATA_BLOCK_PACK_VALUES_s p={0};p.invalidPackCurrent=1;p.invalidStringCurrent[0]=1;SOA_CheckCurrent(&p);PST_EQ(pst_event_count,0);
}
