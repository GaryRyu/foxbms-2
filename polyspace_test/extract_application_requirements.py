"""Extract current DOCX 4.1--4.11 verbatim; never import legacy tests."""
from pathlib import Path
import hashlib, json, re, csv, zipfile, xml.etree.ElementTree as ET
from platform_tools import requirements_document

HERE=Path(__file__).resolve().parent
DOC=requirements_document()
NS={'w':'http://schemas.openxmlformats.org/wordprocessingml/2006/main'}
root=ET.fromstring(zipfile.ZipFile(DOC).read('word/document.xml'))
def text(node):
    return '\n'.join(''.join((t.text or '') if t.tag.endswith('}t') else '\n' if t.tag.endswith(('}br','}cr')) else '' for t in p.iter()) for p in node.findall('.//w:p',NS))
section=0; requirements=[]; scenarios=[]; notes=[]; table_no=0
for node in root.find('w:body',NS):
    if node.tag.endswith('}p'):
        t=''.join(v.text or '' for v in node.findall('.//w:t',NS))
        match=re.match(r'4\.(\d+)(?:\.|\s)',t)
        if match:section=int(match[1])
        if 1<=section<=11 and t: notes.append({'section':section,'text':t})
    elif node.tag.endswith('}tbl'):
        table_no+=1
        if not 1<=section<=11:continue
        rows=[[text(c) for c in row.findall('w:tc',NS)] for row in node.findall('w:tr',NS)]
        if not rows:continue
        for row_no,row in enumerate(rows[1:],2):
            if rows[0][0]=='Requirement ID':
                requirements.append({'section':section,'Requirement ID':row[0],'Description':row[1], 'source_table':table_no,'source_row':row_no})
            elif rows[0][0]=='Test ID':
                scenarios.append(dict(zip(['Test ID','SUT','Requirement ID','Description','Precondition','Inputs','Expected'],row),section=section,source_table=table_no,source_row=row_no))
data={'document':'requirements/source.docx','document_sha256':hashlib.sha256(DOC.read_bytes()).hexdigest(), 'requirements':requirements,'scenarios':scenarios,'notes':notes}
out=HERE/'requirements';out.mkdir(exist_ok=True)
(out/'application-4.1-4.11.json').write_text(json.dumps(data,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
for name,rows in [('requirements',requirements),('scenarios',scenarios)]:
    with (out/(name+'.csv')).open('w',encoding='utf-8-sig',newline='') as f:
        writer=csv.DictWriter(f,fieldnames=list(rows[0]));writer.writeheader();writer.writerows(rows)
print('Extracted requirements:',len(requirements),'scenarios:',len(scenarios),'DOCX SHA256:',data['document_sha256'])
