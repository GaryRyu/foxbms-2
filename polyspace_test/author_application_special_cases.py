"""Module-specific document cases and additional requirement-based boundaries."""
from pathlib import Path
import json,os,re
from author_application_tests import setup,parse_call,assertion_line,checks
HERE=Path(__file__).resolve().parent;REPO=HERE.parent
doc=json.loads((HERE/'requirements/application-4.1-4.11.json').read_text(encoding='utf-8'))
manifest=json.loads((HERE/'requirements/case-manifest-application.json').read_text(encoding='utf-8'))
config=json.loads((HERE/'config/application_host.json').read_text(encoding='utf-8'))

def write_module(source,definitions,preamble='',stubs=None,deps=None,isolated=False):
 key=source[:-2].replace('/','_').replace('-','_'); directory=HERE/'app/application'/Path(source).parent
 directory.mkdir(parents=True,exist_ok=True);test=directory/('test_'+Path(source).stem+'_document.c');prod=REPO/'src/app/application'/source
 prefix=f'/* Requirement-based unit tests. Static source access explicitly authorized. */\n#include "application_contract.h"\n#include "{Path(os.path.relpath(prod,directory)).as_posix()}"\n{preamble}\nPST_SUITE({key});\n'
 bodies=[];ids=[]
 for c,body in definitions:
  native=c['Test ID'].replace('-','_');bodies.append(f'/* {c["Test ID"]} */\nPST_TEST({key},{native}) {{\n{body}\n}}\n');ids.append(c['Test ID'])
  row=next((r for r in manifest if r['Test ID']==c['Test ID']),None)
  data={**c,'module':key,'source':str(prod.relative_to(REPO)),'test_source':str(test.relative_to(HERE)),'native_test':native,'status':'Authored','Mock':'module contract plus external unit-only definitions','Expected basis':'updated DOCX; additional cases have separate IDs'}
  if row:row.update(data);row.pop('reason',None)
  else:manifest.append(data)
 test.write_text(prefix+'\n'.join(bodies),encoding='utf-8')
 cfg={'module':key,'source':str(prod.relative_to(REPO)),'test':str(test.relative_to(HERE)),'cases':ids,'case_count':len(ids),'isolated_cases':isolated,'stubs':stubs or [],'dependencies':deps or []}
 config['modules']=[m for m in config['modules'] if m['module']!=key]+[cfg]

# Algorithm function-local counter cannot be reset from another scope: each case
# is launched in a separate process, keeping steps within each test sequential.
defs=[]
for c in [c for c in doc['scenarios'] if c['section']==7]:
 num=int(c['Test ID'].split('-')[-1]);body=['reset_algorithm();']
 if num==1:body+=['ALGO_MainFunction();','PST_EQ(algo_algorithms[0].state,ALGO_UNINITIALIZED);','PST_EQ(algo_algorithms[1].state,ALGO_UNINITIALIZED);','PST_EQ(pst_enter_calls,1);PST_EQ(pst_exit_calls,1);','PST_EQ(init_calls,0);PST_EQ(calc_calls,0);']
 elif num in [2,3,4,5,6,7]:
  if num==2:body+=['ALGO_MainFunction();PST_EQ(calc_calls,0);']
  body+=['ALGO_UnlockInitialization();']
  if num==3:body+=['algo_algorithms[0].cycleTime_ms=101;','PST_EXPECT_SUT_ASSERT(ALGO_MainFunction(),'+str(assertion_line(REPO/'src/app/application/algorithm/algorithm.c','ALGO_Initialization',[]))+');','PST_EQ(algo_algorithms[0].state,ALGO_UNINITIALIZED);PST_EQ(algo_algorithms[1].state,ALGO_UNINITIALIZED);']
  elif num==6:
   line=next(i for i,l in enumerate((REPO/'src/app/application/algorithm/algorithm.c').read_text().splitlines(),1) if 'FAS_ASSERT((STD_OK == result)' in l)
   body += ['init_result=(STD_RETURN_TYPE_e)42;','PST_EXPECT_SUT_ASSERT(ALGO_MainFunction(),'+str(line)+');','PST_EQ(init_calls,1);']
  else:
   if num==4:body+=['init_result=STD_NOT_OK;']
   if num==7:body+=['algo_algorithms[0].cycleTime_ms=0;']
   body+=['ALGO_MainFunction();','PST_EQ(init_calls,1);','PST_EQ(algo_algorithms[0].state,ALGO_RUNNING);', 'PST_EQ(algo_algorithms[1].state,'+('ALGO_FAILED_INIT' if num==4 else 'ALGO_RUNNING')+');','PST_EQ(calc_calls,'+('1' if num==4 else '2')+');']
   if num==4:body+=['ALGO_MainFunction();PST_EQ(init_calls,1);PST_EQ(calc_calls,1);']
   if num==5:body+=['ALGO_UnlockInitialization();ALGO_MainFunction();PST_EQ(init_calls,1);PST_EQ(calc_calls,2);']
 elif num>=8:
  body+=['algo_algorithms[0].startTime=500;','algo_algorithms[0].state='+('ALGO_READY' if num==8 else 'ALGO_RUNNING')+';',f'pst_tick={0 if num==8 else 500 if num==9 else 50000};','ALGO_MonitorExecutionTime();','PST_EQ(algo_algorithms[0].state,'+('ALGO_READY' if num==8 else 'ALGO_RUNNING' if num==9 else 'ALGO_BLOCKED')+');']
 defs.append((c,'\n'.join(body)))
