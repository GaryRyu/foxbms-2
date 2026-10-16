#!/usr/bin/env bash
# Application 4.1--4.11 native Linux host tests. --legacy-redundancy is explicit.
set -euo pipefail

# Dynamic Test Server is installed separately from Bug Finder/Code Prover.
export POLYSPACE_ROOT="${POLYSPACE_ROOT:-/opt/polyspace/dynamic/R2026b}"

task_script_dir="$(CDPATH= cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
task_python="${PST_PYTHON:-python3}"
if ! command -v "$task_python" >/dev/null 2>&1; then
    printf 'Python executable not found: %s\nSet PST_PYTHON or install Python 3.9+.\n' "$task_python" >&2
    exit 127
fi
"$task_python" -c 'import sys; sys.exit(0 if sys.version_info >= (3, 9) else "Python 3.9+ is required")'
exec "$task_python" "$task_script_dir/run_tests.py" "$@"
