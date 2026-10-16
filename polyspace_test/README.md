# Polyspace Test sources for foxBMS 2 v1.11.0

## Updated application requirements workflow (Windows)

The same application workflow is now the default on **Linux**:

```bash
export POLYSPACE_ROOT=/opt/polyspace/dynamic/R2026b
bash polyspace_test/run_tests.sh --validate-only
bash polyspace_test/run_tests.sh --coverage --compiler /usr/bin/gcc
```

Required: Python 3.9+, native Linux GCC, Git and Polyspace Test Server R2026b.
`--polyspace-root` overrides `POLYSPACE_ROOT`; `--compiler` overrides `PST_GCC`.
Linux selects `polyspace/bin/polyspace-test-server`, falling back to
`polyspace-test` when present. The static product installation is not used.
Do not use MinGW on Linux. The bundled byte-identical `requirements/source.docx`
removes any dependency on the original Windows workspace. `--requirements-doc`
can explicitly select a different document; validate it against the extracted
baseline before test execution.

Paths in module configuration are relative POSIX paths. Linux executable names
have no `.exe` suffix and exact replay commands are saved in
`run-exact-commands.sh`. Current host ABI and compiler diagnostics are measured
per run. Linux runtime results remain unverified here; the Windows baseline is
not a Linux pass guarantee. Known requirement failures remain visible, and the
runner returns nonzero for any Fail, missing test result or runtime Incomplete.

After a run, use its printed ARTIFACTS directory for traceability and coverage:

```bash
python3 polyspace_test/summarize_application_tests.py \
  --run build/polyspace_test/application-<timestamp> --merge-coverage
```

All test sources, unit dependency definitions, host adapters, module configuration,
authoring/reporting scripts and requirement traceability files are included in
the repository. Generated binaries, build directories, profiles and machine-local
verification summaries are not committed. Do not regenerate tests as part of
execution: regeneration is explicit and must preserve reviewed inputs/Expected.

The current default host runner targets DOCX sections 4.1–4.11 using **C
PSTUnit only**, without graphical tests or `.psprjx`. It covers all documented
SOC/SOE/SOH/balancing strategies in separate unit configurations. The remainder
of this README describes the historical redundancy-only workflow.

```bat
polyspace_test\run_tests.bat --validate-only
polyspace_test\run_tests.bat --coverage
polyspace_test\run_tests.bat --module redundancy_redundancy --coverage
```

`--legacy-redundancy` explicitly selects the historical runner. The new runner
returns a failure exit code for native Fail/Incomplete; matching historical
failures does not count as a successful product verification.

Canonical sources mirror `src/app/application` under `app/application`. The
updated document is preserved in `requirements/application-4.1-4.11.json` and
CSV files. `config/application_host.json` selects each unit source, test artifact
and dependencies. Per-module `requirements/` files retain original scenario
content. Existing Ceedling/Unity/CMock/CException tests are not used.

Internal static access uses the explicitly approved `.c` inclusion in the test
translation unit. This is a host C technique, not an official static-access
xUnit API. The SUT is not separately linked a second time. `UNITY_UNIT_TEST`
and `DOCUMENTATION` remain undefined. Hardware and RTOS implementations are
excluded; production headers provide types. Unit dependency definitions are
listed as external stub artifacts. Production configuration/LUT data may be
linked where required. Current source revisions/hashes and warnings are recorded
afresh rather than enforcing the historical redundancy hash.

Expected SUT Assert is intercepted in a test-only record callback and must occur
at the original check before dereference. It never becomes a normal-return
expectation. Unexpected Assert records a test failure and invokes validated
PST_ABORT; a separate callback probe verifies that subsequent tests run. These
host tests do not verify target interrupt disable, watchdog reset or persistent
Assert logging. Modules with inaccessible function-local static state are built
as independent case executables from temporary selected-case sources. Official
Polyspace generates main/registration; those files are not handwritten.

