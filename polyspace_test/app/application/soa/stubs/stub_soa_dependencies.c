/* Document voltage/temperature units: unexpected current-path calls abort. */
#include "application_contract.h"
bool SOA_IsCellCurrentLimitViolated(uint32_t a,BMS_CURRENT_FLOW_STATE_e b){(void)a;(void)b;PST_ABORT();return false;}
bool SOA_IsStringCurrentLimitViolated(uint32_t a,BMS_CURRENT_FLOW_STATE_e b){(void)a;(void)b;PST_ABORT();return false;}
bool SOA_IsPackCurrentLimitViolated(uint32_t a,BMS_CURRENT_FLOW_STATE_e b){(void)a;(void)b;PST_ABORT();return false;}
bool SOA_IsCurrentOnOpenString(BMS_CURRENT_FLOW_STATE_e a,uint8_t b){(void)a;(void)b;PST_ABORT();return false;}
