"""Select latest actual case results while retaining all prior run evidence."""
from pathlib import Path
import json,hashlib,datetime,xml.etree.ElementTree as ET
from platform_tools import requirements_document
HERE=Path(__file__).resolve().parent;REPO=HERE.parent
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def save(p,d):p.write_text(json.dumps(d,ensure_ascii=False,indent=2),encoding='utf-8')
paths=sorted((REPO/'build/polyspace_test').glob('application-*'))
out=REPO/'build/polyspace_test'/datetime.datetime.now().strftime('application-final-%Y%m%d-%H%M%S');out.mkdir()
latest={};runs={};history=[]
for path in paths:
 if not (path/'results.json').exists() or path.name.startswith('application-final'):continue
 data=json.loads((path/'results.json').read_text(encoding='utf-8'))
 unique={}
 for row in data:
  if row.get('native_test'):
   key=(row['module'],row['native_test']);unique.setdefault(key,[]).append(row)
 for key,rs in unique.items():
  if len(rs)!=1:continue # rejected pre-fix monitor selections are historical only
  row=rs[0];latest[key]={**row,'run_directory':str(path)};runs[key]=path
  history.append({'module':key[0],'native_test':key[1],'status':row['status'],'run_directory':str(path)})
save(out/'results.json',list(latest.values()));save(out/'execution-history.json',history)
selected={}
for key,path in runs.items():selected.setdefault(key[0],set()).add(str(path))
# Retain only the latest full module profile plus genuinely separate newer case
# profiles; old profiles with obsolete fixtures are not unioned into the baseline.
for module,items in selected.items():
 full=[p for p in items if (Path(p)/module/'results/pstest_results.psprof').exists()]
 if full:
  newest=max(full);selected[module]={p for p in items if p>=newest}
save(out/'selected-modules.json',{k:sorted(v) for k,v in selected.items()})
checks=[]
for path in sorted(set(runs.values())):
 integrity=path/'integrity.json'
 if integrity.exists():checks.append({'run':str(path),**json.loads(integrity.read_text(encoding='utf-8'))})
documents=json.loads((HERE/'requirements/application-4.1-4.11.json').read_text(encoding='utf-8'))
save(out/'integrity.json',{'document_sha256':sha(requirements_document()),'document_unchanged':sha(requirements_document())==documents['document_sha256'],'run_integrity':checks})
save(HERE/'verification-application-summary.json',{'result_directory':str(out),'case_manifest':'requirements/case-manifest-application.json','native_result_count':len(latest),'updated_document_sha256':documents['document_sha256']})
print(out)
