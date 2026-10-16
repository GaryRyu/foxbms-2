/* BAL strategy unit boundary: other production modules are not linked. */
#include "bal.h"
#include "application_contract.h"
void BAL_SaveLastStates(BAL_STATE_s *p){p->lastState=p->state;p->lastSubstate=p->substate;}
uint8_t BAL_CheckReEntrance(BAL_STATE_s *p){(void)p;return 0xff;}
BAL_STATE_REQUEST_e BAL_TransferStateRequest(BAL_STATE_s *p){return p->stateRequest;}
BAL_RETURN_TYPE_e BAL_CheckStateRequest(BAL_STATE_s *p,BAL_STATE_REQUEST_e r){(void)p;(void)r;return BAL_OK;}
STD_RETURN_TYPE_e BAL_Init(DATA_BLOCK_BALANCING_CONTROL_s *p){p->enableBalancing=false;return STD_OK;}
void BAL_ProcessStateUninitialized(BAL_STATE_s *p,BAL_STATE_REQUEST_e r){(void)p;(void)r;}
void BAL_ProcessStateInitialization(BAL_STATE_s *p){(void)p;}
void BAL_ProcessStateInitialized(BAL_STATE_s *p){(void)p;}
int32_t BAL_GetBalancingThreshold_mV(void){return BAL_DEFAULT_THRESHOLD_mV;}
float_t SE_GetStateOfChargeFromVoltage(int16_t voltage){(void)voltage;return 50.0f;}
