# Application unit-test specification

133 requirements;247 document scenarios;51 separately identified additional cases. Full Test ID, Requirement ID, SUT, Precondition, Mock, Inputs, Expected and code paths are in case-manifest-application.json. Original fields are preserved in application-4.1-4.11.json and CSV.

# Failure review and verification limits

298 specifications: 247 original document scenarios plus 51 additional cases.
291 native executions: 281 Pass, 10 Fail, 0 runtime Incomplete.
7 unresolved document cases are readiness Incomplete, not fabricated native tests.

| IDs (prefix F2-LLR-) | Classification | Evidence |
|---|---|---|
| ALG-070-02-ADD-001 | SUT error candidate | Extreme int32 subtraction in PL_CheckStringVoltage overflows and accepts a large voltage difference. |
| ALG-070-05-ADD-001 | SUT error candidate | Temperature valid count increments without reset on repeated spread checks. |
| ALG-036-06-ADD-001/002 | SUT error candidate | startTime!=0 and start+duration comparison disagree with required elapsed-time behavior at tick0/wrap. |
| ALG-046-TC-21-02/24-02 | Requirement ambiguity | Expected STD_OK lacks initializationFinished setup; untouched initial state yields STD_NOT_OK. |
| ALG-080-28-ADD-001 | SUT error candidate | Invalid power sensor with unusable fallback leaves previous valid flag, retaining it in Pack aggregation. |
| APP-SOE-001-05-ADD-005 / APP-SOE-001-03-ADD-001 | SUT error candidate | Manual energy equation divides by time instead of multiplying, followed by signed-to-unsigned conversion; +/-1A*1V*1hour fails +/-1Wh expectations. |
| ALG-080-29-ADD-001 | SUT error candidate | calculatePower persists across strings; string0 fallback overwrites string1 valid sensor123W. |

Production code and product Expected were not changed to pass failures. Test/environment corrections retained evidence: evaluation order, sequential duplicate declarations/first-step state, selected10mV PL boundary, DB block identity, Pack fixture reset, monitor CLI disabled, isolated selected-case generated registration, results-directory creation, and skipping single-file profile merge.

Unresolved document cases: ALG-014-TC-02 (explicitly deferred oracle), ALG-046-TC-19/22 (BAL_Init read contract), ALG-046-TC-20-02/23-02 (INITIALIZED precondition), ALG-070-TC-08/09 (unassigned packVoltage_mV). Questions are retained in polyspace_test/requirements/clarifications.md. Additional initializationFinished questions cover two native Fail cases.

Not all product clauses are certified. Requirement ALG-090-05 has an empty slave-temperature implementation and lacks complete per-sensor limit/event contracts. Traceability lists this gap. PL reclassification in the redundancy scheduling test is a controlled unit callee; PL calculation itself has separate production-SUT tests. Original state-estimation cases explicitly specify none strategies; these do not verify counting/debug algorithms. Host math/DB/FRAM/OS definitions model documented contracts, not real hardware.

All four coverage metrics are supported. coverage.csv records covered/total for each of23 configurations, from original production-file synthesis only; no-applicable metrics are0/0. Independent profiles are official union merges, never summed across cases. Two-string configuration modifies only a temporary copy of the production BS_NR_OF_STRINGS macro. Harness, mocks, headers and runtime are excluded from SUT aggregation. Source revisions, hashes, ABI, compiler/flags and diagnostics are preserved per run. Target IRQ/watchdog, persistent Assert storage, timing and hardware are outside host-unit evidence.
