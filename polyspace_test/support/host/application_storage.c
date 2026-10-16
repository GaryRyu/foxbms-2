/* External DB/FRAM test artifacts. Buffers and operation order are observable. */
#include "application_contract.h"
#include "fram.h"
FRAM_SOC_s fram_soc;
FRAM_SOE_s fram_soe;
unsigned pst_fram_reads,pst_fram_writes;
unsigned pst_written_ids[32];
DATA_BLOCK_CURRENT_s pst_current;
DATA_BLOCK_POWER_s pst_power;
DATA_BLOCK_MIN_MAX_s pst_minmax;
DATA_BLOCK_SYSTEM_VOLTAGE_1_s pst_voltage1;
DATA_BLOCK_ENERGY_COUNTER_s pst_energy_counter;
DATA_BLOCK_CURRENT_COUNTER_s pst_current_counter;
DATA_BLOCK_CELL_VOLTAGE_s pst_cell_voltage;
DATA_BLOCK_BALANCING_CONTROL_s pst_balancing_control;
DATA_BLOCK_MOVING_AVERAGE_s pst_moving_average;
static void read_block(void *p){
 DATA_BLOCK_HEADER_s *h=p;uint32_t id=h->uniqueId;pst_reads++;
 switch(h->uniqueId){
 case DATA_BLOCK_ID_CURRENT:memcpy(p,&pst_current,sizeof(pst_current));break;
 case DATA_BLOCK_ID_POWER:memcpy(p,&pst_power,sizeof(pst_power));break;
 case DATA_BLOCK_ID_MIN_MAX:memcpy(p,&pst_minmax,sizeof(pst_minmax));break;
 case DATA_BLOCK_ID_SYSTEM_VOLTAGE_1:memcpy(p,&pst_voltage1,sizeof(pst_voltage1));break;
 case DATA_BLOCK_ID_ENERGY_COUNTER:memcpy(p,&pst_energy_counter,sizeof(pst_energy_counter));break;
 case DATA_BLOCK_ID_CURRENT_COUNTER:memcpy(p,&pst_current_counter,sizeof(pst_current_counter));break;
 case DATA_BLOCK_ID_CELL_VOLTAGE:memcpy(p,&pst_cell_voltage,sizeof(pst_cell_voltage));break;
 case DATA_BLOCK_ID_BALANCING_CONTROL:memcpy(p,&pst_balancing_control,sizeof(pst_balancing_control));break;
 case DATA_BLOCK_ID_MOVING_AVERAGE:memcpy(p,&pst_moving_average,sizeof(pst_moving_average));break;
 default:break;
 }
 h->uniqueId=id; /* Transport preserves block identity even for zero fixtures. */
}
static void write_block(void *p){
 DATA_BLOCK_HEADER_s *h=p;PST_ASSERT_LT_UINT(pst_writes,32);pst_written_ids[pst_writes++]=h->uniqueId;
 if(h->uniqueId==DATA_BLOCK_ID_MOVING_AVERAGE)memcpy(&pst_moving_average,p,sizeof(pst_moving_average));
}
STD_RETURN_TYPE_e DATA_Read1DataBlock(void *a){read_block(a);return STD_OK;}
STD_RETURN_TYPE_e DATA_Read2DataBlocks(void *a,void *b){read_block(a);read_block(b);return STD_OK;}
STD_RETURN_TYPE_e DATA_Read3DataBlocks(void *a,void *b,void *c){read_block(a);read_block(b);read_block(c);return STD_OK;}
STD_RETURN_TYPE_e DATA_Read4DataBlocks(void *a,void *b,void *c,void *d){read_block(a);read_block(b);read_block(c);read_block(d);return STD_OK;}
STD_RETURN_TYPE_e DATA_Write1DataBlock(void *a){write_block(a);return STD_OK;}
STD_RETURN_TYPE_e DATA_Write2DataBlocks(void *a,void *b){write_block(a);write_block(b);return STD_OK;}
STD_RETURN_TYPE_e DATA_Write3DataBlocks(void *a,void *b,void *c){write_block(a);write_block(b);write_block(c);return STD_OK;}
STD_RETURN_TYPE_e DATA_Write4DataBlocks(void *a,void *b,void *c,void *d){write_block(a);write_block(b);write_block(c);write_block(d);return STD_OK;}
FRAM_RETURN_TYPE_e FRAM_ReadData(FRAM_BLOCK_ID_e id){(void)id;pst_fram_reads++;return (FRAM_RETURN_TYPE_e)0;}
FRAM_RETURN_TYPE_e FRAM_WriteData(FRAM_BLOCK_ID_e id){(void)id;pst_fram_writes++;return (FRAM_RETURN_TYPE_e)0;}
