"""Read-only host tool resolution for Windows MinGW and Linux GCC."""
from pathlib import Path
import os, shutil

HERE = Path(__file__).resolve().parent
WINDOWS = os.name == 'nt'
EXE = '.exe' if WINDOWS else ''

def resolve_root(value=None):
    return Path(value or os.environ.get('POLYSPACE_ROOT') or
                ('C:/Polyspace/R2026b' if WINDOWS else '/opt/polyspace/dynamic/R2026b')).expanduser().resolve()

def test_tool(root):
    names = ['polyspace-test.exe'] if WINDOWS else ['polyspace-test-server', 'polyspace-test']
    for name in names:
        tool = root/'polyspace/bin'/name
        if tool.is_file():
            return tool
    raise RuntimeError(f'Polyspace Test executable missing under {root}/polyspace/bin: {names}')

def compiler_tool(value=None):
    chosen = value or os.environ.get('PST_GCC')
    if not chosen:
        chosen = ('C:/MinGW_W64_Distributions/MinGW-builds_POSIX_MSVCRT/mingw-w64-old/bin/gcc.exe'
                  if WINDOWS else 'gcc')
    found = shutil.which(chosen)
    if not found:
        raise RuntimeError(f'GCC executable not found: {chosen}')
    return Path(found).resolve()

def git_tool():
    preferred = Path('C:/Program Files/Git/cmd/git.exe')
    found = str(preferred) if WINDOWS and preferred.is_file() else shutil.which('git')
    if not found:
        raise RuntimeError('Git is required to record source revisions')
    return found

def requirements_document(value=None):
    if value:
        return Path(value).expanduser().resolve()
    # Bundled copy allows a standalone clone to validate on another machine.
    bundled = HERE/'requirements/source.docx'
    if bundled.is_file():
        return bundled
    return next(HERE.parents[1].glob('foxBMS2_*.docx'))
