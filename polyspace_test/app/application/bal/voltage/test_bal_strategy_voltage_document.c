/* Requirement-based unit tests. Static source access explicitly authorized. */
#include "application_contract.h"
#include "../../../../../src/app/application/bal/voltage/bal_strategy_voltage.c"

PST_SUITE(bal_voltage_bal_strategy_voltage);
/* F2-LLR-ALG-046-TC-23-01 */
PST_TEST(bal_voltage_bal_strategy_voltage,F2_LLR_ALG_046_TC_23_01) {
pst_reset_contract();
PST_EQ(bal_state.state,BAL_FSM_UNINITIALIZED);
}

/* F2-LLR-ALG-046-TC-24-01 */
PST_TEST(bal_voltage_bal_strategy_voltage,F2_LLR_ALG_046_TC_24_01) {
pst_reset_contract();
PST_EQ(BAL_GetInitializationState(),STD_NOT_OK);
}

/* F2-LLR-ALG-046-TC-24-02 */
PST_TEST(bal_voltage_bal_strategy_voltage,F2_LLR_ALG_046_TC_24_02) {
pst_reset_contract();
PST_EQ(BAL_GetInitializationState(),STD_OK);
}

/* F2-LLR-ALG-046-12-ADD-001: all selection/count0; disabled; history remaining0 */
PST_TEST(bal_voltage_bal_strategy_voltage,F2_LLR_ALG_046_12_ADD_001) {
pst_reset_contract();memset(&bal_tableBalancingControl,0,sizeof(bal_tableBalancingControl));bal_tableBalancingControl.enableBalancing=true;bal_tableBalancingControl.activateBalancing[0][0][0]=true;bal_tableBalancingControl.deltaCharge_mAs[0][0][0]=100;bal_tableBalancingControl.nrBalancedCells[0]=1;bal_state.active=true;
BAL_Deactivate();PST_EQ(bal_tableBalancingControl.enableBalancing,false);PST_EQ(bal_tableBalancingControl.nrBalancedCells[0],0);PST_EQ(bal_tableBalancingControl.activateBalancing[0][0][0],false);PST_EQ(bal_tableBalancingControl.deltaCharge_mAs[0][0][0],0);PST_EQ(bal_state.active,false);PST_EQ(pst_writes,1);
}

/* F2-LLR-ALG-046-10-ADD-001: only +1 cell selected */
PST_TEST(bal_voltage_bal_strategy_voltage,F2_LLR_ALG_046_10_ADD_001) {
pst_reset_contract();extern DATA_BLOCK_MIN_MAX_s pst_minmax;extern DATA_BLOCK_CELL_VOLTAGE_s pst_cell_voltage;
memset(&pst_minmax,0,sizeof(pst_minmax));memset(&pst_cell_voltage,0,sizeof(pst_cell_voltage));pst_minmax.minimumCellVoltage_mV[0]=3000;for(unsigned i=0;i<BS_NR_OF_CELL_BLOCKS_PER_MODULE;i++)pst_cell_voltage.cellVoltage_mV[0][0][i]=3000;
bal_state.balancingThreshold=BAL_DEFAULT_THRESHOLD_mV;pst_cell_voltage.cellVoltage_mV[0][0][0]=3000+BAL_DEFAULT_THRESHOLD_mV;pst_cell_voltage.cellVoltage_mV[0][0][1]=3001+BAL_DEFAULT_THRESHOLD_mV;
PST_EQ(BAL_ActivateBalancing(),false);PST_EQ(bal_tableBalancingControl.activateBalancing[0][0][0],false);PST_EQ(bal_tableBalancingControl.activateBalancing[0][0][1],true);PST_EQ(bal_tableBalancingControl.nrBalancedCells[0],1);
}