for suffix,start,now,expected in [('001',0,1001,'ALGO_BLOCKED'),('002',4294967245,100,'ALGO_BLOCKED'),('003',500,1500,'ALGO_RUNNING')]:
 c={'Test ID':'F2-LLR-ALG-036-06-ADD-'+suffix,'Requirement ID':'F2-LLR-ALG-036-06','SUT':'ALGO_MonitorExecutionTime','Precondition':f'RUNNING start={start}, maxDuration=1000','Inputs':f'tick={now}','Expected':expected,'section':7}
 defs.append((c,f'reset_algorithm();algo_algorithms[0].state=ALGO_RUNNING;algo_algorithms[0].startTime={start}u;pst_tick={now}u;ALGO_MonitorExecutionTime();PST_EQ(algo_algorithms[0].state,{expected});'))
write_module('algorithm/algorithm.c',defs,'''
ALGO_TASKS_s algo_algorithms[2]; const uint16_t algo_length=2;
static unsigned init_calls,calc_calls,done_calls;static STD_RETURN_TYPE_e init_result;
static STD_RETURN_TYPE_e init_stub(void){init_calls++;return init_result;}
static void calc_stub(void){calc_calls++;}
void ALGO_MarkAsDone(uint32_t i){PST_ASSERT_LT_UINT(i,2);done_calls++;}
static void reset_algorithm(void){pst_reset_contract();init_calls=calc_calls=done_calls=0;init_result=STD_OK;algo_initializationRequested=false;
for(unsigned i=0;i<2;i++)algo_algorithms[i]=(ALGO_TASKS_s){ALGO_UNINITIALIZED,100,1000,0,i?init_stub:NULL,calc_stub};}
''',isolated=True)

# BAL common sequential reentry and preservation case supplement.
source='bal/bal.c'; existing=HERE/'app/application/bal/test_bal_document.c'
for tid in ['F2-LLR-ALG-046-TC-04','F2-LLR-ALG-046-TC-18']:
 c=next(c for c in doc['scenarios'] if c['Test ID']==tid);decl,init=setup(c)
 if tid.endswith('04'):decl,init=setup({**c,'Precondition':c['Precondition'].split('단계 2:')[0]})
 if tid.endswith('04'):init=[s for s in init if not s.startswith('initState.triggerEntry')]+['initState.triggerEntry=0;']
 if tid.endswith('04'):
  body=decl+init+['PST_EQ(BAL_CheckReEntrance(&initState),0);','PST_EQ(BAL_CheckReEntrance(&initState),0xFF);','PST_EQ(initState.triggerEntry,1);PST_EQ(pst_enter_calls,2);PST_EQ(pst_exit_calls,2);']
 else:body=decl+init+['BAL_STATE_s before=initState;BAL_ProcessStateUninitialized(&initState,BAL_STATE_NO_REQUEST);','PST_EQ(memcmp(&initState,&before,sizeof(before)),0);']
 native=tid.replace('-','_');existing.write_text(existing.read_text(encoding='utf-8')+f'\nPST_TEST(bal_bal,{native}) {{ pst_reset_contract();\n'+'\n'.join(body)+'\n}\n',encoding='utf-8')
 row=next(r for r in manifest if r['Test ID']==tid);row.update(status='Authored',native_test=native);row.pop('reason',None)
 cfg=next(m for m in config['modules'] if m['module']=='bal_bal');cfg['cases'].append(tid);cfg['case_count']+=1