Results are saved under `build/polyspace_test/application-<timestamp>/`.
`commands.json`, `run-exact-commands.bat`, `build-manifest.json`, native results
and HTML/XML reports preserve actual evidence. Generate the final traceability
and production-only union coverage report with:

```bat
python polyspace_test\summarize_application_tests.py --run build\polyspace_test\application-<timestamp> --merge-coverage
```

`case-results.csv/json` separates authored/readiness status from native test
execution. `coverage.csv/json` reports Statement, Decision, Condition and MC/DC
from each production SUT file, excluding harness, mocks, headers and runtime.
Independent case coverage is union-merged using the official profiler, never
summed across cases. An absent applicable Condition/MC/DC metric is recorded
as 0/0 at the supported mcdc instrumentation level; a missing profile remains
uncollected and is not labeled unsupported.

Authoring scripts reproducibly extract the Word document and create generic,
module-specific and additional boundary cases. Regeneration is explicit because
it replaces the authored files; do not run it merely to execute tests. Unresolved
document inputs/preconditions remain visible and are not inferred from legacy
tests or SUT output. Production code and the source DOCX are never changed to
make a test pass.

## Linux execution

Use Bash, Python 3.9+, native Linux GCC, Git and **Polyspace Test Server R2026b for Linux**.
Run from any working directory; repository paths are resolved from the script.

```bash
export POLYSPACE_ROOT=/opt/polyspace/dynamic/R2026b
bash polyspace_test/run_tests.sh --validate-only
bash polyspace_test/run_tests.sh
bash polyspace_test/run_tests.sh --coverage
```

Alternatively pass `--polyspace-root /path/to/R2026b` directly. If unspecified,
the Linux default is `/opt/polyspace/dynamic/R2026b`. It selects
`polyspace/bin/polyspace-test-server` first (falls back to `polyspace-test`
only if that executable exists instead). Windows retains its toolkit configuration.
Linux does not use Windows installation/compiler paths or require MinGW.
Select GCC with `--compiler /usr/bin/gcc` or `PST_GCC`; otherwise use PATH's gcc.
`PST_PYTHON` selects a Python executable if `python3` is unsuitable.
All path arguments may contain spaces and are passed without shell evaluation.
For direct execution use `chmod +x polyspace_test/run_tests.sh` then
`./polyspace_test/run_tests.sh`; invoking with `bash` requires no execute bit.
Shell scripts use LF; `.gitattributes` preserves LF on checkout.

Static products are separate: `/opt/polyspace/static/R2026b/polyspace/bin/`
contains `polyspace-bug-finder-server` and `polyspace-code-prover-server`.
This dynamic-test runner does not use that static installation.
PSTUnit runtime/header files are resolved under the dynamic root's
`polyspace/pstest/pstunit/src/pstest.c` and `polyspace/pstest/pstunit/include/`.
Coverage additionally requires the dynamic root's `polyspace/bin/polyspace-code-profiler`
and `polyspace/psprofile/include/`; missing tools/runtime files produce an error
before compilation. Their presence and Server CLI behavior must be verified on
the Linux machine; the supplied Server executable path has not been run here.

The same 1-string/2-string source list, host adapters, requirements and expected
asserts apply on both platforms. No production code or expectations are changed
to accommodate Linux. Line-ending normalization allows the unchanged source's
LF or CRLF checkout; actual code differences still fail the baseline check.
The measured ABI, GCC target/version, actual revision, source hashes, warnings
and results are recorded per run. A Linux result may differ from the historical
MinGW baseline (for example, `long` is often 8 bytes on Linux); such differences
are reported, never converted into new expected values.

