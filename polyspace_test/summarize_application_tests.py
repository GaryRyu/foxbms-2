"""Native case traceability and production-file-only coverage, no result edits."""
from pathlib import Path
import argparse,json,csv,collections,xml.etree.ElementTree as ET,subprocess,hashlib
from platform_tools import EXE, WINDOWS, resolve_root, test_tool
HERE=Path(__file__).resolve().parent;REPO=HERE.parent;PS=resolve_root()/'polyspace/bin'
def save(p,d):p.write_text(json.dumps(d,ensure_ascii=False,indent=2),encoding='utf-8')
def main():
 global PS
 p=argparse.ArgumentParser();p.add_argument('--run');p.add_argument('--merge-coverage',action='store_true');p.add_argument('--polyspace-root');a=p.parse_args()
 root=resolve_root(a.polyspace_root);PS=root/'polyspace/bin'
 run=Path(a.run).resolve() if a.run else sorted((REPO/'build/polyspace_test').glob('application-*'))[-1]
 manifest=json.loads((HERE/'requirements/case-manifest-application.json').read_text(encoding='utf-8'));configs=json.loads((HERE/'config/application_host.json').read_text(encoding='utf-8'))['modules']
 native=json.loads((run/'results.json').read_text(encoding='utf-8'));rows=[];coverage=[]
 for c in manifest:
  matches=[r for r in native if r.get('module')==c['module'] and r.get('native_test')==c['native_test']]
  if len(matches)>1:raise RuntimeError('Duplicate execution result for '+c['Test ID'])
  row={**c,'execution_status':'Incomplete','result_origin':'specification readiness; not native runtime'}
  if matches:row.update(execution_status=matches[0]['status'],native_result=matches[0],result_origin='Official Polyspace Test')
  elif c['status']=='Authored':row['reason']='No matching native result; build/run diagnostics retained'
  if row['execution_status']=='Fail':
   if '046_TC_21_02' in c['native_test'] or '046_TC_24_02' in c['native_test']:row['failure_category']='Requirement ambiguity: initializationFinished precondition missing'
   else:row['failure_category']='SUT error candidate; requirement/fixture and native assessment evidence require review'
  rows.append(row)
 for cfg in configs:
  external=run/'selected-modules.json'
  selected=json.loads(external.read_text(encoding='utf-8')) if external.exists() else {}
  origins=selected.get(cfg['module'],[str(run)])
  if isinstance(origins,str):origins=[origins]
  builds=[]
  for origin in map(Path,origins):builds+=list(origin.glob(cfg['module']))+list(origin.glob(cfg['module']+'__*'))
  profiles=[b/'results/pstest_results.psprof' for b in builds if (b/'results/pstest_results.psprof').exists()]
  xmls=[]
  if a.merge_coverage and len(profiles)>1:
   dest=run/'coverage'/cfg['module'];dest.mkdir(parents=True,exist_ok=True)
   log=[]
   for cmd in [[PS/('polyspace-code-profiler'+EXE),'-merge','-results-dir',dest,*profiles],[test_tool(root),'-report','-report-dir',dest/'xml','-xml',dest]]:
    result=subprocess.run(list(map(str,cmd)),capture_output=True,text=True,encoding='utf-8',errors='replace',timeout=120)
    log.append({'argv':list(map(str,cmd)),'exit':result.returncode,'stdout':result.stdout,'stderr':result.stderr})
   save(dest/'commands.json',log);xmls=sorted((dest/'xml').glob('**/profiling/*.xml'))
  if not xmls and len(builds)==1:xmls=sorted((builds[0]/'report-xml').glob('**/profiling/*.xml'))
  metrics=None;expected=(REPO/cfg['source']).resolve()
  for xml in xmls:
   for directory in ET.parse(xml).getroot().findall('.//sourceroot/dir'):
    for file in directory.findall('file'):
     path=Path(directory.get('name'))/(file.get('basename')+'.'+file.get('extension'))
     if (str(path.resolve()).lower()==str(expected).lower() if WINDOWS else path.resolve()==expected):
      syn=file.find('metrics/codecov/synthesis')
      if syn is not None:metrics=syn.attrib
   if metrics:break
  for label,keys in [('Statement',['Statement']),('Decision',['Decision']),('Condition',['Condition']),('MC/DC',['MCDC','MC/DC','Mcdc'])]:
   val=next((metrics[k] for k in keys if metrics and k in metrics),None)
   # Absent metric on a supported instrumentation level can mean no applicable
   # conditions, not unsupported. Distinguish missing profile from empty metric.
   coverage.append({'module':cfg['module'],'source':cfg['source'],'metric':label,'supported':True,'covered':val.split('/')[0] if val else 0 if metrics else None,'total':val.split('/')[1] if val else 0 if metrics else None,'status':'Collected' if metrics else 'Not collected','notes':'SUT file synthesis only; condition or MC/DC absent in SUT synthesis is 0/0 at requested mcdc level' if metrics else 'Missing production profile; not claimed unsupported'})
 counts=collections.Counter(r['execution_status'] for r in rows);docrows=[r for r in rows if '-TC-' in r['Test ID']]
 save(run/'case-results.json',{'counts':dict(counts),'document_counts':dict(collections.Counter(r['execution_status'] for r in docrows)),'cases':rows})
 original=json.loads((HERE/'requirements/application-4.1-4.11.json').read_text(encoding='utf-8'))
 req_rows=[]
 for req in original['requirements']:
  linked=[r for r in rows if req['Requirement ID'] in r['Requirement ID'].splitlines()]
  req_rows.append({**req,'linked_tests':[r['Test ID'] for r in linked],'native_test_count':sum(r['result_origin']=='Official Polyspace Test' for r in linked),'status':'No linked test' if not linked else 'Linked; each test verifies its explicit expectations, not all parent clauses'})
 save(run/'requirements-traceability.json',req_rows)
 save(run/'coverage.json',coverage)
 fields=['Test ID','Requirement ID','SUT','Precondition','Mock','Inputs','Expected','execution_status','result_origin','reason','failure_category','test_source']
 with (run/'case-results.csv').open('w',encoding='utf-8-sig',newline='') as f:
  writer=csv.DictWriter(f,fieldnames=fields);writer.writeheader();writer.writerows([{k:r.get(k,'') for k in fields} for r in rows])
 with (run/'coverage.csv').open('w',encoding='utf-8-sig',newline='') as f:
  writer=csv.DictWriter(f,fieldnames=list(coverage[0]));writer.writeheader();writer.writerows(coverage)
 summary=['# Application 4.1–4.11 xUnit 실행 결과','',f'전체 명세 {len(rows)}개: {dict(counts)}. 문서 시나리오 {len(docrows)}개: '+str(dict(collections.Counter(r['execution_status'] for r in docrows)))+'.','',
 'PSTUnit C만 사용한다. 그래픽 테스트/psprjx는 만들지 않았다. 생산 .c 직접 포함은 사용자 승인한 내부 접근 방식이며 공식 static xUnit API라고 주장하지 않는다. 단위 의존 대역과 호스트 호환을 구분하며 TI HAL/RTOS는 실행하지 않는다. 기대 Assert는 기록 대역에서 위치를 확인하고 복귀한다. 타겟 무한 정지/IRQ/watchdog 검증은 아니다.','',
 '문서·세부 요구사항·코드 테스트·실행 결과를 case-results.csv로 연결한다. 미작성/문서 보류와 네이티브 Incomplete는 result_origin으로 구분한다. 산술 오류 후보는 실패로 보존하며 Expected나 생산 소스를 바꿔 통과시키지 않는다.','',
 '| Module | Native Pass | Fail | Incomplete |','|---|---:|---:|---:|']
 for cfg in configs:
  rs=[r for r in rows if r['module']==cfg['module']];cnt=collections.Counter(r['execution_status'] for r in rs)
  summary.append(f"| {cfg['module']} | {cnt['Pass']} | {cnt['Fail']} | {cnt['Incomplete']} |")
 summary+=['','커버리지: coverage.csv에 각 생산 SUT의 Statement/Decision/Condition/MC/DC 충족·전체를 저장한다. 임시 시험·Mock·헤더·런타임을 파일 집계에서 제외한다. 독립 프로세스 결과는 공식 profiler union으로 병합하며 테스트별 수를 더하지 않는다.','',
 '명령·경고·compiler/flags·현재 소스 해시·문서 해시는 commands.json 및 build-manifest.json, 보존 검증은 integrity.json을 참조한다. 실행 결과는 현재 호스트 구성의 관찰이며 모든 제품 기능/하드웨어 검증을 뜻하지 않는다.']
 (run/'verification-report.md').write_text('\n'.join(summary)+'\n',encoding='utf-8')
 print('SUMMARY',run,dict(counts))
if __name__=='__main__':main()
