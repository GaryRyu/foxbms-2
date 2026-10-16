/* Requirement-based unit tests. Static source access explicitly authorized. */
#include "application_contract.h"
#include "../../../../../src/app/application/bal/history/bal_strategy_history.c"

PST_SUITE(bal_history_bal_strategy_history);
/* F2-LLR-ALG-046-TC-20-01 */
PST_TEST(bal_history_bal_strategy_history,F2_LLR_ALG_046_TC_20_01) {
pst_reset_contract();
PST_EQ(bal_state.state,BAL_FSM_UNINITIALIZED);
}

/* F2-LLR-ALG-046-TC-21-01 */
PST_TEST(bal_history_bal_strategy_history,F2_LLR_ALG_046_TC_21_01) {
pst_reset_contract();
PST_EQ(BAL_GetInitializationState(),STD_NOT_OK);
}

/* F2-LLR-ALG-046-TC-21-02 */
PST_TEST(bal_history_bal_strategy_history,F2_LLR_ALG_046_TC_21_02) {
pst_reset_contract();
PST_EQ(BAL_GetInitializationState(),STD_OK);
}

/* F2-LLR-ALG-046-12-ADD-001: all selection/count0; disabled; history remaining0 */
PST_TEST(bal_history_bal_strategy_history,F2_LLR_ALG_046_12_ADD_001) {
pst_reset_contract();memset(&bal_balancing,0,sizeof(bal_balancing));bal_balancing.enableBalancing=true;bal_balancing.activateBalancing[0][0][0]=true;bal_balancing.deltaCharge_mAs[0][0][0]=100;bal_balancing.nrBalancedCells[0]=1;bal_state.active=true;
BAL_Deactivate();PST_EQ(bal_balancing.enableBalancing,false);PST_EQ(bal_balancing.nrBalancedCells[0],0);PST_EQ(bal_balancing.activateBalancing[0][0][0],false);PST_EQ(bal_balancing.deltaCharge_mAs[0][0][0],0);PST_EQ(bal_state.active,false);PST_EQ(pst_writes,1);
}

/* F2-LLR-ALG-046-11-ADD-001: positive remaining selected;remaining saturates0 */
PST_TEST(bal_history_bal_strategy_history,F2_LLR_ALG_046_11_ADD_001) {
pst_reset_contract();extern DATA_BLOCK_BALANCING_CONTROL_s pst_balancing_control;extern DATA_BLOCK_CELL_VOLTAGE_s pst_cell_voltage;memset(&pst_balancing_control,0,sizeof(pst_balancing_control));memset(&pst_cell_voltage,0,sizeof(pst_cell_voltage));pst_balancing_control.deltaCharge_mAs[0][0][0]=1;pst_cell_voltage.cellVoltage_mV[0][0][0]=3000;bal_state.balancingAllowed=true;BAL_ActivateBalancing();PST_EQ(bal_balancing.deltaCharge_mAs[0][0][0],0);PST_EQ(bal_balancing.activateBalancing[0][0][0],true);PST_EQ(bal_balancing.nrBalancedCells[0],1);
}