Linux outputs `runner` and `host_abi` without `.exe`, and writes
`build/polyspace_test/<timestamp>/run-exact-commands.sh` with quoted commands,
working directories and accepted exit codes. Windows continues to write `.bat`.
Both platforms preserve XML/HTML reports and `commands.json` diagnostics.
For the explicit `--legacy-redundancy` workflow, exit 0 means the 152 case statuses match the historical baseline with no
incomplete cases; the known 13 failures remain visible in reports. Exit 1 reports
a build/tool error or a changed/incomplete result. This is regression comparison,
not a claim that all product requirements pass.

Linux machine execution has not been verified here. Bash syntax/argument
forwarding and Windows regression execution were checked during preparation.

생산 소스 `src/<경로>/<이름>.c`의 시험은
`polyspace_test/<경로>/test_<이름>_<목적>.c`에서 관리합니다.
현재 대상은 `app/application/redundancy/redundancy.c`입니다.
숫자 접미사는 같은 목적의 시험을 추가로 분할할 때 사용합니다.

## 파일 역할

- `app/application/redundancy/test_redundancy_requirements.c`: 문서 4.11의 29개 시나리오와 추가 요구사항 시험, 총 137개.
- `app/application/redundancy/test_redundancy_multistring.c`: 2스트링 구성의 독립성 및 집계 시험 15개.
- 모듈의 `stubs/`: DB·OS·BMS·DIAG 및 assert 외부 의존성 대역과 호출/상태 계약. PSTUnit CLI에서는 시험 전용 링크 입력이며, 그래피컬 프로젝트에 등록할 때는 **Add Stub Source File / Stubs.Files**를 사용합니다.
- `support/host/`: 호스트 컴파일 호환 헤더 및 공식 PST_ABORT의 callback 복귀 검증. unit 대역과 구분합니다.
- 모듈의 `requirements/`: 원본 Word 문서, 4.11 추출 자료, 요구사항/시나리오 대응표와 Test ID 목록.
- 모듈의 `regressions/power_fix/`: 이후 전력 계산 수정 정책용 13개 시험. v1.11.0 기본 실행에는 포함하지 않습니다.
- `config/redundancy_host.json`: 재현 가능한 기준 소스 해시, 매크로, 상대 include 경로, 실제 의존성, 실행 구성.

시험 소스는 생산 firmware 소스 목록에 등록하지 않습니다. 기존 Waf는 `app`,
`bootloader`, `os`, `portable`을 명시적으로 순회하므로 이 폴더를 순회하지 않습니다.
생산 코드와 함께 이 폴더를 재귀 glob하는 새 빌드/분석을 추가할 때는
`polyspace_test/**`를 생산 입력에서 제외해야 합니다.

## 실행

Python 3.9 이상, MinGW GCC 및 Polyspace Test R2026b가 필요합니다.
현재 구성은 `C:/Polyspace/R2026b`를 사용합니다.

```bat
polyspace_test\run_tests.bat --validate-only
polyspace_test\run_tests.bat
polyspace_test\run_tests.bat --coverage
```

컴파일러는 `--compiler <gcc.exe>` 또는 `PST_GCC`로 지정할 수 있습니다.
미지정 시 기존 검증에 사용한 MinGW 경로, 이후 PATH의 gcc를 사용하며 실제 버전과
target을 기록합니다. 설치 경로는 `POLYSPACE_ROOT` 또는 toolkit state에서 읽습니다.
이 워크플로의 R2026b 설치 루트는 읽기 전용입니다.

기본 실행은 coverage 없이 공식 main/registration 생성, 별도 컴파일 및 링크,
monitor 실행, XML/HTML 보고서 생성을 수행합니다. `--coverage`는 MC/DC와
relational boundary를 계측합니다. SUT를 포함하는 테스트 번역 단위도 계측되므로
커버리지에서는 `redundancy.c`와 시험 harness를 구분해 해석해야 합니다.

생성물은 `build/polyspace_test/<실행시각>/`에 기록되며 `/build/`는 기존
`.gitignore`에 의해 제외됩니다. 실제 명령 전체는 `run-exact-commands.bat`,
stdout/stderr와 종료 코드는 `commands.json`, 컴파일 환경과 소스/생성 헤더 해시는
`build-manifest.json`, 개별 시험 비교는 `result-summary.json`에 남습니다.
`verification-report.md`와 두 구성의 `report-html/`, `report-xml/`에서 결과를 확인합니다.

