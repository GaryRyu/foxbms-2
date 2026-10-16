/* DOCX 4.1--4.11 PSTUnit; production unchanged. */
#include "application_contract.h"
#include "../../../../src/app/application/bal/bal.c"
PST_SUITE(bal_bal);
/* F2-LLR-ALG-046-TC-01: original Inputs/Expected, independent fixture. */
PST_TEST(bal_bal,F2_LLR_ALG_046_TC_01) {
    pst_reset_contract();
    BAL_STATE_s initState = {0};
    initState.timer = 0;
    initState.stateRequest = BAL_STATE_NO_REQUEST;
    initState.lastState = BAL_FSM_UNINITIALIZED;
    initState.state = BAL_FSM_UNINITIALIZED;
    initState.lastSubstate = BAL_ENTRY;
    initState.substate = BAL_ENTRY;
    initState.triggerEntry = 0;
    initState.errorRequestCounter = 0;
    initState.initializationFinished = STD_NOT_OK;
    initState.active = false;
    initState.balancingThreshold = 0;
    initState.balancingAllowed = false;
    initState.balancingGlobalAllowed = false;
    BAL_SaveLastStates(&initState);
    PST_EQ(BAL_FSM_UNINITIALIZED,initState.lastState);
    PST_EQ(BAL_FSM_UNINITIALIZED,initState.state);
    PST_EQ(BAL_ENTRY,initState.lastSubstate);
    PST_EQ(BAL_ENTRY,initState.substate);
}

/* F2-LLR-ALG-046-TC-02: original Inputs/Expected, independent fixture. */
PST_TEST(bal_bal,F2_LLR_ALG_046_TC_02) {
    pst_reset_contract();
    BAL_STATE_s initState = {0};
    initState.timer = 0;
    initState.stateRequest = BAL_STATE_NO_REQUEST;
    initState.lastState = BAL_FSM_UNINITIALIZED;
    initState.state = BAL_FSM_INITIALIZATION;
    initState.lastSubstate = BAL_ENTRY;
    initState.substate = BAL_ENTRY;
    initState.triggerEntry = 0;
    initState.errorRequestCounter = 0;
    initState.initializationFinished = STD_NOT_OK;
    initState.active = false;
    initState.balancingThreshold = 0;
    initState.balancingAllowed = false;
    initState.balancingGlobalAllowed = false;
    BAL_SaveLastStates(&initState);
    PST_EQ(BAL_FSM_INITIALIZATION,initState.lastState);
    PST_EQ(BAL_FSM_INITIALIZATION,initState.state);
    PST_EQ(BAL_ENTRY,initState.lastSubstate);
    PST_EQ(BAL_ENTRY,initState.substate);
}

/* F2-LLR-ALG-046-TC-03: original Inputs/Expected, independent fixture. */
PST_TEST(bal_bal,F2_LLR_ALG_046_TC_03) {
    pst_reset_contract();
    BAL_STATE_s initState = {0};
    initState.timer = 0;
    initState.stateRequest = BAL_STATE_NO_REQUEST;
    initState.lastState = BAL_FSM_UNINITIALIZED;
    initState.state = BAL_FSM_UNINITIALIZED;
    initState.lastSubstate = BAL_ENTRY;
    initState.substate = BAL_CHECK_IMBALANCES;
    initState.triggerEntry = 0;
    initState.errorRequestCounter = 0;
    initState.initializationFinished = STD_NOT_OK;
    initState.active = false;
    initState.balancingThreshold = 0;
    initState.balancingAllowed = false;
    initState.balancingGlobalAllowed = false;
    BAL_SaveLastStates(&initState);
    PST_EQ(BAL_FSM_UNINITIALIZED,initState.lastState);
    PST_EQ(BAL_FSM_UNINITIALIZED,initState.state);
    PST_EQ(BAL_CHECK_IMBALANCES,initState.lastSubstate);
    PST_EQ(BAL_CHECK_IMBALANCES,initState.substate);
}

