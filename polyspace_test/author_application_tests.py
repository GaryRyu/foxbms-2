"""Author PSTUnit from verbatim document fields; unsupported contracts stay explicit.

No legacy framework/tests are read. Generation is reproducible and each body has
the original ID, setup, actual production call and requirement-derived checks.
"""
from pathlib import Path
import json,re,os,collections
HERE=Path(__file__).resolve().parent; REPO=HERE.parent
doc=json.loads((HERE/'requirements/application-4.1-4.11.json').read_text(encoding='utf-8'))
modules=collections.defaultdict(list)
for c in doc['scenarios']:
    match=re.search(r'\[([^\]]+\.c)\]',c['SUT'])
    source=match[1] if match else 'redundancy/redundancy.c'
    modules[source].append(c)

def value(t):
    return t.strip().rstrip(';')

def setup(c):
    decl=[]; statements=[]
    for line in c['Precondition'].splitlines():
        m=re.match(r'(?:상태/객체|전역 상태) (\w+) \(([^)]+)\): (.+?)(?:; 지정|$)',line)
        if m:
            name,typ,v=m.groups()
            if name=='fram_soc':statements.append('memset(&fram_soc,0,sizeof(fram_soc));');continue
            if v.startswith('{'):decl.append(f'{typ} {name} = {v};')
            else:decl.append(f'{typ} {name} = {value(v)};')
            continue
        m=re.match(r'(?:상태/객체|전역 상태) ([\w.\[\]u]+): (.+)',line)
        if m:statements.append(f'{m[1]} = {value(m[2])};')
        m=re.match(r'외부 응답: BMS_(?:IsStringClosed|IsStringPrecharging|GetCurrentFlowDirection)\([^)]*\) → (\w+)',line)
        if m:
            name='pst_closed' if 'IsStringClosed' in line else 'pst_precharging' if 'IsStringPrecharging' in line else 'pst_direction'
            statements.append(f'{name}={m[1]};')
    # Sequential DOCX fixtures repeat declarations; initialize once per case.
    unique=[];seen=set()
    for d in decl:
        name=re.search(r'\b(\w+)\s*=',d)[1]
        if name not in seen:unique.append(d);seen.add(name)
    return unique,statements

def parse_call(c):
    lines=c['Inputs'].splitlines();f=lines[0].strip()
    if '단계' in f or ';' in c['SUT']:raise ValueError('Sequential multi-call contract needs explicit authoring')
    params=[]
    for line in lines[1:]:
        m=re.match(r'\d+번째 인수 \((.+)\): (.+)',line)
        if m:params.append(value(m[2]))
    if c['section']==11:
        f=c['SUT'];params=[]
        for line in lines:
            m=re.match(r'\d+(?:st|nd|rd) parameter.*?: (.+)',line)
            if m:params.append(value(m[1]))
    return f,params

def assertion_line(source,f,params):
    t=source.read_text(encoding='utf-8'); start=re.search(r'\b'+re.escape(f)+r'\s*\([^;{}]*\)\s*\{',t)
    if not start:raise ValueError('Cannot resolve original Assert function')
    body=t[start.end():]; assertions=list(re.finditer(r'FAS_ASSERT\(([^;]+)\);',body))
    if not assertions:raise ValueError('Expected Assert absent in production function')
    sig=t[start.start():start.end()];names=[re.findall(r'\w+',p)[-1] for p in sig[sig.index('(')+1:sig.rindex(')')].split(',')]
    chosen=None
    for i,p in enumerate(params):
        if p in ('NULL','NULL_PTR','1u','4294967295u') and i<len(names):
            chosen=next((a for a in assertions if re.search(r'\b'+names[i]+r'\b',a[1])),None)
            if chosen:break
    chosen=chosen or assertions[0]
    return t[:start.end()+chosen.start()].count('\n')+1

def checks(c,call):
    lines=[]
    for line in c['Expected'].splitlines():
        m=re.match(r'SUT 반환값\s*(?:=|:)\s*([^\s]+)',line)
        if m:lines.append(f'PST_EQ({call},{m[1]});')
        m=re.match(r'관찰값 (.+?) = (.+)',line)
        if m:lines.append(f'PST_EQ({m[1]},{value(m[2])});')
    return lines

