/* DOCX 4.1--4.11 PSTUnit; production unchanged. */
#include "application_contract.h"
#include "../../../../src/app/application/config/soa_cfg.c"
PST_SUITE(config_soa_cfg);
/* F2-LLR-ALG-066-TC-01-01: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_01_01) {
    pst_reset_contract();
    PST_EQ(SOA_IsPackCurrentLimitViolated(0u,BMS_CHARGING),false);
}

/* F2-LLR-ALG-066-TC-01-02: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_01_02) {
    pst_reset_contract();
    PST_EQ(SOA_IsPackCurrentLimitViolated(0u,BMS_DISCHARGING),false);
}

/* F2-LLR-ALG-066-TC-01-03: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_01_03) {
    pst_reset_contract();
    PST_EQ(SOA_IsPackCurrentLimitViolated(0u,BMS_RELAXATION),false);
}

/* F2-LLR-ALG-066-TC-01-04: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_01_04) {
    pst_reset_contract();
    PST_EQ(SOA_IsPackCurrentLimitViolated(0u,BMS_AT_REST),false);
}

/* F2-LLR-ALG-066-TC-01-05: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_01_05) {
    pst_reset_contract();
    PST_EQ(SOA_IsPackCurrentLimitViolated(2400u,BMS_CHARGING),false);
}

/* F2-LLR-ALG-066-TC-01-06: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_01_06) {
    pst_reset_contract();
    PST_EQ(SOA_IsPackCurrentLimitViolated(2400u,BMS_DISCHARGING),false);
}

/* F2-LLR-ALG-066-TC-01-07: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_01_07) {
    pst_reset_contract();
    PST_EQ(SOA_IsPackCurrentLimitViolated(2400u,BMS_RELAXATION),false);
}

/* F2-LLR-ALG-066-TC-01-08: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_01_08) {
    pst_reset_contract();
    PST_EQ(SOA_IsPackCurrentLimitViolated(2400u,BMS_AT_REST),false);
}

/* F2-LLR-ALG-066-TC-01-09: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_01_09) {
    pst_reset_contract();
    PST_EQ(SOA_IsPackCurrentLimitViolated(2400u + 1u,BMS_CHARGING),true);
}

/* F2-LLR-ALG-066-TC-01-10: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_01_10) {
    pst_reset_contract();
    PST_EQ(SOA_IsPackCurrentLimitViolated(2400u + 1u,BMS_DISCHARGING),true);
}

/* F2-LLR-ALG-066-TC-01-11: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_01_11) {
    pst_reset_contract();
    PST_EQ(SOA_IsPackCurrentLimitViolated(2400u + 1u,BMS_RELAXATION),false);
}

/* F2-LLR-ALG-066-TC-01-12: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_01_12) {
    pst_reset_contract();
    PST_EQ(SOA_IsPackCurrentLimitViolated(2400u + 1u,BMS_AT_REST),false);
}

/* F2-LLR-ALG-066-TC-01-13: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_01_13) {
    pst_reset_contract();
    PST_EQ(SOA_IsPackCurrentLimitViolated(4294967295u,BMS_CHARGING),true);
}

/* F2-LLR-ALG-066-TC-01-14: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_01_14) {
    pst_reset_contract();
    PST_EQ(SOA_IsPackCurrentLimitViolated(4294967295u,BMS_DISCHARGING),true);
}

/* F2-LLR-ALG-066-TC-01-15: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_01_15) {
    pst_reset_contract();
    PST_EQ(SOA_IsPackCurrentLimitViolated(4294967295u,BMS_RELAXATION),false);
}

/* F2-LLR-ALG-066-TC-01-16: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_01_16) {
    pst_reset_contract();
    PST_EQ(SOA_IsPackCurrentLimitViolated(4294967295u,BMS_AT_REST),false);
}

/* F2-LLR-ALG-066-TC-02-01: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_02_01) {
    pst_reset_contract();
    PST_EQ(SOA_IsStringCurrentLimitViolated(0u,BMS_CHARGING),false);
}

/* F2-LLR-ALG-066-TC-02-02: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_02_02) {
    pst_reset_contract();
    PST_EQ(SOA_IsStringCurrentLimitViolated(0u,BMS_DISCHARGING),false);
}

/* F2-LLR-ALG-066-TC-02-03: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_02_03) {
    pst_reset_contract();
    PST_EQ(SOA_IsStringCurrentLimitViolated(0u,BMS_RELAXATION),false);
}

/* F2-LLR-ALG-066-TC-02-04: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_02_04) {
    pst_reset_contract();
    PST_EQ(SOA_IsStringCurrentLimitViolated(0u,BMS_AT_REST),false);
}

/* F2-LLR-ALG-066-TC-02-05: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_02_05) {
    pst_reset_contract();
    PST_EQ(SOA_IsStringCurrentLimitViolated(2400u,BMS_CHARGING),false);
}

/* F2-LLR-ALG-066-TC-02-06: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_02_06) {
    pst_reset_contract();
    PST_EQ(SOA_IsStringCurrentLimitViolated(2400u,BMS_DISCHARGING),false);
}

/* F2-LLR-ALG-066-TC-02-07: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_02_07) {
    pst_reset_contract();
    PST_EQ(SOA_IsStringCurrentLimitViolated(2400u,BMS_RELAXATION),false);
}

/* F2-LLR-ALG-066-TC-02-08: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_02_08) {
    pst_reset_contract();
    PST_EQ(SOA_IsStringCurrentLimitViolated(2400u,BMS_AT_REST),false);
}

/* F2-LLR-ALG-066-TC-02-09: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_02_09) {
    pst_reset_contract();
    PST_EQ(SOA_IsStringCurrentLimitViolated(2400u + 1u,BMS_CHARGING),true);
}

/* F2-LLR-ALG-066-TC-02-10: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_02_10) {
    pst_reset_contract();
    PST_EQ(SOA_IsStringCurrentLimitViolated(2400u + 1u,BMS_DISCHARGING),true);
}

/* F2-LLR-ALG-066-TC-02-11: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_02_11) {
    pst_reset_contract();
    PST_EQ(SOA_IsStringCurrentLimitViolated(2400u + 1u,BMS_RELAXATION),false);
}

/* F2-LLR-ALG-066-TC-02-12: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_02_12) {
    pst_reset_contract();
    PST_EQ(SOA_IsStringCurrentLimitViolated(2400u + 1u,BMS_AT_REST),false);
}

/* F2-LLR-ALG-066-TC-02-13: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_02_13) {
    pst_reset_contract();
    PST_EQ(SOA_IsStringCurrentLimitViolated(4294967295u,BMS_CHARGING),true);
}

/* F2-LLR-ALG-066-TC-02-14: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_02_14) {
    pst_reset_contract();
    PST_EQ(SOA_IsStringCurrentLimitViolated(4294967295u,BMS_DISCHARGING),true);
}

/* F2-LLR-ALG-066-TC-02-15: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_02_15) {
    pst_reset_contract();
    PST_EQ(SOA_IsStringCurrentLimitViolated(4294967295u,BMS_RELAXATION),false);
}

/* F2-LLR-ALG-066-TC-02-16: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_02_16) {
    pst_reset_contract();
    PST_EQ(SOA_IsStringCurrentLimitViolated(4294967295u,BMS_AT_REST),false);
}

/* F2-LLR-ALG-066-TC-03-01: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_03_01) {
    pst_reset_contract();
    PST_EQ(SOA_IsCellCurrentLimitViolated(0u,BMS_CHARGING),false);
}

/* F2-LLR-ALG-066-TC-03-02: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_03_02) {
    pst_reset_contract();
    PST_EQ(SOA_IsCellCurrentLimitViolated(0u,BMS_DISCHARGING),false);
}

/* F2-LLR-ALG-066-TC-03-03: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_03_03) {
    pst_reset_contract();
    PST_EQ(SOA_IsCellCurrentLimitViolated(0u,BMS_RELAXATION),false);
}

/* F2-LLR-ALG-066-TC-03-04: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_03_04) {
    pst_reset_contract();
    PST_EQ(SOA_IsCellCurrentLimitViolated(0u,BMS_AT_REST),false);
}

/* F2-LLR-ALG-066-TC-03-05: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_03_05) {
    pst_reset_contract();
    uint32_t chargeLimit = 1u * 180000u;
    PST_EQ(SOA_IsCellCurrentLimitViolated((1u * 180000u),BMS_CHARGING),false);
}

/* F2-LLR-ALG-066-TC-03-06: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_03_06) {
    pst_reset_contract();
    uint32_t dischargeLimit = 1u * 180000u;
    PST_EQ(SOA_IsCellCurrentLimitViolated((1u * 180000u),BMS_DISCHARGING),false);
}

/* F2-LLR-ALG-066-TC-03-07: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_03_07) {
    pst_reset_contract();
    uint32_t chargeLimit = 1u * 180000u;
    PST_EQ(SOA_IsCellCurrentLimitViolated((1u * 180000u),BMS_RELAXATION),false);
}

/* F2-LLR-ALG-066-TC-03-08: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_03_08) {
    pst_reset_contract();
    uint32_t chargeLimit = 1u * 180000u;
    PST_EQ(SOA_IsCellCurrentLimitViolated((1u * 180000u),BMS_AT_REST),false);
}

/* F2-LLR-ALG-066-TC-03-09: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_03_09) {
    pst_reset_contract();
    uint32_t dischargeLimit = 1u * 180000u;
    PST_EQ(SOA_IsCellCurrentLimitViolated((1u * 180000u),BMS_RELAXATION),false);
}

/* F2-LLR-ALG-066-TC-03-10: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_03_10) {
    pst_reset_contract();
    uint32_t dischargeLimit = 1u * 180000u;
    PST_EQ(SOA_IsCellCurrentLimitViolated((1u * 180000u),BMS_AT_REST),false);
}

/* F2-LLR-ALG-066-TC-03-11: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_03_11) {
    pst_reset_contract();
    uint32_t chargeLimit = 1u * 180000u;
    PST_EQ(SOA_IsCellCurrentLimitViolated((1u * 180000u) + 1u,BMS_CHARGING),true);
}

/* F2-LLR-ALG-066-TC-03-12: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_03_12) {
    pst_reset_contract();
    uint32_t dischargeLimit = 1u * 180000u;
    PST_EQ(SOA_IsCellCurrentLimitViolated((1u * 180000u) + 1u,BMS_DISCHARGING),true);
}

/* F2-LLR-ALG-066-TC-03-13: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_03_13) {
    pst_reset_contract();
    uint32_t chargeLimit = 1u * 180000u;
    PST_EQ(SOA_IsCellCurrentLimitViolated((1u * 180000u) + 1u,BMS_RELAXATION),false);
}

/* F2-LLR-ALG-066-TC-03-14: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_03_14) {
    pst_reset_contract();
    uint32_t chargeLimit = 1u * 180000u;
    PST_EQ(SOA_IsCellCurrentLimitViolated((1u * 180000u) + 1u,BMS_AT_REST),false);
}

/* F2-LLR-ALG-066-TC-03-15: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_03_15) {
    pst_reset_contract();
    uint32_t dischargeLimit = 1u * 180000u;
    PST_EQ(SOA_IsCellCurrentLimitViolated((1u * 180000u) + 1u,BMS_RELAXATION),false);
}

/* F2-LLR-ALG-066-TC-03-16: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_03_16) {
    pst_reset_contract();
    uint32_t dischargeLimit = 1u * 180000u;
    PST_EQ(SOA_IsCellCurrentLimitViolated((1u * 180000u) + 1u,BMS_AT_REST),false);
}

/* F2-LLR-ALG-066-TC-03-17: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_03_17) {
    pst_reset_contract();
    PST_EQ(SOA_IsCellCurrentLimitViolated(4294967295u,BMS_CHARGING),true);
}

/* F2-LLR-ALG-066-TC-03-18: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_03_18) {
    pst_reset_contract();
    PST_EQ(SOA_IsCellCurrentLimitViolated(4294967295u,BMS_DISCHARGING),true);
}

/* F2-LLR-ALG-066-TC-03-19: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_03_19) {
    pst_reset_contract();
    PST_EQ(SOA_IsCellCurrentLimitViolated(4294967295u,BMS_RELAXATION),false);
}

/* F2-LLR-ALG-066-TC-03-20: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_03_20) {
    pst_reset_contract();
    PST_EQ(SOA_IsCellCurrentLimitViolated(4294967295u,BMS_AT_REST),false);
}

/* F2-LLR-ALG-066-TC-04-01: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_04_01) {
    pst_reset_contract();
    PST_EXPECT_SUT_ASSERT(SOA_IsCurrentOnOpenString(BMS_CHARGING,1u),117);
}

/* F2-LLR-ALG-066-TC-04-02: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_04_02) {
    pst_reset_contract();
    pst_closed=false;
    pst_precharging=false;
    PST_EQ(SOA_IsCurrentOnOpenString(BMS_CHARGING,0u),true);
}

/* F2-LLR-ALG-066-TC-04-03: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_04_03) {
    pst_reset_contract();
    pst_closed=true;
    pst_precharging=false;
    PST_EQ(SOA_IsCurrentOnOpenString(BMS_CHARGING,0u),false);
}

/* F2-LLR-ALG-066-TC-04-04: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_04_04) {
    pst_reset_contract();
    pst_closed=false;
    pst_precharging=true;
    PST_EQ(SOA_IsCurrentOnOpenString(BMS_CHARGING,0u),false);
}

/* F2-LLR-ALG-066-TC-04-05: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_04_05) {
    pst_reset_contract();
    pst_closed=false;
    pst_precharging=false;
    PST_EQ(SOA_IsCurrentOnOpenString(BMS_DISCHARGING,0u),true);
}

/* F2-LLR-ALG-066-TC-04-06: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_04_06) {
    pst_reset_contract();
    pst_closed=true;
    pst_precharging=false;
    PST_EQ(SOA_IsCurrentOnOpenString(BMS_DISCHARGING,0u),false);
}

/* F2-LLR-ALG-066-TC-04-07: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_04_07) {
    pst_reset_contract();
    pst_closed=false;
    pst_precharging=true;
    PST_EQ(SOA_IsCurrentOnOpenString(BMS_DISCHARGING,0u),false);
}

/* F2-LLR-ALG-066-TC-04-08: original Inputs/Expected, independent fixture. */
PST_TEST(config_soa_cfg,F2_LLR_ALG_066_TC_04_08) {
    pst_reset_contract();
    PST_EQ(SOA_IsCurrentOnOpenString(BMS_RELAXATION,0u),false);
}