## 기준과 판정

기준은 v1.11.0 커밋 `308028fb13d046ba29b98886895c2e17937b1437`이며
SUT SHA256은 `bb7490b557131072584f6e9bbc0a8eca639dd43b243b20aa6d07d921f2c0bf75`입니다.
실행 시 실제 checkout 커밋과 생산 폴더 변경 상태를 별도로 기록합니다.
SUT 해시가 다르면 먼저 요구사항과 계약을 검토하도록 실행을 중지합니다.
파일명/폴더에 버전별 복사본을 계속 늘리는 대신 Git으로 시험 변경 이력을 관리합니다.

기존 기본 시험 기록은 152개 중 139 Pass / 13 Fail / 0 Incomplete입니다.
기존 실패는 온도 유효 개수, 전력 validity/recovery 및 스트링 독립성 요구사항과
구현의 불일치이며 실패로 유지합니다. 실행 스크립트는 전체 ID와 개별 상태를
baseline과 비교합니다. 상태가 같고 incomplete가 없으면 재배치 검증이 성공한
것이며, 제품 요구사항이 모두 통과했다는 의미는 아닙니다.

기대 SUT assert는 해당 검사문에서 발생했을 때 통과 조건입니다. 예상 밖 assert는
검증 실패 및 PST_ABORT로 처리하며 뒤의 시험이 계속 실행되는지 별도 probe로
확인합니다. 타깃 interrupt 비활성화/무한루프를 Windows에서 실행하지 않습니다.
`__curpc`는 uintptr_t 크기의 0 토큰이며 실제 TI PC 주소가 아닙니다.
FreeRTOS 헤더는 타입 선언에만 사용하고 실제 RTOS/HAL은 링크하지 않습니다.
미정의 clock 토큰은 하드웨어 clock 사용이 도입되면 컴파일이 실패하게 합니다.

통합 경계를 확장할 때는 해당 실제 구현을 링크하고 같은 symbol의 unit Stub은
제외해야 합니다. 매크로를 끄는 것만으로 실제 구현이 공급되지는 않습니다.
기존 Ceedling/Unity/CMock/CException 시험 코드를 사용하지 않으며, 승인된 빈
`tests/unit/support/foxbms_config.h`만 생성 include 폴더에 원본 그대로 복사합니다.

## 이전 자료와 추적성

기존 workspace의 `polyspace/redundancy-tests`, `polyspace/power-fix-20261014`
결과는 수정하지 않고 과거 증적으로 남겼습니다. 새 실행은 이 폴더에 의존하지
않으며 시험 원본을 여기서 관리합니다. `migration-manifest.json`에 기존 복사본의
위치·해시, 선택된 원본 및 변경 내역을 기록했습니다.
파일명 변경으로 시험 ID는 바뀌지 않습니다. `case-manifest.json`은 PSTUnit ID를
유지하고 `verification-scenarios.csv`는 원문 Test ID를 보존합니다.

재배치 중 NULL assert 예상 줄 번호 14곳을 복원된 v1.11.0의 동일 검사문에 맞췄습니다.
`assert-location-changes.json`에 이전/현재 위치와 근거를 기록했습니다.
입력, 반환값, 구조체·전역 상태·외부 응답 및 기능 기대값은 변경하지 않았습니다.
원본 Word와 JSON/CSV는 요구사항 추적 자료이며 이번 작업에서 그래피컬 프로젝트의
Requirements 링크를 새로 생성한 것은 아닙니다.

공식 실행 workflow: [run-polyspace-test-xunit-tests SKILL.md](C:/Users/garyryu/.agents/skills/run-polyspace-test-xunit-tests/SKILL.md).