# Moving-average fresh process; explicit buffers and DB contract.
c=next(c for c in doc['scenarios'] if c['section']==2)
write_module('algorithm/moving_average/moving_average.c',[(c,'''
pst_reset_contract();memset(&pst_current,0,sizeof(pst_current));memset(&pst_power,0,sizeof(pst_power));memset(&pst_moving_average,0,sizeof(pst_moving_average));
pst_current.header.uniqueId=DATA_BLOCK_ID_CURRENT;pst_power.header.uniqueId=DATA_BLOCK_ID_POWER;pst_moving_average.header.uniqueId=DATA_BLOCK_ID_MOVING_AVERAGE;
pst_current.newCurrent=1;pst_power.newPower=1;ALGO_MovingAverage();
PST_EQ(pst_reads,3);PST_EQ(pst_writes,1);
DATA_BLOCK_MOVING_AVERAGE_s expected={.header.uniqueId=DATA_BLOCK_ID_MOVING_AVERAGE};
PST_EQ(memcmp(&pst_moving_average,&expected,sizeof(expected)),0);
''')],'''extern DATA_BLOCK_CURRENT_s pst_current;extern DATA_BLOCK_POWER_s pst_power;extern DATA_BLOCK_MOVING_AVERAGE_s pst_moving_average;''',stubs=['support/host/application_storage.c'],isolated=True)

# Strategy getter observation uses real static state; no UNITY-only getter compiled.
for strategy in ['history','voltage']:
 source=f'bal/{strategy}/bal_strategy_{strategy}.c';defs=[]
 for c in [c for c in doc['scenarios'] if ('['+source+']') in c['SUT']]:
  f,params=parse_call(c);body=['pst_reset_contract();']
  if f=='BAL_GetInitializationState':
   _,init=setup(c);body+=init+checks(c,f+'()')
  elif f=='BAL_GetState':
   expected=re.search(r'SUT 반환값 = (\w+)',c['Expected'])[1]
   if expected=='BAL_FSM_INITIALIZED':
    # Document has no precondition specifying the INITIALIZED transition.
    row=next(r for r in manifest if r['Test ID']==c['Test ID']);row['reason']='Document expects INITIALIZED but supplies no state setting/trigger sequence';continue
   body+=['PST_EQ(bal_state.state,BAL_FSM_UNINITIALIZED);']
  else:
   row=next(r for r in manifest if r['Test ID']==c['Test ID']);row['reason']='BAL_Init case specifies an external read absent from BAL_Init production API; requirement clarification needed';continue
  defs.append((c,'\n'.join(body)))
 if defs:write_module(source,defs,stubs=['support/host/application_storage.c','app/application/bal/stubs/stub_strategy_calls.c'],isolated=True)

