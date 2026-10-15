"""Build canonical PSTUnit sources; retain official results and exact commands."""
from pathlib import Path
import argparse
import csv
import datetime
import hashlib
import json
import os
import re
import shutil
import shlex
import subprocess
import xml.etree.ElementTree as ET

HERE = Path(__file__).resolve().parent
REPO = HERE.parent
MODULE = HERE / "app/application/redundancy"
HOST = HERE / "support/host"
CONFIG = json.loads((HERE / "config/redundancy_host.json").read_text(encoding="utf-8"))
WINDOWS = os.name == "nt"
EXE = ".exe" if WINDOWS else ""


def test_executable(ps):
    """Use the Linux Test Server installation, never the static product root."""
    names = ("polyspace-test.exe",) if WINDOWS else ("polyspace-test-server", "polyspace-test")
    for name in names:
        path = ps / "bin" / name
        if path.is_file():
            return path
    raise RuntimeError(f"Polyspace Test executable missing under {ps / 'bin'}: {', '.join(names)}")


def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def write_json(path, value):
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")


def validate():
    sut = REPO / CONFIG["sut"]
    content_hash = hashlib.sha256(sut.read_bytes().replace(b"\r\n", b"\n")).hexdigest()
    if sha(sut) != CONFIG["sut_sha256"] and content_hash != CONFIG.get("sut_lf_sha256"):
        raise RuntimeError("SUT differs from the v1.11.0 baseline; review contracts before execution.")
    all_ids = []
    for variant in CONFIG["variants"]:
        test = MODULE / variant["test"]
        text = test.read_text(encoding="utf-8")
        ids = re.findall(r"PST_TEST\(\s*redundancy\s*,\s*(\w+)\s*\)", text)
        if len(ids) != variant["case_count"]:
            raise RuntimeError(f"Unexpected case count: {test.name}")
        all_ids.extend(ids)
        included = re.search(r'#include "([^"]+\.c)"', text)
        if not included or (test.parent / included[1]).resolve() != sut.resolve():
            raise RuntimeError(f"Incorrect production source include: {test}")
    manifest = json.loads((MODULE / "requirements/case-manifest.json").read_text(encoding="utf-8"))
    if len(set(all_ids)) != 152 or set(all_ids) != {c["name"] for c in manifest}:
        raise RuntimeError("Missing or duplicate case IDs.")
    for relative in CONFIG["include_paths"] + CONFIG["real_dependencies"]:
        path = REPO / relative
        if not path.exists() or not path.resolve().is_relative_to(REPO.resolve()):
            raise RuntimeError(f"Invalid repository dependency: {relative}")
        if relative.startswith("src/bootloader") or relative.startswith("tests/"):
            raise RuntimeError(f"Forbidden production include/source: {relative}")
    section = json.loads((MODULE / "requirements/section-4.11.json").read_text(encoding="utf-8"))
    if sha(MODULE / "requirements" / section["document"]) != section["document_sha256"]:
        raise RuntimeError("Requirements document hash changed.")
    print("Validated 152 unique cases, source includes, repository dependencies and Word document.")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--compiler", help="Host GCC executable; otherwise PST_GCC/platform default")
    parser.add_argument("--polyspace-root", default=os.environ.get("POLYSPACE_ROOT"))
    parser.add_argument("--coverage", action="store_true", help="Collect MC/DC and relational boundary coverage")
    parser.add_argument("--validate-only", action="store_true")
    args = parser.parse_args()
    validate()
    if args.validate_only:
        return 0
    if not args.polyspace_root:
        state = (Path(os.environ["APPDATA"]) / "polyspace-agentic-toolkit/config.json" if WINDOWS
                 else Path.home() / ".config/polyspace-agentic-toolkit/config.json")
        if not WINDOWS:
            args.polyspace_root = "/opt/polyspace/dynamic/R2026b"
        elif not state.is_file():
            raise RuntimeError("Set POLYSPACE_ROOT or pass --polyspace-root with the R2026b installation directory.")
        else:
            args.polyspace_root = json.loads(state.read_text(encoding="utf-8"))["polyspaceRoot"]
    poly = Path(args.polyspace_root).resolve()
    if WINDOWS and poly != Path("C:/Polyspace/R2026b").resolve():
        raise RuntimeError("This workflow is configured for C:/Polyspace/R2026b.")
    ps = poly / "polyspace"
    pst = test_executable(ps)
    required = [pst, ps / "pstest/pstunit/src/pstest.c", ps / "pstest/pstunit/include/pstunit.h"]
    if args.coverage:
        required.append(ps / ("bin/polyspace-code-profiler" + EXE))
    for path in required:
        if not path.is_file():
            raise RuntimeError(f"Required R2026b tool/runtime missing: {path}")
    gcc = args.compiler or os.environ.get("PST_GCC")
    if not gcc:
        gcc = CONFIG["compiler_hint"] if WINDOWS and Path(CONFIG["compiler_hint"]).exists() else shutil.which("gcc")
    if not gcc:
        raise RuntimeError("Set PST_GCC or pass --compiler with the host GCC executable.")
    gcc = shutil.which(gcc) or (str(Path(gcc).resolve()) if Path(gcc).is_file() else None)
    if not gcc:
        raise RuntimeError("Configured compiler executable was not found.")
    timestamp = datetime.datetime.now().strftime("%Y%m%d-%H%M%S-%f")
    output = REPO / "build/polyspace_test" / timestamp
    output.mkdir(parents=True)
    commands = []
    exact = output / ("run-exact-commands.bat" if WINDOWS else "run-exact-commands.sh")
    exact.write_text("@echo off\nsetlocal enableextensions\n" if WINDOWS else "#!/usr/bin/env bash\nset -euo pipefail\n", encoding="utf-8")
    if not WINDOWS:
        exact.chmod(0o755)

    def run(argv, cwd=output, acceptable=(0,), timeout=240):
        argv = list(map(str, argv))
        print("RUN", Path(argv[0]).name, flush=True)
        try:
            result = subprocess.run(argv, cwd=cwd, capture_output=True, text=True,
                                    encoding="utf-8", errors="replace", timeout=timeout)
        except subprocess.TimeoutExpired as exc:
            write_json(output / "timeout-diagnostics.json", {"argv": argv, "cwd": str(cwd),
                       "stdout": str(exc.stdout), "stderr": str(exc.stderr)})
            raise
        commands.append({"argv": argv, "cwd": str(cwd), "exit_code": result.returncode,
                         "stdout": result.stdout, "stderr": result.stderr})
        write_json(output / "commands.json", commands)
        with exact.open("a", encoding="utf-8") as f:
            if WINDOWS:
                f.write('cd /d "' + str(cwd) + '"\n' + subprocess.list2cmdline(argv) + "\n")
                f.write("if errorlevel " + str(max(acceptable) + 1) + " exit /b %errorlevel%\n")
            else:
                f.write("cd -- " + shlex.quote(str(cwd)) + "\n")
                f.write("task_rc=0\n" + shlex.join(argv) + " || task_rc=$?\n")
                checks = " && ".join(f'[ "$task_rc" -ne {code} ]' for code in acceptable)
                f.write(f'if {checks}; then exit "$task_rc"; fi\n')
        if result.returncode not in acceptable:
            raise RuntimeError(f"Command failed ({result.returncode}): {argv[0]}\n{result.stderr[-4000:]}")
        return result

    version = run([gcc, "--version"]).stdout
    target = run([gcc, "-dumpmachine"]).stdout.strip()
    if WINDOWS and "mingw" not in target:
        raise RuntimeError(f"Expected MinGW host compiler, got {target}")
    if not WINDOWS and "linux" not in target:
        raise RuntimeError(f"Expected native Linux GCC target, got {target}")
    git = shutil.which("git")
    windows_git = Path("C:/Program Files/Git/cmd/git.exe")
    if WINDOWS and windows_git.exists():
        git = str(windows_git)
    if not git:
        raise RuntimeError("Git is required on PATH to record source revisions.")
    revision = run([git, "rev-parse", "HEAD"], cwd=REPO).stdout.strip()
    dirty = run([git, "status", "--porcelain", "--", "src/app", "src/os", "src/portable"], cwd=REPO).stdout
    profiler = ps / ("bin/polyspace-code-profiler" + EXE)
    manifest = {"baseline_version": CONFIG["baseline_version"], "baseline_commit": CONFIG["baseline_commit"],
                "actual_commit": revision, "production_worktree_changes": dirty,
                "polyspace_root": str(poly), "test_executable": str(pst), "compiler": str(gcc), "compiler_version": version,
                "target": target, "platform": os.name, "coverage": args.coverage, "language_standard": "c11", "variants": [],
                "host_adaptations": ["uintptr_t simulated PC token (0), not a TI location",
                "Expected asserts use setjmp/longjmp; unexpected asserts use validated PST_ABORT callback unwind",
                "FreeRTOS production headers supply types only; no OS/HAL implementation executed",
                "Clock macro deliberately undefined for executable hardware clock use",
                "Only the authorized empty foxbms_config.h is copied from tests/unit/support",
                "2-string battery_system_cfg.h is generated only in the build folder",
                "Production TI pragmas may be ignored by host GCC; warnings retained without broad suppression",
                "Static assertions enabled; UNITY_UNIT_TEST and DOCUMENTATION not defined"],
                "test_artifacts": {"TestSources": [v["test"] for v in CONFIG["variants"]],
                "ExternalStubSources": ["stubs/stub_redundancy_dependencies.c"],
                "HostForcedIncludes": ["support/host/host_compat.h"],
                "note": "Official PSTUnit CLI links the external stub artifact; no graphical project created."}}
    write_json(output / "build-manifest.json", manifest)

    def configuration(build, strings):
        inc = build / "include"
        inc.mkdir(parents=True, exist_ok=True)
        original = REPO / "src/app/application/config/battery_system_cfg.h"
        text, count = re.subn(r"(#define\s+BS_NR_OF_STRINGS\s+)\(1u\)",
                             rf"\g<1>({strings}u)", original.read_text(encoding="utf-8"), count=1)
        if count != 1:
            raise RuntimeError("Expected exactly one production string-count macro")
        if strings == 1:
            (inc / "battery_system_cfg.h").write_bytes(original.read_bytes())
        else:
            (inc / "battery_system_cfg.h").write_text(text, encoding="utf-8")
        (inc / "foxbms_config.h").write_bytes((REPO / "tests/unit/support/foxbms_config.h").read_bytes())
        (inc / "config_cpu_clock_hz.h").write_text(
            "/* Host OS types only; no hardware clock configured or executed. */\n"
            "#define HALCOGEN_CPU_CLOCK_HZ FOXBMS_PST_HARDWARE_CLOCK_NOT_AVAILABLE\n", encoding="utf-8")
        return inc

    def flags(inc):
        result = ["-std=c11", "-O0", "-g", "-Wall", "-Wextra", "-Werror=implicit-function-declaration",
                  "-DFAS_ASSERT_LEVEL=1", "-DPST_RETURN_ON_ABORT=0", "-DPST_REPORT_PASSED_ASSESSMENTS=1",
                  "-include", str(HOST / "host_compat.h"), "-include", str(inc / "battery_system_cfg.h")]
        result += [f"-D{k}={v}" for k, v in CONFIG["macros"].items()]
        paths = [inc, MODULE / "stubs"] + [REPO / p for p in CONFIG["include_paths"]]
        paths += [ps / "pstest/pstunit/include", ps / "psprofile/include"]
        for path in paths:
            result += ["-I", str(path)]
        return result

    probe = output / "abort-probe"
    inc = configuration(probe, 1)
    probe_source = HOST / "test_pst_abort_callback.c"
    run([pst, "-generate", "-main", "-registration", "-results-dir", probe,
         "-filename", "main.c", "-test-sources", probe_source])
    runtime = ps / "pstest/pstunit/src/pstest.c"
    run([gcc, *flags(inc), "-DPST_MONITOR_MODE", probe_source, probe / "main.c", runtime,
         "-o", probe / ("runner" + EXE)], cwd=probe)
    run([pst, "-monitor", "-results-dir", probe / "results", "--", probe / ("runner" + EXE)], cwd=probe, acceptable=(0, 1))
    run([pst, "-report", "-report-dir", probe / "report-xml", "-xml", probe / "results"], acceptable=(0, 1))
    probe_xml = next((probe / "report-xml").glob("**/pstunit/pstest_results.xml"))
    probe_tests = {t.get("name"): t for t in ET.parse(probe_xml).findall(".//Test")}
    if probe_tests["next_case_runs"].get("passed") != "true" or probe_tests["abort_in_callback"].get("incomplete") != "true":
        raise RuntimeError("PST_ABORT callback unwind probe failed")
    manifest["abort_probe"] = {k: t.attrib for k, t in probe_tests.items()}
    abi = probe / "host_abi.c"
    abi.write_text('#include <stdio.h>\n#include <stdint.h>\nint main(void) { '
                   'printf("pointer=%u int=%u long=%u uintptr_t=%u\\n", (unsigned)sizeof(void*), '
                   '(unsigned)sizeof(int), (unsigned)sizeof(long), (unsigned)sizeof(uintptr_t)); return 0; }\n')
    run([gcc, abi, "-o", probe / ("host_abi" + EXE)])
    manifest["host_abi"] = run([probe / ("host_abi" + EXE)]).stdout.strip()
    rows = []
    for variant in CONFIG["variants"]:
        strings = variant["strings"]
        build = output / f"strings-{strings}"
        inc = configuration(build, strings)
        test = MODULE / variant["test"]
        sources = [test, MODULE / "stubs/stub_redundancy_dependencies.c"]
        sources += [REPO / p for p in CONFIG["real_dependencies"]]
        run([pst, "-generate", "-main", "-registration", "-results-dir", build,
             "-filename", "generated_main.c", "-test-sources", test])
        sources += [build / "generated_main.c", runtime]
        compile_flags = flags(inc) + ["-DPST_MONITOR_MODE_WITH_PROFILING" if args.coverage else "-DPST_MONITOR_MODE"]
        current = {**variant, "flags": compile_flags,
                   "sources": [{"path": str(p), "sha256": sha(p)} for p in sources + [REPO / CONFIG["sut"]]],
                   "headers": [{"path": str(p), "sha256": sha(p)} for p in inc.glob("*.h")],
                   "original_battery_config_sha256": sha(REPO / "src/app/application/config/battery_system_cfg.h")}
        manifest["variants"].append(current)
        write_json(output / "build-manifest.json", manifest)
        objects = []
        for i, source in enumerate(sources):
            obj = build / f"source-{i}.o"
            objects.append(obj)
            command = [gcc, *compile_flags, "-c", source, "-o", obj]
            if args.coverage:
                command = [profiler, "-instrument", "-fail-if-error", "-instrum-dir", build / "instrum",
                           "-limit-instrumentation-to", REPO / "src", "-ignore-file", sources[1],
                           "-ignore-dir", HOST, "-ignore-file", build / "generated_main.c", "-ignore-dir", ps,
                           "-cov-metric-level", "mcdc", "-cov-relbound", "--", *command]
            run(command, cwd=build)
        nm = Path(gcc).parent / ("nm" + EXE)
        if nm.exists():
            run([nm, "-u", *objects], cwd=build)
        run([gcc, *objects, "-lm", "-o", build / ("runner" + EXE)], cwd=build)
        monitor = [pst, "-monitor", "-results-dir", build / "results"]
        if args.coverage:
            monitor += ["-instrum-dir", build / "instrum"]
        run([*monitor, "--", build / ("runner" + EXE)], cwd=build, acceptable=(0, 1))
        for fmt in ("xml", "html"):
            run([pst, "-report", "-report-dir", build / f"report-{fmt}", f"-{fmt}", build / "results"], acceptable=(0, 1))
        xml = next((build / "report-xml").glob("**/pstunit/pstest_results.xml"))
        tests = ET.parse(xml).findall(".//Test")
        if len(tests) != variant["case_count"]:
            raise RuntimeError("Official report case count differs from registered tests")
        for t in tests:
            status = "Incomplete" if t.get("incomplete") == "true" else "Pass" if t.get("passed") == "true" else "Fail"
            rows.append({"case": t.get("name"), "strings": strings, "status": status,
                         "failed_assessments": [{"expression": x.text, **x.attrib} for x in t.findall(".//FailedAssessments/Assessment")]})
    with (MODULE / "baseline-case-results.csv").open(encoding="utf-8-sig", newline="") as f:
        prior = {(r["case"], int(r["strings"])): r["status"] for r in csv.DictReader(f)}
    changes = []
    for row in rows:
        row["previous_status"] = prior[(row["case"], row["strings"])]
        if row["status"] != row["previous_status"]:
            changes.append(row)
    counts = {s: sum(r["status"] == s for r in rows) for s in ("Pass", "Fail", "Incomplete")}
    summary = {"total": len(rows), "counts": counts, "status_changes": changes,
               "all_case_ids_preserved": len({(r["case"], r["strings"]) for r in rows}) == 152,
               "functional_expectations_changed": False, "cases": rows}
    write_json(output / "result-summary.json", summary)
    write_json(output / "build-manifest.json", manifest)
    lines = ["# v1.11.0 Polyspace Test verification", "", f"152 cases: {counts}", "",
             f"Individual case status changes against baseline: {len(changes)}.", "",
             "Known failures remain failures; expected SUT asserts are passing conditions.", "",
             "| Case | Strings | Status | Previous |", "| --- | ---: | --- | --- |"]
    lines += [f'| {r["case"]} | {r["strings"]} | {r["status"]} | {r["previous_status"]} |' for r in rows]
    (output / "verification-report.md").write_text("\n".join(lines) + "\n", encoding="utf-8")
    print("RESULT", counts, "status changes:", len(changes), flush=True)
    print("ARTIFACTS", output, flush=True)
    return 1 if changes or counts["Incomplete"] else 0


if __name__ == "__main__":
    raise SystemExit(main())
