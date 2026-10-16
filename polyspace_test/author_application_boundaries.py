"""Additional requirement-based unit vectors; never derive Expected from output."""
from pathlib import Path
import json
from author_application_special_cases import write_module,config,manifest,HERE,REPO,reset

def add(module,req,suffix,sut,pre,inputs,expected,body):
 cfg=next(m for m in config['modules'] if m['module']==module);test=HERE/cfg['test']
 tid=req+'-ADD-'+suffix;native=tid.replace('-','_')
 test.write_text(test.read_text(encoding='utf-8')+f'\n/* {tid}: {expected} */\nPST_TEST({module},{native}) {{\n{body}\n}}\n',encoding='utf-8')
 cfg['cases'].append(tid);cfg['case_count']+=1
 manifest.append({'Test ID':tid,'Requirement ID':req,'SUT':sut,'Precondition':pre,'Inputs':inputs,'Expected':expected,'Mock':'module external dependency contract','module':module,'source':cfg['source'],'test_source':cfg['test'],'native_test':native,'status':'Authored','purpose':'requirement-based gap case','section':0})

module='plausibility_plausibility'
for suffix,a,b,expected in [('001','INT32_MIN','INT32_MAX','STD_NOT_OK'),('002','INT32_MIN','INT32_MIN','STD_OK'),('003','-3000','0','STD_NOT_OK'),('004','-2999','0','STD_OK')]:
 add(module,'F2-LLR-ALG-070-02',suffix,'PL_CheckStringVoltage','no globals',f'{a}, {b}',expected,f'pst_reset_contract();PST_EQ(PL_CheckStringVoltage({a},{b}),{expected});')
for suffix,a,b,expected,average in [('001',3000,3010,'STD_OK',3005),('002',3000,3011,'STD_NOT_OK',3005)]:
 add(module,'F2-LLR-ALG-070-03',suffix,'PL_CheckCellVoltage','valid output pointer',f'{a},{b}',f'{expected}; average {average}',f'pst_reset_contract();int16_t out=0;PST_EQ(PL_CheckCellVoltage({a},{b},&out),{expected});PST_EQ(out,{average});')
add(module,'F2-LLR-ALG-070-03','003','PL_CheckCellTemperature','valid output','-100,-101','STD_OK; average -100','pst_reset_contract();int16_t out=0;PST_EQ(PL_CheckCellTemperature(-100,-101,&out),STD_OK);PST_EQ(out,-100);')
add(module,'F2-LLR-ALG-070-05','001','PL_CheckTemperatureSpread','all valid; repeat call','all sensors=200; mean200','valid count equals configured sensors on both calls','''pst_reset_contract();DATA_BLOCK_CELL_TEMPERATURE_s t={0};DATA_BLOCK_MIN_MAX_s m={0};m.averageTemperature_ddegC[0]=200;
for(unsigned i=0;i<BS_NR_OF_TEMP_SENSORS_PER_MODULE;i++)t.cellTemperature_ddegC[0][0][i]=200;
PST_EQ(PL_CheckTemperatureSpread(&t,&m),STD_OK);PST_EQ(t.nrValidTemperatures[0],BS_NR_OF_TEMP_SENSORS_PER_STRING);
PST_EQ(PL_CheckTemperatureSpread(&t,&m),STD_OK);PST_EQ(t.nrValidTemperatures[0],BS_NR_OF_TEMP_SENSORS_PER_STRING);''')

