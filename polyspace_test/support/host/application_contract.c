/* Test-only external definitions. Never link real OS/BMS/DIAG/FAS alongside these. */
#include "application_contract.h"
#include "foxmath.h"
jmp_buf pst_assert_jump;
int pst_assert_expected;
uint32_t pst_assert_line,pst_tick;
unsigned pst_enter_calls,pst_exit_calls,pst_reads,pst_writes;
bool pst_closed,pst_precharging;
BMS_CURRENT_FLOW_STATE_e pst_direction;
PST_DIAG_EVENT pst_events[256];
unsigned pst_event_count;
void pst_reset_contract(void) {
 pst_assert_expected=0;pst_assert_line=0;pst_tick=0;pst_enter_calls=pst_exit_calls=pst_reads=pst_writes=pst_event_count=0;
 pst_closed=false;pst_precharging=false;pst_direction=BMS_AT_REST;memset(pst_events,0,sizeof(pst_events));
}
void FAS_StoreAssertLocation(uint32_t *pc,uint32_t line) {
 (void)pc;pst_assert_line=line;
 if(pst_assert_expected)longjmp(pst_assert_jump,1);
 PST_VERIFY_TRUE_MSG(0,"Unexpected SUT Assert");PST_ABORT();
}
void FAS_DisableInterrupts(void) { PST_VERIFY_TRUE_MSG(0,"Target interrupt operation reached");PST_ABORT(); }
void OS_EnterTaskCritical(void){pst_enter_calls++;}
void OS_ExitTaskCritical(void){pst_exit_calls++;}
uint32_t OS_GetTickCount(void){return pst_tick;}
bool BMS_IsStringClosed(uint8_t s){PST_ASSERT_LT_UINT(s,BS_NR_OF_STRINGS);return pst_closed;}
bool BMS_IsStringPrecharging(uint8_t s){PST_ASSERT_LT_UINT(s,BS_NR_OF_STRINGS);return pst_precharging;}
BMS_CURRENT_FLOW_STATE_e BMS_GetBatterySystemState(void){return pst_direction;}
BMS_CURRENT_FLOW_STATE_e BMS_GetCurrentFlowDirection(int32_t current){(void)current;return pst_direction;}
DIAG_RETURNTYPE_e DIAG_Handler(DIAG_ID_e id,DIAG_EVENT_e e,DIAG_IMPACT_LEVEL_e impact,uint32_t s){
 PST_ASSERT_LT_UINT(pst_event_count,256);pst_events[pst_event_count++]=(PST_DIAG_EVENT){id,e,impact,s};return DIAG_HANDLER_RETURN_OK;
}
STD_RETURN_TYPE_e DIAG_CheckEvent(STD_RETURN_TYPE_e c,DIAG_ID_e id,DIAG_IMPACT_LEVEL_e impact,uint32_t s){
 DIAG_Handler(id,c==STD_OK?DIAG_EVENT_OK:DIAG_EVENT_NOT_OK,impact,s);return c;
}
void pst_check_event(unsigned i,DIAG_ID_e id,DIAG_EVENT_e e,DIAG_IMPACT_LEVEL_e impact,uint32_t s){
 PST_ASSERT_LT_UINT(i,pst_event_count);PST_EQ(pst_events[i].id,id);PST_EQ(pst_events[i].event,e);PST_EQ(pst_events[i].impact,impact);PST_EQ(pst_events[i].index,s);
}
/* Arithmetic primitive contracts, not SUT selection/aggregation oracles. */
int32_t MATH_AbsInt32_t(int32_t x){return x<0?-x:x;}
int64_t MATH_AbsInt64_t(int64_t x){return x<0?-x:x;}
float_t MATH_LinearInterpolation(float_t x0,float_t y0,float_t x1,float_t y1,float_t x){PST_ASSERT_TRUE(x1!=x0);return y0+(y1-y0)*(x-x0)/(x1-x0);}