manifest=[]; configs=[]
for source,cases in modules.items():
    key=source[:-2].replace('/','_').replace('-','_');directory=HERE/'app/application'/Path(source).parent
    directory.mkdir(parents=True,exist_ok=True)
    req=directory/'requirements';req.mkdir(exist_ok=True)
    (req/('document-cases-'+key+'.json')).write_text(json.dumps(cases,ensure_ascii=False,indent=2),encoding='utf-8')
    production=REPO/'src/app/application'/source
    test=directory/('test_'+Path(source).stem+'_document.c')
    prefix=['/* DOCX 4.1--4.11 PSTUnit; production unchanged. */','#include "application_contract.h"']
    if 'soc/counting' in source or 'soc/lookup-table' in source:prefix+=['#include "fram.h"']
    prefix += [f'#include "{Path(os.path.relpath(production,directory)).as_posix()}"',f'PST_SUITE({key});']
    reset=[]
    if source=='algorithm/config/algorithm_cfg.c':reset=['algo_algorithms[0].state=ALGO_UNINITIALIZED;']
    if source=='config/bal_cfg.c':reset=['bal_threshold_mV=BAL_DEFAULT_THRESHOLD_mV;']
    if '/soc/counting/' in '/'+source or '/soc/lookup-table/' in '/'+source:reset=['memset(&soc_state,0,sizeof(soc_state));','memset(&fram_soc,0,sizeof(fram_soc));']
    bodies=[]; implemented=[]
    for c in cases:
        row={**c,'module':key,'source':'src/app/application/'+source,'test_source':str(test.relative_to(HERE)),'native_test':c['Test ID'].replace('-','_'),'status':'Incomplete'}
        try:
            if c['section'] in [2,7,11] or ('/bal/' in '/'+source and source!='bal/bal.c'):raise ValueError('Requires module-specific state/callee authoring')
            f,params=parse_call(c);decl,init=setup(c)
            if '판정 보류' in c['Expected']:raise ValueError('Document explicitly defers this oracle')
            declared=set(re.findall(r'(?:상태/객체|전역 상태) (\w+) \(',c['Precondition']))
            for p in params:
                if p=='packVoltage_mV' and p not in declared:raise ValueError('DOCX input packVoltage_mV has no assigned value; do not infer from old tests')
            if 'socInitialized (내부 상태 관찰)' in f:init.append('soc_state.socInitialized=true;')
            if f=='socInitialized (내부 상태 관찰)':f='soc_state.socInitialized';call=f
            else:call=f+'('+','.join(params)+')'
            assert_source=production
            if c['section']==6:
                if 'StateOfCharge' in f:assert_source=REPO/'src/app/application/algorithm/state_estimation/soc/none/soc_none.c'
                elif 'StateOfEnergy' in f:assert_source=REPO/'src/app/application/algorithm/state_estimation/soe/none/soe_none.c'
                elif 'StateOfHealth' in f:assert_source=REPO/'src/app/application/algorithm/state_estimation/soh/none/soh_none.c'
                init += ['memset(&se_tableSocEstimation,0,sizeof(se_tableSocEstimation));se_tableSocEstimation.header.uniqueId=DATA_BLOCK_ID_SOC;',
                         'memset(&se_tableSoeEstimation,0,sizeof(se_tableSoeEstimation));se_tableSoeEstimation.header.uniqueId=DATA_BLOCK_ID_SOE;',
                         'memset(&se_tableSohEstimation,0,sizeof(se_tableSohEstimation));se_tableSohEstimation.header.uniqueId=DATA_BLOCK_ID_SOH;']
            pre=['pst_reset_contract();']+reset+decl+init
            expect_assert='SUT의 FAS_ASSERT 실패' in c['Expected']
            verify=[]
            if expect_assert:verify=[f'PST_EXPECT_SUT_ASSERT({call},{assertion_line(assert_source,f,params)});']
            else:
                verify=checks(c,call)
                result_checks=[v for v in verify if call in v]
                other_checks=[v for v in verify if call not in v]
                verify=(result_checks if result_checks else [call+';'])+other_checks
                if 'SOC_CheckDatabaseSocPercentageLimits'==f:
                    obj=params[0].lstrip('&');before=obj+'_before'
                    pre.append(f'DATA_BLOCK_SOC_s {before}={obj};')
                    for field in ['averageSoc_perc','minimumSoc_perc','maximumSoc_perc']:
                        x=f'{before}.{field}[0]';verify.append(f'PST_EQ({obj}.{field}[0],({x}<0?0:({x}>100?100:{x})));')
                    for field in ['chargeThroughput_As','dischargeThroughput_As']:verify.append(f'PST_EQ({obj}.{field}[0],{before}.{field}[0]);')
                if 'SOC_UpdateNvmValues'==f:
                    obj=params[0].lstrip('&')
                    for field in ['averageSoc_perc','minimumSoc_perc','maximumSoc_perc','chargeThroughput_As','dischargeThroughput_As']:verify.append(f'PST_EQ(fram_soc.{field}[0],{obj}.{field}[0]);')
                if 'StateOfEnergy' in c['SUT'] or 'StateOfHealth' in c['SUT'] or 'soc/debug' in source or 'soc/none' in source:
                    if params and params[0].startswith('&'):
                        obj=params[0][1:];pre.append(f'__typeof__({obj}) before={obj};')
                        if 'soh/debug' in source:
                            for field,num in [('averageSoh_perc','50.0f'),('minimumSoh_perc','49.9f'),('maximumSoh_perc','50.1f')]:verify.append(f'PST_EQ({obj}.{field}[0],'+('0.0f' if 'Initialize' in f else num)+');')
                        else:verify.append(f'PST_EQ(memcmp(&before,&{obj},sizeof(before)),0);')
                if 'soc_state.socInitialized=true' in c['Expected']:verify.append('PST_EQ(soc_state.socInitialized,true);')
                if c['section']==6:
                    verify.append('PST_EQ(pst_writes,'+('3' if f=='SE_RunStateEstimations' else '1')+');')
                    if f=='SE_RunStateEstimations':verify+=['PST_EQ(pst_written_ids[0],DATA_BLOCK_ID_SOC);','PST_EQ(pst_written_ids[1],DATA_BLOCK_ID_SOH);','PST_EQ(pst_written_ids[2],DATA_BLOCK_ID_SOE);']
                events=re.findall(r'외부 호출: DIAG_Handler\(([^\n]+)\)',c['Expected'])
                for i,args in enumerate(events):verify.append(f'pst_check_event({i},{args});')
                if events:verify.append(f'PST_EQ(pst_event_count,{len(events)});')
                for name,count in [('OS_EnterTaskCritical','pst_enter_calls'),('OS_ExitTaskCritical','pst_exit_calls')]:
                    n=c['Expected'].count('외부 호출: '+name+'(')
                    if n:verify.append(f'PST_EQ({count},{n});')
                if not any('PST_' in v or 'pst_check_event' in v for v in verify):raise ValueError('No concrete output/callee assessment authored')
            body='\n'.join('    '+x for x in pre+verify)
            bodies.append(f'/* {c["Test ID"]}: original Inputs/Expected, independent fixture. */\nPST_TEST({key},{row["native_test"]}) {{\n{body}\n}}\n')
            row['status']='Authored';implemented.append(row)
        except ValueError as ex:row['reason']=str(ex)
        manifest.append(row)
    if bodies:
        test.write_text('\n'.join(prefix+bodies),encoding='utf-8')
        cfg={'module':key,'source':str(production.relative_to(REPO)),'test':str(test.relative_to(HERE)),'case_count':len(bodies),'cases':[c['Test ID'] for c in implemented]}
        if source=='algorithm/config/algorithm_cfg.c':cfg['stubs']=['app/application/algorithm/config/stubs/stub_algorithm_cfg.c']
        if '/soc/counting/' in '/'+source or '/soc/lookup-table/' in '/'+source:
            cfg['stubs']=['support/host/application_storage.c'];cfg['dependencies']=['src/app/application/config/battery_cell_cfg.c']
        if source=='bal/bal.c':cfg['stubs']=['support/host/application_storage.c']
        if source=='soa/soa.c':cfg['stubs']=['app/application/soa/stubs/stub_soa_dependencies.c']
        if c['section']==6:
            cfg['stubs']=['support/host/application_storage.c']
            cfg['dependencies']=['src/app/application/algorithm/state_estimation/'+p for p in ['soc/none/soc_none.c','soe/none/soe_none.c','soh/none/soh_none.c']]
        configs.append(cfg)
(HERE/'requirements/case-manifest-application.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2),encoding='utf-8')
(HERE/'config/application_host.json').write_text(json.dumps({'modules':configs},indent=2),encoding='utf-8')
print('Authored',sum(r['status']=='Authored' for r in manifest),'of',len(manifest),'document cases; modules',len(configs))