# Redundancy: original document's 29 calls, each independent; no imported tests.
defs=[];prod=REPO/'src/app/application/redundancy/redundancy.c'
reset='''pst_reset_contract();memset(&mrc_state,0,sizeof(mrc_state));
memset(&mrc_tableCellVoltages,0,sizeof(mrc_tableCellVoltages));mrc_tableCellVoltages.header.uniqueId=DATA_BLOCK_ID_CELL_VOLTAGE;
memset(&mrc_tableCellTemperatures,0,sizeof(mrc_tableCellTemperatures));mrc_tableCellTemperatures.header.uniqueId=DATA_BLOCK_ID_CELL_TEMPERATURE;
memset(&mrc_tableMinimumMaximumValues,0,sizeof(mrc_tableMinimumMaximumValues));mrc_tableMinimumMaximumValues.header.uniqueId=DATA_BLOCK_ID_MIN_MAX;
memset(&mrc_tablePackValues,0,sizeof(mrc_tablePackValues));mrc_tablePackValues.header.uniqueId=DATA_BLOCK_ID_PACK_VALUES;
'''
for c in [c for c in doc['scenarios'] if c['section']==11]:
 body=[reset];params=[]
 for line in c['Precondition'].splitlines():
  m=re.match(r'객체 (\w+) \[([^]]+)\]:',line)
  if m:body.append(f'{m[2]} {m[1]}={{0}};')
 for line in c['Inputs'].splitlines():
  m=re.match(r'\d+(?:st|nd|rd) parameter.*?: (.+)',line)
  if m:
   val=m[1];obj=re.match(r'객체 (\w+)의 주소',val)
   params.append('&'+obj[1] if obj else 'NULL_PTR' if val.startswith('NULL_PTR') else val.split(' (')[0])
  tick=re.match(r'외부 입력 — OS_GetTickCount 반환값.*?: (\w+)',line)
  if tick:body.append('pst_tick='+tick[1]+';')
 f=c['SUT'];call=f+'('+','.join(params)+')'
 if 'NULL 검사에서 assert' in c['Expected']:body.append(f'PST_EXPECT_SUT_ASSERT({call},{assertion_line(prod,f,params)});')
 elif c['Test ID'].endswith('TC-09'):
  body+=['MRC_STATE_s state_before=mrc_state;DATA_BLOCK_CELL_VOLTAGE_s v_before=mrc_tableCellVoltages;DATA_BLOCK_CELL_TEMPERATURE_s t_before=mrc_tableCellTemperatures;DATA_BLOCK_MIN_MAX_s mm_before=mrc_tableMinimumMaximumValues;',
         'PST_EQ(MRC_ValidateAfeMeasurement(),STD_NOT_OK);PST_EQ(pst_writes,0);PST_EQ(pst_reads,4);',
         'PST_EQ(memcmp(&mrc_state,&state_before,sizeof(state_before)),0);PST_EQ(memcmp(&mrc_tableCellVoltages,&v_before,sizeof(v_before)),0);PST_EQ(memcmp(&mrc_tableCellTemperatures,&t_before,sizeof(t_before)),0);PST_EQ(memcmp(&mrc_tableMinimumMaximumValues,&mm_before,sizeof(mm_before)),0);',
         'pst_check_event(0,DIAG_ID_BASE_CELL_VOLTAGE_MEASUREMENT_TIMEOUT,DIAG_EVENT_NOT_OK,DIAG_SYSTEM,0);',
         'pst_check_event(1,DIAG_ID_REDUNDANCY0_CELL_VOLTAGE_MEASUREMENT_TIMEOUT,DIAG_EVENT_OK,DIAG_SYSTEM,0);',
         'pst_check_event(2,DIAG_ID_BASE_CELL_TEMPERATURE_MEASUREMENT_TIMEOUT,DIAG_EVENT_NOT_OK,DIAG_SYSTEM,0);',
         'pst_check_event(3,DIAG_ID_REDUNDANCY0_CELL_TEMPERATURE_MEASUREMENT_TIMEOUT,DIAG_EVENT_OK,DIAG_SYSTEM,0);PST_EQ(pst_event_count,4);']
 else:body+=checks(c,call)
 defs.append((c,'\n'.join(body)))
write_module('redundancy/redundancy.c',defs,stubs=['app/application/redundancy/stubs/stub_document_redundancy.c'])

# Balancing configuration multi-step document tests.
defs=[]
for c in [c for c in doc['scenarios'] if 'ALG-063-TC' in c['Test ID']]:
 body=['pst_reset_contract();bal_threshold_mV=BAL_DEFAULT_THRESHOLD_mV;']
 args=re.findall(r'1번째 인수 \(int32_t threshold_mV\): ([^\n]+)',c['Inputs'])
 expected=re.findall(r'SUT 반환값 = ([^\n]+)',c['Expected'])
 for a,e in zip(args,expected):body += [f'BAL_SetBalancingThreshold({a});',f'PST_EQ(BAL_GetBalancingThreshold_mV(),{e});']
 body += [f'PST_EQ(pst_enter_calls,{len(args)});PST_EQ(pst_exit_calls,{len(args)});'];defs.append((c,'\n'.join(body)))
write_module('config/bal_cfg.c',defs)
c=next(c for c in doc['scenarios'] if c['Test ID']=='F2-LLR-ALG-046-TC-25')
write_module('bal/none/bal_strategy_none.c',[(c,'pst_reset_contract();PST_EQ(BAL_GetInitializationState(),STD_OK);PST_EQ(BAL_SetStateRequest(BAL_STATE_INIT_REQUEST),BAL_OK);BAL_Trigger();PST_EQ(pst_reads,0);PST_EQ(pst_writes,0);')])

# Persist full traceability. Special authoring may be rerun after generic authoring.
(HERE/'requirements/case-manifest-application.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2),encoding='utf-8')
(HERE/'config/application_host.json').write_text(json.dumps(config,indent=2),encoding='utf-8')
print('Special cases added; authored',sum(x['status']=='Authored' for x in manifest),'total',len(manifest))
