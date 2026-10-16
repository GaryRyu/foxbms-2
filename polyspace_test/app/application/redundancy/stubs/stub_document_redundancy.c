/* Isolated redundancy unit external dependencies; no real PL/DB/OS linked. */
#include "application_contract.h"
#include "database_helper.h"
#include "plausibility.h"
STD_RETURN_TYPE_e pst_rdn_write_result=STD_OK;
int pst_rdn_pack_fixture,pst_rdn_spread_fixture;
unsigned pst_rdn_spread_calls;
static void read(void *p){DATA_BLOCK_HEADER_s *h=p;pst_reads++;uint32_t id=h->uniqueId;
switch(id){
case DATA_BLOCK_ID_CELL_VOLTAGE_BASE:case DATA_BLOCK_ID_CELL_VOLTAGE_REDUNDANCY0:memset(p,0,sizeof(DATA_BLOCK_CELL_VOLTAGE_s));break;
case DATA_BLOCK_ID_CELL_TEMPERATURE_BASE:case DATA_BLOCK_ID_CELL_TEMPERATURE_REDUNDANCY0:memset(p,0,sizeof(DATA_BLOCK_CELL_TEMPERATURE_s));break;
case DATA_BLOCK_ID_CURRENT:if(!pst_rdn_pack_fixture)PST_ABORT();memset(p,0,sizeof(DATA_BLOCK_CURRENT_s));break;
case DATA_BLOCK_ID_SYSTEM_VOLTAGE_1:if(!pst_rdn_pack_fixture)PST_ABORT();memset(p,0,sizeof(DATA_BLOCK_SYSTEM_VOLTAGE_1_s));break;
case DATA_BLOCK_ID_SYSTEM_VOLTAGE_3:if(!pst_rdn_pack_fixture)PST_ABORT();memset(p,0,sizeof(DATA_BLOCK_SYSTEM_VOLTAGE_3_s));break;
case DATA_BLOCK_ID_POWER:if(!pst_rdn_pack_fixture)PST_ABORT();memset(p,0,sizeof(DATA_BLOCK_POWER_s));break;
default:PST_VERIFY_TRUE_MSG(0,"Unconfigured DB input");PST_ABORT();}h->uniqueId=id;}
STD_RETURN_TYPE_e DATA_Read4DataBlocks(void*a,void*b,void*c,void*d){read(a);read(b);read(c);read(d);return STD_OK;}
STD_RETURN_TYPE_e DATA_Read3DataBlocks(void*a,void*b,void*c){read(a);read(b);read(c);return STD_OK;}
STD_RETURN_TYPE_e DATA_Read2DataBlocks(void*a,void*b){read(a);read(b);return STD_OK;}
STD_RETURN_TYPE_e DATA_Read1DataBlock(void*a){read(a);return STD_OK;}
STD_RETURN_TYPE_e DATA_Write1DataBlock(void*a){(void)a;pst_writes++;return STD_OK;}
STD_RETURN_TYPE_e DATA_Write2DataBlocks(void*a,void*b){(void)a;(void)b;pst_writes+=2;return STD_OK;}
STD_RETURN_TYPE_e DATA_Write3DataBlocks(void*a,void*b,void*c){(void)a;(void)b;(void)c;pst_writes+=3;return pst_rdn_write_result;}
STD_RETURN_TYPE_e DATA_Write4DataBlocks(void*a,void*b,void*c,void*d){(void)a;(void)b;(void)c;(void)d;pst_writes+=4;return STD_OK;}
bool DATA_DatabaseEntryUpdatedAtLeastOnce(DATA_BLOCK_HEADER_s h){return h.timestamp!=0||h.previousTimestamp!=0;}
bool DATA_EntryUpdatedWithinInterval(DATA_BLOCK_HEADER_s h,uint32_t interval){return DATA_DatabaseEntryUpdatedAtLeastOnce(h)&&((uint32_t)(pst_tick-h.timestamp)<=interval);}
uint8_t BMS_GetNumberOfConnectedStrings(void){return pst_closed?BS_NR_OF_STRINGS:0;}
STD_RETURN_TYPE_e PL_CheckVoltageSpread(DATA_BLOCK_CELL_VOLTAGE_s*a,DATA_BLOCK_MIN_MAX_s*b){(void)b;if(!pst_rdn_spread_fixture)PST_ABORT();pst_rdn_spread_calls++;a->invalidCellVoltage[0][0][0]=true;return STD_NOT_OK;}
STD_RETURN_TYPE_e PL_CheckTemperatureSpread(DATA_BLOCK_CELL_TEMPERATURE_s*a,DATA_BLOCK_MIN_MAX_s*b){(void)a;(void)b;PST_ABORT();return STD_NOT_OK;}
STD_RETURN_TYPE_e PL_CheckCellVoltage(int16_t a,int16_t b,int16_t*c){(void)a;(void)b;(void)c;PST_ABORT();return STD_NOT_OK;}
STD_RETURN_TYPE_e PL_CheckCellTemperature(int16_t a,int16_t b,int16_t*c){(void)a;(void)b;(void)c;PST_ABORT();return STD_NOT_OK;}
STD_RETURN_TYPE_e PL_CheckStringVoltage(int32_t a,int32_t b){(void)a;(void)b;PST_ABORT();return STD_NOT_OK;}