module='redundancy_redundancy'
add(module,'F2-LLR-ALG-080-11','001','MRC_CalculateCellVoltageMinMaxAverage','all voltage channels valid','all3000; first2900; second3100','min2900/max3100/average3000; full valid count',reset+'''
DATA_BLOCK_CELL_VOLTAGE_s v={0};DATA_BLOCK_MIN_MAX_s m={0};
for(unsigned i=0;i<BS_NR_OF_CELL_BLOCKS_PER_MODULE;i++)v.cellVoltage_mV[0][0][i]=3000;
v.cellVoltage_mV[0][0][0]=2900;v.cellVoltage_mV[0][0][1]=3100;
PST_EQ(MRC_CalculateCellVoltageMinMaxAverage(&v,&m),STD_OK);PST_EQ(m.minimumCellVoltage_mV[0],2900);PST_EQ(m.maximumCellVoltage_mV[0],3100);PST_EQ(m.averageCellVoltage_mV[0],3000);PST_EQ(m.validMeasuredCellVoltages[0],BS_NR_OF_CELL_BLOCKS_PER_STRING);''')
add(module,'F2-LLR-ALG-080-12','001','MRC_CalculateCellTemperatureMinMaxAverage','all valid','all200 first100 second300','min100/max300/mean200',reset+'''
DATA_BLOCK_CELL_TEMPERATURE_s t={0};DATA_BLOCK_MIN_MAX_s m={0};
for(unsigned i=0;i<BS_NR_OF_TEMP_SENSORS_PER_MODULE;i++)t.cellTemperature_ddegC[0][0][i]=200;
t.cellTemperature_ddegC[0][0][0]=100;t.cellTemperature_ddegC[0][0][1]=300;
PST_EQ(MRC_CalculateCellTemperatureMinMaxAverage(&t,&m),STD_OK);PST_EQ(m.minimumTemperature_ddegC[0],100);PST_EQ(m.maximumTemperature_ddegC[0],300);PST_EQ(m.averageTemperature_ddegC[0],200);''')

# SOC manual integration uses a fixed, mathematically derived 1 second vector.
module='algorithm_state_estimation_soc_counting_soc_counting'
add(module,'F2-LLR-ALG-008-06','001','SE_CalculateStateOfCharge','initialized; all50%; manual counting; t0=0','I=1000mA, t1=1000ms, DISCHARGING','50 - (1000/SOC_STRING_CAPACITY_mAs)*100; discharge1As','''
pst_reset_contract();memset(&soc_state,0,sizeof(soc_state));soc_state.socInitialized=true;memset(&fram_soc,0,sizeof(fram_soc));
extern DATA_BLOCK_CURRENT_s pst_current;memset(&pst_current,0,sizeof(pst_current));pst_current.timestamp[0]=1000;pst_current.current_mA[0]=1000;pst_direction=BMS_DISCHARGING;
DATA_BLOCK_SOC_s s={0};s.averageSoc_perc[0]=s.minimumSoc_perc[0]=s.maximumSoc_perc[0]=50;
float_t expected=50-(1000.0f/SOC_STRING_CAPACITY_mAs)*100.0f*BS_CURRENT_DIRECTION_FLOAT;
SE_CalculateStateOfCharge(&s);PST_EQ(s.averageSoc_perc[0],expected);PST_EQ(s.minimumSoc_perc[0],expected);PST_EQ(s.maximumSoc_perc[0],expected);PST_EQ(s.dischargeThroughput_As[0],1.0f);PST_EQ(fram_soc.dischargeThroughput_As[0],1.0f);''')

