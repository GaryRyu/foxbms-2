#ifndef REDUNDANCY_PST_STUB_CONTRACT_H
#define REDUNDANCY_PST_STUB_CONTRACT_H
#include "database.h"
#include "diag.h"
#include <setjmp.h>
typedef struct { DIAG_ID_e id; DIAG_EVENT_e event; DIAG_IMPACT_LEVEL_e impact; uint32_t index; } Event;
extern uint32_t test_tick, assert_line;
extern int assert_expected;
extern jmp_buf assert_jump;
extern bool closed[BS_NR_OF_STRINGS], precharging[BS_NR_OF_STRINGS];
extern Event events[512];
extern unsigned event_count, read_calls, write_calls, written_count;
extern int written_ids[32];
extern STD_RETURN_TYPE_e read_result, write_result;
extern DATA_BLOCK_CELL_VOLTAGE_s input_vb, input_vr, saved_voltage;
extern DATA_BLOCK_CELL_TEMPERATURE_s input_tb, input_tr, saved_temperature;
extern DATA_BLOCK_MIN_MAX_s saved_minmax;
extern DATA_BLOCK_PACK_VALUES_s saved_pack;
extern DATA_BLOCK_CURRENT_s input_current;
extern DATA_BLOCK_POWER_s input_power;
extern DATA_BLOCK_SYSTEM_VOLTAGE_1_s input_v1;
extern DATA_BLOCK_SYSTEM_VOLTAGE_3_s input_v3;
void reset_stubs(void);
int event_is(DIAG_ID_e id, DIAG_EVENT_e event, DIAG_IMPACT_LEVEL_e impact, unsigned index);
#endif