/* F2-LLR-ALG-046-TC-05: original Inputs/Expected, independent fixture. */
PST_TEST(bal_bal,F2_LLR_ALG_046_TC_05) {
    pst_reset_contract();
    BAL_STATE_s initState = {0};
    initState.timer = 0;
    initState.stateRequest = BAL_STATE_ERROR_REQUEST;
    initState.lastState = BAL_FSM_UNINITIALIZED;
    initState.state = BAL_FSM_UNINITIALIZED;
    initState.lastSubstate = BAL_ENTRY;
    initState.substate = BAL_ENTRY;
    initState.triggerEntry = 0;
    initState.errorRequestCounter = 0;
    initState.initializationFinished = STD_NOT_OK;
    initState.active = false;
    initState.balancingThreshold = 0;
    initState.balancingAllowed = false;
    initState.balancingGlobalAllowed = false;
    PST_EQ(BAL_TransferStateRequest(&initState),BAL_STATE_ERROR_REQUEST);
    PST_EQ(BAL_STATE_NO_REQUEST,initState.stateRequest);
    PST_EQ(pst_enter_calls,1);
    PST_EQ(pst_exit_calls,1);
}

/* F2-LLR-ALG-046-TC-06: original Inputs/Expected, independent fixture. */
PST_TEST(bal_bal,F2_LLR_ALG_046_TC_06) {
    pst_reset_contract();
    BAL_STATE_s initState = {0};
    initState.timer = 0;
    initState.stateRequest = BAL_STATE_NO_REQUEST;
    initState.lastState = BAL_FSM_UNINITIALIZED;
    initState.state = BAL_FSM_UNINITIALIZED;
    initState.lastSubstate = BAL_ENTRY;
    initState.substate = BAL_ENTRY;
    initState.triggerEntry = 0;
    initState.errorRequestCounter = 0;
    initState.initializationFinished = STD_NOT_OK;
    initState.active = false;
    initState.balancingThreshold = 0;
    initState.balancingAllowed = false;
    initState.balancingGlobalAllowed = false;
    PST_EQ(BAL_CheckStateRequest(&initState,BAL_STATE_ERROR_REQUEST),BAL_OK);
}

/* F2-LLR-ALG-046-TC-07: original Inputs/Expected, independent fixture. */
PST_TEST(bal_bal,F2_LLR_ALG_046_TC_07) {
    pst_reset_contract();
    BAL_STATE_s initState = {0};
    initState.timer = 0;
    initState.stateRequest = BAL_STATE_NO_REQUEST;
    initState.lastState = BAL_FSM_UNINITIALIZED;
    initState.state = BAL_FSM_UNINITIALIZED;
    initState.lastSubstate = BAL_ENTRY;
    initState.substate = BAL_ENTRY;
    initState.triggerEntry = 0;
    initState.errorRequestCounter = 0;
    initState.initializationFinished = STD_NOT_OK;
    initState.active = false;
    initState.balancingThreshold = 0;
    initState.balancingAllowed = false;
    initState.balancingGlobalAllowed = false;
    PST_EQ(BAL_CheckStateRequest(&initState,BAL_STATE_GLOBAL_ENABLE_REQUEST),BAL_OK);
    PST_EQ(true,initState.balancingGlobalAllowed);
}

/* F2-LLR-ALG-046-TC-08: original Inputs/Expected, independent fixture. */
PST_TEST(bal_bal,F2_LLR_ALG_046_TC_08) {
    pst_reset_contract();
    BAL_STATE_s initState = {0};
    initState.timer = 0;
    initState.stateRequest = BAL_STATE_NO_REQUEST;
    initState.lastState = BAL_FSM_UNINITIALIZED;
    initState.state = BAL_FSM_UNINITIALIZED;
    initState.lastSubstate = BAL_ENTRY;
    initState.substate = BAL_ENTRY;
    initState.triggerEntry = 0;
    initState.errorRequestCounter = 0;
    initState.initializationFinished = STD_NOT_OK;
    initState.active = false;
    initState.balancingThreshold = 0;
    initState.balancingAllowed = false;
    initState.balancingGlobalAllowed = true;
    PST_EQ(BAL_CheckStateRequest(&initState,BAL_STATE_GLOBAL_DISABLE_REQUEST),BAL_OK);
    PST_EQ(false,initState.balancingGlobalAllowed);
}