# SOE counting has no document scenarios: add independent initialization, clamp,
# signed energy calculation and state gating tests for its five requirements.
defs=[];module='algorithm_state_estimation_soe_counting_soe_counting'
for suffix,body,pre,inputs,expected,req in [
 ('001','pst_reset_contract();PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfEnergy(NULL,false,0),321);','valid index','NULL','Assert','F2-LLR-APP-SOE-001-01'),
 ('002','pst_reset_contract();DATA_BLOCK_SOE_s s={0};PST_EXPECT_SUT_ASSERT(SE_InitializeStateOfEnergy(&s,false,BS_NR_OF_STRINGS),322);','nonNULL block','out-of-range index','Assert','F2-LLR-APP-SOE-001-01'),
 ('003','pst_reset_contract();memset(&soe_state,0,sizeof(soe_state));DATA_BLOCK_SOE_s s={0},before=s;SE_CalculateStateOfEnergy(&s);PST_EQ(memcmp(&s,&before,sizeof(s)),0);PST_EQ(pst_reads,0);','uninitialized','normal block','no processing','F2-LLR-APP-SOE-001-02'),
 ('004','pst_reset_contract();DATA_BLOCK_SOE_s s={0};s.averageSoe_perc[0]=-1;s.minimumSoe_perc[0]=50;s.maximumSoe_perc[0]=101;SOE_CheckDatabaseSoePercentageLimits(&s,0);PST_EQ(s.averageSoe_perc[0],0);PST_EQ(s.minimumSoe_perc[0],50);PST_EQ(s.maximumSoe_perc[0],100);','nonNULL block','-1,50,101%','0,50,100%','F2-LLR-APP-SOE-001-04'),
 ('005','''pst_reset_contract();memset(&soe_state,0,sizeof(soe_state));soe_state.soeInitialized=true;
extern DATA_BLOCK_CURRENT_s pst_current;extern DATA_BLOCK_SYSTEM_VOLTAGE_1_s pst_voltage1;
memset(&pst_current,0,sizeof(pst_current));memset(&pst_voltage1,0,sizeof(pst_voltage1));pst_current.timestamp[0]=3600000;pst_current.current_mA[0]=-1000;pst_voltage1.highVoltage_mV[0]=1000;pst_direction=BMS_CHARGING;
DATA_BLOCK_SOE_s s={0};s.averageSoe_Wh[0]=s.minimumSoe_Wh[0]=s.maximumSoe_Wh[0]=10;SE_CalculateStateOfEnergy(&s);
PST_EQ(s.averageSoe_Wh[0],11);PST_EQ(s.minimumSoe_Wh[0],11);PST_EQ(s.maximumSoe_Wh[0],11);PST_EQ(s.chargeEnergyThroughput_Wh[0],1);''','initialized,manual,10Wh','-1A*1V*3600s','11Wh, charge1Wh','F2-LLR-APP-SOE-001-05')]:
 c={'Test ID':req+'-ADD-'+suffix,'Requirement ID':req,'SUT':'SOE counting','Precondition':pre,'Inputs':inputs,'Expected':expected,'section':4};defs.append((c,body))
write_module('algorithm/state_estimation/soe/counting/soe_counting.c',defs,'#include "fram.h"',stubs=['support/host/application_storage.c'],deps=['src/app/application/config/battery_cell_cfg.c'],isolated=True)

# Additional no-valid statistics and current/power aggregate policies.
for typ,f,invalid,minfield,maxfield,avgfield,countfield,req in [
 ('DATA_BLOCK_CELL_VOLTAGE_s','MRC_CalculateCellVoltageMinMaxAverage','invalidCellVoltage','minimumCellVoltage_mV','maximumCellVoltage_mV','averageCellVoltage_mV','validMeasuredCellVoltages','F2-LLR-ALG-080-13'),
 ('DATA_BLOCK_CELL_TEMPERATURE_s','MRC_CalculateCellTemperatureMinMaxAverage','invalidCellTemperature','minimumTemperature_ddegC','maximumTemperature_ddegC','averageTemperature_ddegC','validMeasuredCellTemperatures','F2-LLR-ALG-080-13')]:
 suffix='001' if 'Voltage' in f else '002'
 body=reset+f'''{typ} input={{0}};memset(&input.{invalid},1,sizeof(input.{invalid}));DATA_BLOCK_MIN_MAX_s output={{0}};
PST_EQ({f}(&input,&output),STD_NOT_OK);PST_EQ(output.{minfield}[0],INT16_MAX);PST_EQ(output.{maxfield}[0],INT16_MIN);PST_EQ(output.{avgfield}[0],0);PST_EQ(output.{countfield}[0],0);'''
 add('redundancy_redundancy',req,suffix,f,'all invalid','no valid samples','STD_NOT_OK; sentinel extrema; average/count0',body)
