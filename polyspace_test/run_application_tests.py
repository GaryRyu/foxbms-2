"""Build/run application unit configurations with official PSTUnit and MinGW."""
from pathlib import Path
import argparse,datetime,json,hashlib,subprocess,os,sys,xml.etree.ElementTree as ET
import shlex
from platform_tools import WINDOWS, EXE, resolve_root, test_tool, compiler_tool, git_tool, requirements_document
HERE=Path(__file__).resolve().parent;REPO=HERE.parent
PS=resolve_root();BIN=PS/'polyspace/bin'
GCC=None
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def save(p,d):p.write_text(json.dumps(d,ensure_ascii=False,indent=2),encoding='utf-8')
def main():
 global PS,BIN,GCC
 parser=argparse.ArgumentParser();parser.add_argument('--module',action='append');parser.add_argument('--case',action='append');parser.add_argument('--coverage',action='store_true');parser.add_argument('--validate-only',action='store_true');parser.add_argument('--compiler');parser.add_argument('--polyspace-root');parser.add_argument('--requirements-doc');args=parser.parse_args()
 document=requirements_document(args.requirements_doc)
 PS=resolve_root(args.polyspace_root);BIN=PS/'polyspace/bin'
 config=json.loads((HERE/'config/application_host.json').read_text(encoding='utf-8'));old=json.loads((HERE/'config/redundancy_host.json').read_text(encoding='utf-8'))
 current=json.loads((HERE/'requirements/application-4.1-4.11.json').read_text(encoding='utf-8'))
 if sha(document)!=current['document_sha256']:raise RuntimeError('DOCX changed; review/extract fresh requirements before execution')
 if args.validate_only:
  current=json.loads((HERE/'requirements/application-4.1-4.11.json').read_text(encoding='utf-8'))
  assert sha(document)==current['document_sha256'],'DOCX changed; review/extract fresh requirements'
  for m in config['modules']:
   assert (REPO/m['source']).exists() and (HERE/m['test']).exists()
   for rel in m.get('stubs',[]):assert (HERE/rel).is_file(),rel
   for rel in m.get('dependencies',[]):assert (REPO/rel).is_file(),rel
  print('Validated current document,',len(config['modules']),'module configurations and source paths. No build/run performed.');return 0
 GCC=compiler_tool(args.compiler);PST=test_tool(PS);PROFILER=BIN/('polyspace-code-profiler'+EXE)
 required=[PS/'polyspace/pstest/pstunit/src/pstest.c',PS/'polyspace/pstest/pstunit/include/pstunit.h']
 if args.coverage:required += [PROFILER,PS/'polyspace/psprofile/include']
 for path in required:
  if not path.exists():raise RuntimeError(f'Required Polyspace runtime/tool missing: {path}')
 output=REPO/'build/polyspace_test'/datetime.datetime.now().strftime('application-%Y%m%d-%H%M%S-%f');output.mkdir(parents=True)
 commands=[];results=[]
 env=os.environ.copy();env['PATH']=str(GCC.parent)+os.pathsep+env['PATH']
 def run(argv,cwd,accepted=(0,),timeout=180):
  argv=list(map(str,argv));r=subprocess.run(argv,cwd=cwd,env=env,capture_output=True,text=True,encoding='utf-8',errors='replace',timeout=timeout)
  commands.append({'argv':argv,'cwd':str(cwd),'exit':r.returncode,'stdout':r.stdout,'stderr':r.stderr});save(output/'commands.json',commands)
  if r.returncode not in accepted:raise RuntimeError(r.stdout[-2500:]+r.stderr[-3500:])
  return r
 target=run([GCC,'-dumpmachine'],output).stdout.strip()
 if WINDOWS and 'mingw' not in target.lower():raise RuntimeError(f'Windows requires MinGW GCC, got {target}')
 if not WINDOWS and 'linux' not in target.lower():raise RuntimeError(f'Linux requires native Linux GCC, got {target}')
 manifest={'document':sha(document),'document_path':str(document),'sources':{str(p.relative_to(REPO)):sha(p) for p in (REPO/'src/app').rglob('*') if p.is_file()},'modules':config['modules'],'compiler':run([GCC,'--version'],output).stdout,'target':target,'actual_revision':run([git_tool(),'rev-parse','HEAD'],REPO).stdout.strip(),'polyspace_root':str(PS),'test_tool':str(PST),'platform':sys.platform}
 save(output/'build-manifest.json',manifest)
 include=output/'include';include.mkdir();(include/'foxbms_config.h').write_bytes((REPO/'tests/unit/support/foxbms_config.h').read_bytes())
 (include/'config_cpu_clock_hz.h').write_text('#define HALCOGEN_CPU_CLOCK_HZ FOXBMS_PST_HARDWARE_CLOCK_NOT_AVAILABLE\n')
 dirs=set(old['include_paths'])
 dirs.update(str(p.parent.relative_to(REPO)) for p in (REPO/'src/app').rglob('*.h'))
 # HAL headers absent in this checkout are deliberately not synthesized.
 flags=['-std=c11','-O0','-g','-Wall','-Wextra','-Werror=implicit-function-declaration','-DFAS_ASSERT_LEVEL=1','-DPST_RETURN_ON_ABORT=0','-DPST_REPORT_PASSED_ASSESSMENTS=1','-include',str(HERE/'support/host/host_compat.h')]
 flags += ['-D'+k+'='+v for k,v in old['macros'].items()]
 flags += ['-I'+str(include),'-I'+str(HERE/'support/host'),'-I'+str(PS/'polyspace/pstest/pstunit/include'),'-I'+str(PS/'polyspace/psprofile/include')]
 flags += ['-I'+str(REPO/p) for p in sorted(dirs)]
 save(output/'compile-settings.json',{'flags':flags,'standard':'c11','host':('Windows MinGW' if WINDOWS else 'Linux native GCC')+'; no HAL/OS execution','no_graphical_tests':True,'static_access':'approved .c direct inclusion'})
 abi=output/'host_abi.c';abi.write_text('#include <stdio.h>\n#include <stdint.h>\nint main(void){printf("pointer=%u uintptr_t=%u int=%u long=%u float=%u double=%u",(unsigned)sizeof(void*),(unsigned)sizeof(uintptr_t),(unsigned)sizeof(int),(unsigned)sizeof(long),(unsigned)sizeof(float),(unsigned)sizeof(double));return 0;}\n')
 run([GCC,abi,'-o',output/('host_abi'+EXE)],output);manifest['host_abi']=run([output/('host_abi'+EXE)],output).stdout;save(output/'build-manifest.json',manifest)
 # Fresh host safety probe: a production callback can abort one test while the
 # following native test still executes. Keep its expected Incomplete separate.
 probe=output/'abort-probe';probe.mkdir();source=HERE/'support/host/test_pst_abort_callback.c'
 run([PST,'-generate','-main','-registration','-results-dir',probe,'-filename','main.c','-test-sources',source],probe)
 run([GCC,*flags,'-DPST_MONITOR_MODE',source,probe/'main.c',PS/'polyspace/pstest/pstunit/src/pstest.c','-o',probe/('runner'+EXE)],probe)
 run([PST,'-monitor','-results-dir',probe/'results','--',probe/('runner'+EXE)],probe,(0,1))
 run([PST,'-report','-report-dir',probe/'xml','-xml',probe/'results'],probe,(0,1))
 probe_xml=next((probe/'xml').glob('**/pstunit/pstest_results.xml'));probe_results={t.get('name'):t.attrib for t in ET.parse(probe_xml).findall('.//Test')}
 if probe_results['next_case_runs'].get('passed')!='true' or probe_results['abort_in_callback'].get('incomplete')!='true':raise RuntimeError('Fresh callback abort/unwind probe failed')
 save(probe/'verification.json',probe_results)
 modules=[m for m in config['modules'] if not args.module or m['module'] in args.module]
 if args.case:modules=[{**m,'cases':[c for c in m['cases'] if c in args.case],'isolated_cases':True} for m in modules if any(c in args.case for c in m['cases'])]
 expanded=[]
 for m in modules:
  if m.get('isolated_cases'):
   for case in m['cases']:expanded.append({**m,'selected_case':case,'isolated_cases':False,'case_count':1})
  else:expanded.append(m)
 modules=expanded
 for m in modules:
  build=output/(m['module']+('__'+m['selected_case'].replace('-','_') if m.get('selected_case') else ''));build.mkdir();print('BUILD',build.name,m['case_count'],flush=True)
  try:
   module_flags=list(flags)
   if m.get('strings'):
    import re
    battery=REPO/'src/app/application/config/battery_system_cfg.h';variant=build/'battery_system_cfg.h'
    text,count=re.subn(r'(#define\s+BS_NR_OF_STRINGS\s+)\(1u\)',lambda x:x[1]+f'({m["strings"]}u)',battery.read_text(encoding='utf-8'),count=1)
    if count!=1:raise RuntimeError('Cannot map string variant to current production configuration')
    variant.write_text(text,encoding='utf-8');module_flags+=['-include',str(variant)]
   sources=[HERE/m['test'],HERE/'support/host/application_contract.c']
   if m.get('selected_case'):
    import re
    origin=sources[0];content=origin.read_text(encoding='utf-8');chosen=m['selected_case'].replace('-','_');blocks=[]
    for match in re.finditer(r'PST_TEST\(\s*\w+\s*,\s*(\w+)\s*\)\s*\{',content):
     pos=match.end();depth=1
     while depth:
      if content[pos]=='{':depth+=1
      elif content[pos]=='}':depth-=1
      pos+=1
     if match[1]!=chosen:blocks.append((match.start(),pos))
    for begin,end in reversed(blocks):content=content[:begin]+('\n'*content[begin:end].count('\n'))+content[end:]
    content=re.sub(r'#include "([^"\n]+\.c)"',lambda x:'#include "'+(origin.parent/x[1]).resolve().as_posix()+'"',content)
    isolated=build/'selected_case.c';isolated.write_text('#line 1 "'+origin.as_posix()+'"\n'+content,encoding='utf-8');sources[0]=isolated
   if m.get('stubs'):sources += [HERE/s for s in m['stubs']]
   if m.get('dependencies'):sources += [REPO/s for s in m['dependencies']]
   run([PST,'-generate','-main','-registration','-results-dir',build,'-filename','generated_main.c','-test-sources',sources[0]],build)
   sources += [build/'generated_main.c',PS/'polyspace/pstest/pstunit/src/pstest.c']
   objs=[]
   for i,s in enumerate(sources):
    obj=build/f'{i}.o';objs.append(obj)
    cmd=[GCC,*module_flags,'-DPST_MONITOR_MODE_WITH_PROFILING' if args.coverage else '-DPST_MONITOR_MODE','-c',s,'-o',obj]
    if args.coverage:
     profile=[PROFILER,'-instrument','-fail-if-error','-instrum-dir',build/'instrum','-cov-metric-level','mcdc']
     if i==0:
      # Instrument the included SUT; exclude named tests and report SUT file only.
      import re
      profile += ['-ignore-dir',PS,'-ignore-dir',HERE/'support']
      for name in re.findall(r'PST_TEST\(\s*(\w+)\s*,\s*(\w+)\s*\)',s.read_text(encoding='utf-8')):
       profile += ['-ignore-fcn','pst_autogen_p1_'+name[0]+'_p2_'+name[1]+'_test_fcn']
     else:profile += ['-ignore-file',s]
     cmd=[*profile,'--',*cmd]
    run(cmd,build)
   run([GCC,*objs,'-lm','-o',build/('runner'+EXE)],build)
   monitor=[PST,'-monitor','-results-dir',build/'results']
   if args.coverage:monitor+=['-instrum-dir',build/'instrum']
   if m.get('isolated_cases'):
    for case in m['cases']:
     native=case.replace('-','_');dest=build/'case-results'/native;dest.mkdir(parents=True)
     case_monitor=[PST,'-monitor','-results-dir',dest]
     if args.coverage:case_monitor+=['-instrum-dir',build/'instrum']
     run([*case_monitor,'--',build/('runner'+EXE),'-test',native],build,(0,1),120)
     for fmt in ['xml','html']:run([PST,'-report','-report-dir',dest/('report-'+fmt),'-'+fmt,dest],build,(0,1))
     xml=next((dest/'report-xml').glob('**/pstunit/pstest_results.xml'))
     for t in ET.parse(xml).findall('.//Test'):
      results.append({'module':m['module'],'native_test':t.get('name'),'status':'Incomplete' if t.get('incomplete')=='true' else 'Pass' if t.get('passed')=='true' else 'Fail','attributes':t.attrib,'failed_assessments':[{'expression':a.text,**a.attrib} for a in t.findall('.//FailedAssessments/Assessment')]})
    print('DONE',m['module'],flush=True);save(output/'results.json',results);continue
   run([*monitor,'--',build/('runner'+EXE)],build,(0,1),120)
   for fmt in ['xml','html']:run([PST,'-report','-report-dir',build/('report-'+fmt),'-'+fmt,build/'results'],build,(0,1))
   xml=next((build/'report-xml').glob('**/pstunit/pstest_results.xml'))
   for t in ET.parse(xml).findall('.//Test'):
    status='Incomplete' if t.get('incomplete')=='true' else 'Pass' if t.get('passed')=='true' else 'Fail'
    results.append({'module':m['module'],'native_test':t.get('name'),'status':status,'attributes':t.attrib,'failed_assessments':[{'expression':a.text,**a.attrib} for a in t.findall('.//FailedAssessments/Assessment')]})
   print('DONE',m['module'],flush=True)
  except Exception as e:
   (build/'error.txt').write_text(str(e),encoding='utf-8');results.append({'module':m['module'],'status':'Incomplete','reason':str(e)})
   print('INCOMPLETE',m['module'],str(e)[-400:],flush=True)
  save(output/'results.json',results)
 # Exact commands are replayable and native failures are not converted to success.
 import subprocess as sp
 bat=['@echo off','setlocal'] if WINDOWS else ['#!/usr/bin/env bash','set -eu']
 for c in commands:
  bat += ['cd /d '+sp.list2cmdline([c['cwd']]),sp.list2cmdline(c['argv'])] if WINDOWS else ['cd '+shlex.quote(c['cwd']),shlex.join(c['argv'])+(' || test $? -eq '+str(c['exit']) if c['exit'] else '')]
 script=output/('run-exact-commands.bat' if WINDOWS else 'run-exact-commands.sh')
 script.write_text('\n'.join(bat)+'\n',encoding='utf-8')
 if not WINDOWS:script.chmod(0o755)
 save(output/'integrity.json',{'production_unchanged':all(sha(REPO/p)==h for p,h in manifest['sources'].items()),'document_unchanged':sha(document)==manifest['document']})
 print('ARTIFACTS',output,flush=True)
 # A missing expected case is an execution error, never a silent successful run.
 requested=[(m['module'],m.get('selected_case',c).replace('-','_')) for m in modules for c in (m['cases'] if not m.get('selected_case') else [m['selected_case']])]
 observed=[(r['module'],r.get('native_test')) for r in results if r.get('native_test')]
 if len(observed)!=len(set(observed)) or set(requested)!=set(observed):
  save(output/'execution-completeness.json',{'requested':requested,'observed':observed,'missing':sorted(set(requested)-set(observed))})
  return 1
 return 1 if any(r['status']!='Pass' for r in results) else 0
if __name__=='__main__':raise SystemExit(main())
