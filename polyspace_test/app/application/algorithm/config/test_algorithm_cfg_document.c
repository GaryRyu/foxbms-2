/* DOCX 4.1--4.11 PSTUnit; production unchanged. */
#include "application_contract.h"
#include "../../../../../src/app/application/algorithm/config/algorithm_cfg.c"
PST_SUITE(algorithm_config_algorithm_cfg);
/* F2-LLR-ALG-001-TC-01: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_config_algorithm_cfg,F2_LLR_ALG_001_TC_01) {
    pst_reset_contract();
    algo_algorithms[0].state=ALGO_UNINITIALIZED;
    PST_EXPECT_SUT_ASSERT(ALGO_MarkAsDone(4294967295u),83);
}

/* F2-LLR-ALG-001-TC-02: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_config_algorithm_cfg,F2_LLR_ALG_001_TC_02) {
    pst_reset_contract();
    algo_algorithms[0].state=ALGO_UNINITIALIZED;
    algo_algorithms[0].state = ALGO_REINIT_REQUESTED;
    ALGO_MarkAsDone(0);
    PST_EQ(algo_algorithms[0].state,ALGO_REINIT_REQUESTED);
}

/* F2-LLR-ALG-001-TC-03: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_config_algorithm_cfg,F2_LLR_ALG_001_TC_03) {
    pst_reset_contract();
    algo_algorithms[0].state=ALGO_UNINITIALIZED;
    algo_algorithms[0].state = ALGO_RUNNING;
    ALGO_MarkAsDone(0);
    PST_EQ(algo_algorithms[0].state,ALGO_READY);
}

/* F2-LLR-ALG-001-TC-04: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_config_algorithm_cfg,F2_LLR_ALG_001_TC_04) {
    pst_reset_contract();
    algo_algorithms[0].state=ALGO_UNINITIALIZED;
    algo_algorithms[0].state = ALGO_BLOCKED;
    ALGO_MarkAsDone(0);
    PST_EQ(algo_algorithms[0].state,ALGO_BLOCKED);
}

/* F2-LLR-ALG-005-TC-01: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_config_algorithm_cfg,F2_LLR_ALG_005_TC_01) {
    pst_reset_contract();
    algo_algorithms[0].state=ALGO_UNINITIALIZED;
    PST_EXPECT_SUT_ASSERT(ALGO_MarkAsReinit(4294967295u),94);
}

/* F2-LLR-ALG-005-TC-02: original Inputs/Expected, independent fixture. */
PST_TEST(algorithm_config_algorithm_cfg,F2_LLR_ALG_005_TC_02) {
    pst_reset_contract();
    algo_algorithms[0].state=ALGO_UNINITIALIZED;
    algo_algorithms[0].state = ALGO_RUNNING;
    ALGO_MarkAsReinit(0);
    PST_EQ(algo_algorithms[0].state,ALGO_REINIT_REQUESTED);
    PST_EQ(pst_enter_calls,1);
    PST_EQ(pst_exit_calls,1);
}
