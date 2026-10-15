/* External undefined-callee stubs; no real DB/OS/BMS/DIAG/FAS implementation linked. */
#include "stub_contract.h"
#include "bms.h"
#include "os.h"
#include "pstunit.h"
#include <string.h>
uint32_t test_tick, assert_line;
int assert_expected;
jmp_buf assert_jump;
bool closed[BS_NR_OF_STRINGS], precharging[BS_NR_OF_STRINGS];
Event events[512];
unsigned event_count, read_calls, write_calls, written_count;
int written_ids[32];
STD_RETURN_TYPE_e read_result, write_result;
DATA_BLOCK_CELL_VOLTAGE_s input_vb, input_vr, saved_voltage;
DATA_BLOCK_CELL_TEMPERATURE_s input_tb, input_tr, saved_temperature;
DATA_BLOCK_MIN_MAX_s saved_minmax;
DATA_BLOCK_PACK_VALUES_s saved_pack;
DATA_BLOCK_CURRENT_s input_current;
DATA_BLOCK_POWER_s input_power;
DATA_BLOCK_SYSTEM_VOLTAGE_1_s input_v1;
DATA_BLOCK_SYSTEM_VOLTAGE_3_s input_v3;
void reset_stubs(void) {
    test_tick=1000; assert_line=0; assert_expected=0;
    event_count=read_calls=write_calls=written_count=0;
    read_result=write_result=STD_OK;
    memset(closed,0,sizeof(closed)); memset(precharging,0,sizeof(precharging));
    memset(events,0,sizeof(events)); memset(written_ids,0,sizeof(written_ids));
#define ZERO(x) memset(&(x),0,sizeof(x))
    ZERO(input_vb); ZERO(input_vr); ZERO(input_tb); ZERO(input_tr);
    ZERO(input_current); ZERO(input_power); ZERO(input_v1); ZERO(input_v3);
    ZERO(saved_voltage); ZERO(saved_temperature); ZERO(saved_minmax); ZERO(saved_pack);
#undef ZERO
    input_vb.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE_BASE;
    input_vr.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE_REDUNDANCY0;
    input_tb.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE_BASE;
    input_tr.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE_REDUNDANCY0;
    input_current.header.uniqueId=DATA_BLOCK_ID_CURRENT;
    input_power.header.uniqueId=DATA_BLOCK_ID_POWER;
    input_v1.header.uniqueId=DATA_BLOCK_ID_SYSTEM_VOLTAGE_1;
    input_v3.header.uniqueId=DATA_BLOCK_ID_SYSTEM_VOLTAGE_3;
}
uint32_t OS_GetTickCount(void) { return test_tick; }
uint8_t BMS_GetNumberOfConnectedStrings(void) { uint8_t n=0; for(unsigned s=0;s<BS_NR_OF_STRINGS;s++) n+=closed[s]; return n; }
bool BMS_IsStringClosed(uint8_t s) { PST_ASSERT_LT_UINT(s,BS_NR_OF_STRINGS); return closed[s]; }
bool BMS_IsStringPrecharging(uint8_t s) { PST_ASSERT_LT_UINT(s,BS_NR_OF_STRINGS); return precharging[s]; }
DIAG_RETURNTYPE_e DIAG_Handler(DIAG_ID_e id, DIAG_EVENT_e event, DIAG_IMPACT_LEVEL_e impact, uint32_t index) {
    PST_ASSERT_LT_UINT(event_count,512);
    events[event_count++]=(Event){id,event,impact,index}; return (DIAG_RETURNTYPE_e)0;
}
STD_RETURN_TYPE_e DIAG_CheckEvent(STD_RETURN_TYPE_e cond,DIAG_ID_e id,DIAG_IMPACT_LEVEL_e impact,uint32_t index) {
    DIAG_Handler(id,cond==STD_OK?DIAG_EVENT_OK:DIAG_EVENT_NOT_OK,impact,index); return STD_OK;
}
int event_is(DIAG_ID_e id,DIAG_EVENT_e event,DIAG_IMPACT_LEVEL_e impact,unsigned index) {
    for(unsigned i=0;i<event_count;i++) if(events[i].id==id && events[i].event==event && events[i].impact==impact && events[i].index==index) return 1;
    return 0;
}
void FAS_StoreAssertLocation(uint32_t *pc,uint32_t line) {
    (void)pc; assert_line=line;
    if(assert_expected) longjmp(assert_jump,1);
    PST_VERIFY_TRUE_MSG(0,"Unexpected production FAS_ASSERT"); PST_ABORT();
}
void FAS_DisableInterrupts(void) { PST_VERIFY_TRUE_MSG(0,"Target interrupt operation reached"); PST_ABORT(); }
static void read_block(void *p) {
    DATA_BLOCK_HEADER_s *h=p;
#define COPY(id,obj) case id: memcpy(p,&obj,sizeof(obj)); break
    switch(h->uniqueId) {
        COPY(DATA_BLOCK_ID_CELL_VOLTAGE_BASE,input_vb);
        COPY(DATA_BLOCK_ID_CELL_VOLTAGE_REDUNDANCY0,input_vr);
        COPY(DATA_BLOCK_ID_CELL_TEMPERATURE_BASE,input_tb);
        COPY(DATA_BLOCK_ID_CELL_TEMPERATURE_REDUNDANCY0,input_tr);
        COPY(DATA_BLOCK_ID_CURRENT,input_current); COPY(DATA_BLOCK_ID_POWER,input_power);
        COPY(DATA_BLOCK_ID_SYSTEM_VOLTAGE_1,input_v1); COPY(DATA_BLOCK_ID_SYSTEM_VOLTAGE_3,input_v3);
        default: PST_VERIFY_TRUE_MSG(0,"Unexpected database read block"); PST_ABORT();
    }
#undef COPY
}
static void write_block(void *p) {
    DATA_BLOCK_HEADER_s *h=p;
    PST_ASSERT_LT_UINT(written_count,32); written_ids[written_count++]=h->uniqueId;
#define COPY(id,obj) case id: memcpy(&obj,p,sizeof(obj)); break
    switch(h->uniqueId) {
        COPY(DATA_BLOCK_ID_CELL_VOLTAGE,saved_voltage); COPY(DATA_BLOCK_ID_CELL_TEMPERATURE,saved_temperature);
        COPY(DATA_BLOCK_ID_MIN_MAX,saved_minmax); COPY(DATA_BLOCK_ID_PACK_VALUES,saved_pack);
        default: PST_VERIFY_TRUE_MSG(0,"Unexpected database write block"); PST_ABORT();
    }
#undef COPY
}
STD_RETURN_TYPE_e DATA_Read4DataBlocks(void*a,void*b,void*c,void*d) {
    read_calls++; if(read_result==STD_OK) {read_block(a);read_block(b);read_block(c);read_block(d);} return read_result;
}
STD_RETURN_TYPE_e DATA_Write1DataBlock(void*a) {write_calls++;write_block(a);return write_result;}
STD_RETURN_TYPE_e DATA_Write2DataBlocks(void*a,void*b) {write_calls++;write_block(a);write_block(b);return write_result;}
STD_RETURN_TYPE_e DATA_Write3DataBlocks(void*a,void*b,void*c) {write_calls++;write_block(a);write_block(b);write_block(c);return write_result;}