/* F2-LLR-ALG-046-TC-09: original Inputs/Expected, independent fixture. */
PST_TEST(bal_bal,F2_LLR_ALG_046_TC_09) {
    pst_reset_contract();
    BAL_STATE_s initState = {0};
    initState.timer = 0;
    initState.stateRequest = BAL_STATE_NO_REQUEST;
    initState.lastState = BAL_FSM_UNINITIALIZED;
    initState.state = BAL_FSM_UNINITIALIZED;
    initState.lastSubstate = BAL_ENTRY;
    initState.substate = BAL_ENTRY;
    initState.triggerEntry = 0;
    initState.errorRequestCounter = 0;
    initState.initializationFinished = STD_NOT_OK;
    initState.active = false;
    initState.balancingThreshold = 0;
    initState.balancingAllowed = false;
    initState.balancingGlobalAllowed = false;
    PST_EQ(BAL_CheckStateRequest(&initState,BAL_STATE_NO_BALANCING_REQUEST),BAL_OK);
}

/* F2-LLR-ALG-046-TC-10: original Inputs/Expected, independent fixture. */
PST_TEST(bal_bal,F2_LLR_ALG_046_TC_10) {
    pst_reset_contract();
    BAL_STATE_s initState = {0};
    initState.timer = 0;
    initState.stateRequest = BAL_STATE_NO_REQUEST;
    initState.lastState = BAL_FSM_UNINITIALIZED;
    initState.state = BAL_FSM_UNINITIALIZED;
    initState.lastSubstate = BAL_ENTRY;
    initState.substate = BAL_ENTRY;
    initState.triggerEntry = 0;
    initState.errorRequestCounter = 0;
    initState.initializationFinished = STD_NOT_OK;
    initState.active = false;
    initState.balancingThreshold = 0;
    initState.balancingAllowed = false;
    initState.balancingGlobalAllowed = false;
    PST_EQ(BAL_CheckStateRequest(&initState,BAL_STATE_ALLOW_BALANCING_REQUEST),BAL_OK);
}

/* F2-LLR-ALG-046-TC-11: original Inputs/Expected, independent fixture. */
PST_TEST(bal_bal,F2_LLR_ALG_046_TC_11) {
    pst_reset_contract();
    BAL_STATE_s initState = {0};
    initState.timer = 0;
    initState.stateRequest = BAL_STATE_NO_REQUEST;
    initState.lastState = BAL_FSM_UNINITIALIZED;
    initState.state = BAL_FSM_UNINITIALIZED;
    initState.lastSubstate = BAL_ENTRY;
    initState.substate = BAL_ENTRY;
    initState.triggerEntry = 0;
    initState.errorRequestCounter = 0;
    initState.initializationFinished = STD_NOT_OK;
    initState.active = false;
    initState.balancingThreshold = 0;
    initState.balancingAllowed = false;
    initState.balancingGlobalAllowed = false;
    PST_EQ(BAL_CheckStateRequest(&initState,BAL_STATE_INIT_REQUEST),BAL_OK);
}

/* F2-LLR-ALG-046-TC-12: original Inputs/Expected, independent fixture. */
PST_TEST(bal_bal,F2_LLR_ALG_046_TC_12) {
    pst_reset_contract();
    BAL_STATE_s initState = {0};
    initState.timer = 0;
    initState.stateRequest = BAL_STATE_NO_REQUEST;
    initState.lastState = BAL_FSM_UNINITIALIZED;
    initState.state = BAL_FSM_INITIALIZED;
    initState.lastSubstate = BAL_ENTRY;
    initState.substate = BAL_ENTRY;
    initState.triggerEntry = 0;
    initState.errorRequestCounter = 0;
    initState.initializationFinished = STD_NOT_OK;
    initState.active = false;
    initState.balancingThreshold = 0;
    initState.balancingAllowed = false;
    initState.balancingGlobalAllowed = false;
    PST_EQ(BAL_CheckStateRequest(&initState,BAL_STATE_INIT_REQUEST),BAL_ALREADY_INITIALIZED);
}