add('redundancy_redundancy','F2-LLR-ALG-080-28','001','MRC_ValidatePowerMeasurement','previous power77 valid; current invalid; voltage valid','new invalid sensor power','77 retained; invalidStringPower1; packPower0 invalid',reset+'''
DATA_BLOCK_POWER_s p={0};p.timestamp[0]=1;p.invalidMeasurement[0]=1;pst_tick=1;mrc_tablePackValues.stringPower_W[0]=77;mrc_tablePackValues.invalidStringPower[0]=0;mrc_tablePackValues.invalidStringCurrent[0]=1;mrc_tablePackValues.invalidStringVoltage[0]=0;
MRC_ValidatePowerMeasurement(&p);PST_EQ(mrc_tablePackValues.stringPower_W[0],77);PST_EQ(mrc_tablePackValues.invalidStringPower[0],1);PST_EQ(mrc_tablePackValues.packPower_W,0);PST_EQ(mrc_tablePackValues.invalidPackPower,1);''')
add('redundancy_redundancy','F2-LLR-ALG-080-22','001','MRC_ValidatePowerMeasurement','current/voltage valid','invalid sensor; -2000mA*3000mV','valid -6W',reset+'''
DATA_BLOCK_POWER_s p={0};p.timestamp[0]=1;p.invalidMeasurement[0]=1;pst_tick=1;mrc_tablePackValues.stringCurrent_mA[0]=-2000;mrc_tablePackValues.stringVoltage_mV[0]=3000;
MRC_ValidatePowerMeasurement(&p);PST_EQ(mrc_tablePackValues.stringPower_W[0],-6);PST_EQ(mrc_tablePackValues.invalidStringPower[0],0);PST_EQ(mrc_tablePackValues.packPower_W,-6);''')
for strategy in ['history','voltage']:
 module=f'bal_{strategy}_bal_strategy_{strategy}';obj='bal_balancing' if strategy=='history' else 'bal_tableBalancingControl';f='BAL_Deactivate' if strategy=='history' else 'BAL_Deactivate'
 add(module,'F2-LLR-ALG-046-12','001','BAL_Deactivate','selected/active cells, nonzero counts','deactivate','all selection/count0; disabled; history remaining0',f'''pst_reset_contract();memset(&{obj},0,sizeof({obj}));{obj}.enableBalancing=true;{obj}.activateBalancing[0][0][0]=true;{obj}.deltaCharge_mAs[0][0][0]=100;{obj}.nrBalancedCells[0]=1;bal_state.active=true;
{f}();PST_EQ({obj}.enableBalancing,false);PST_EQ({obj}.nrBalancedCells[0],0);PST_EQ({obj}.activateBalancing[0][0][0],false);PST_EQ({obj}.deltaCharge_mAs[0][0][0],0);PST_EQ(bal_state.active,false);PST_EQ(pst_writes,1);''')

for suffix,invalid in [('001',0),('002',1)]:
 add('algorithm_moving_average_moving_average','F2-LLR-ALG-007-05',suffix,'ALGO_MovingAverage','fresh process; counters changed' if not invalid else 'fresh process; counters changed but invalid','zero samples' if not invalid else 'invalid current/power','write1' if not invalid else 'write0','''pst_reset_contract();memset(&pst_current,0,sizeof(pst_current));memset(&pst_power,0,sizeof(pst_power));memset(&pst_moving_average,0,sizeof(pst_moving_average));pst_current.newCurrent=pst_power.newPower=1;
'''+f'pst_current.invalidMeasurement[0]=pst_power.invalidMeasurement[0]={invalid};ALGO_MovingAverage();PST_EQ(pst_writes,{0 if invalid else 1});'+('ALGO_MovingAverage();PST_EQ(pst_writes,1);' if not invalid else ''))

# Write newly extended configs and full manifest.
(HERE/'requirements/case-manifest-application.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2),encoding='utf-8')
(HERE/'config/application_host.json').write_text(json.dumps(config,indent=2),encoding='utf-8')
print('Additional requirement cases authored; total',len(manifest))