/* F2-LLR-ALG-046-TC-13: original Inputs/Expected, independent fixture. */
PST_TEST(bal_bal,F2_LLR_ALG_046_TC_13) {
    pst_reset_contract();
    BAL_STATE_s initState = {0};
    initState.timer = 0;
    initState.stateRequest = BAL_STATE_NO_REQUEST;
    initState.lastState = BAL_FSM_UNINITIALIZED;
    initState.state = BAL_FSM_UNINITIALIZED;
    initState.lastSubstate = BAL_ENTRY;
    initState.substate = BAL_ENTRY;
    initState.triggerEntry = 0;
    initState.errorRequestCounter = 0;
    initState.initializationFinished = STD_NOT_OK;
    initState.active = false;
    initState.balancingThreshold = 0;
    initState.balancingAllowed = false;
    initState.balancingGlobalAllowed = false;
    PST_EQ(BAL_CheckStateRequest(&initState,BAL_STATE_NO_REQUEST),BAL_ILLEGAL_REQUEST);
}

/* F2-LLR-ALG-046-TC-14: original Inputs/Expected, independent fixture. */
PST_TEST(bal_bal,F2_LLR_ALG_046_TC_14) {
    pst_reset_contract();
    BAL_STATE_s initState = {0};
    initState.timer = 0;
    initState.stateRequest = BAL_STATE_NO_REQUEST;
    initState.lastState = BAL_FSM_UNINITIALIZED;
    initState.state = BAL_FSM_UNINITIALIZED;
    initState.lastSubstate = BAL_ENTRY;
    initState.substate = BAL_ENTRY;
    initState.triggerEntry = 0;
    initState.errorRequestCounter = 0;
    initState.initializationFinished = STD_NOT_OK;
    initState.active = false;
    initState.balancingThreshold = 0;
    initState.balancingAllowed = false;
    initState.balancingGlobalAllowed = false;
    BAL_ProcessStateUninitialized(&initState,BAL_STATE_INIT_REQUEST);
    PST_EQ(1u,initState.timer);
    PST_EQ(BAL_FSM_INITIALIZATION,initState.state);
    PST_EQ(BAL_ENTRY,initState.substate);
}

/* F2-LLR-ALG-046-TC-15: original Inputs/Expected, independent fixture. */
PST_TEST(bal_bal,F2_LLR_ALG_046_TC_15) {
    pst_reset_contract();
    BAL_STATE_s initState = {0};
    initState.timer = 0;
    initState.stateRequest = BAL_STATE_NO_REQUEST;
    initState.lastState = BAL_FSM_UNINITIALIZED;
    initState.state = BAL_FSM_UNINITIALIZED;
    initState.lastSubstate = BAL_ENTRY;
    initState.substate = BAL_ENTRY;
    initState.triggerEntry = 0;
    initState.errorRequestCounter = 0xFE;
    initState.initializationFinished = STD_NOT_OK;
    initState.active = false;
    initState.balancingThreshold = 0;
    initState.balancingAllowed = false;
    initState.balancingGlobalAllowed = false;
    BAL_ProcessStateUninitialized(&initState,BAL_STATE_ERROR_REQUEST);
    PST_EQ(0xFF,initState.errorRequestCounter);
}

/* F2-LLR-ALG-046-TC-16: original Inputs/Expected, independent fixture. */
PST_TEST(bal_bal,F2_LLR_ALG_046_TC_16) {
    pst_reset_contract();
    BAL_STATE_s initState = {0};
    initState.timer = 0;
    initState.stateRequest = BAL_STATE_NO_REQUEST;
    initState.lastState = BAL_FSM_UNINITIALIZED;
    initState.state = BAL_FSM_UNINITIALIZED;
    initState.lastSubstate = BAL_ENTRY;
    initState.substate = BAL_ENTRY;
    initState.triggerEntry = 0;
    initState.errorRequestCounter = 0;
    initState.initializationFinished = STD_NOT_OK;
    initState.active = false;
    initState.balancingThreshold = 0;
    initState.balancingAllowed = false;
    initState.balancingGlobalAllowed = false;
    BAL_ProcessStateInitialization(&initState);
    PST_EQ(1u,initState.timer);
    PST_EQ(BAL_FSM_INITIALIZED,initState.state);
    PST_EQ(BAL_ENTRY,initState.substate);
}

/* F2-LLR-ALG-046-TC-17: original Inputs/Expected, independent fixture. */
PST_TEST(bal_bal,F2_LLR_ALG_046_TC_17) {
    pst_reset_contract();
    BAL_STATE_s initState = {0};
    initState.timer = 0;
    initState.stateRequest = BAL_STATE_NO_REQUEST;
    initState.lastState = BAL_FSM_UNINITIALIZED;
    initState.state = BAL_FSM_UNINITIALIZED;
    initState.lastSubstate = BAL_ENTRY;
    initState.substate = BAL_ENTRY;
    initState.triggerEntry = 0;
    initState.errorRequestCounter = 0;
    initState.initializationFinished = STD_NOT_OK;
    initState.active = false;
    initState.balancingThreshold = 0;
    initState.balancingAllowed = false;
    initState.balancingGlobalAllowed = false;
    BAL_ProcessStateInitialized(&initState);
    PST_EQ(STD_OK,initState.initializationFinished);
    PST_EQ(1u,initState.timer);
    PST_EQ(BAL_FSM_CHECK_BALANCING,initState.state);
    PST_EQ(BAL_ENTRY,initState.substate);
}

PST_TEST(bal_bal,F2_LLR_ALG_046_TC_04) { pst_reset_contract();
BAL_STATE_s initState = {0};
initState.timer = 0;
initState.stateRequest = BAL_STATE_NO_REQUEST;
initState.lastState = BAL_FSM_UNINITIALIZED;
initState.state = BAL_FSM_UNINITIALIZED;
initState.lastSubstate = BAL_ENTRY;
initState.substate = BAL_ENTRY;
initState.errorRequestCounter = 0;
initState.initializationFinished = STD_NOT_OK;
initState.active = false;
initState.balancingThreshold = 0;
initState.balancingAllowed = false;
initState.balancingGlobalAllowed = false;
initState.triggerEntry=0;
PST_EQ(BAL_CheckReEntrance(&initState),0);
PST_EQ(BAL_CheckReEntrance(&initState),0xFF);
PST_EQ(initState.triggerEntry,1);PST_EQ(pst_enter_calls,2);PST_EQ(pst_exit_calls,2);
}

PST_TEST(bal_bal,F2_LLR_ALG_046_TC_18) { pst_reset_contract();
BAL_STATE_s initState = {0};
initState.timer = 0;
initState.stateRequest = BAL_STATE_NO_REQUEST;
initState.lastState = BAL_FSM_UNINITIALIZED;
initState.state = BAL_FSM_UNINITIALIZED;
initState.lastSubstate = BAL_ENTRY;
initState.substate = BAL_ENTRY;
initState.triggerEntry = 0;
initState.errorRequestCounter = 0;
initState.initializationFinished = STD_NOT_OK;
initState.active = false;
initState.balancingThreshold = 0;
initState.balancingAllowed = false;
initState.balancingGlobalAllowed = false;
BAL_STATE_s before=initState;BAL_ProcessStateUninitialized(&initState,BAL_STATE_NO_REQUEST);
PST_EQ(memcmp(&initState,&before,sizeof(before)),0);
}
