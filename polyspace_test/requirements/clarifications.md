# Updated DOCX questions and remaining verification gaps

The source DOCX and production code are unchanged. Existing IDs are preserved.

| Test ID | Missing contract / question | Treatment |
|---|---|---|
| ALG-014-TC-02 | DOCX explicitly defers mismatched MIN_MAX object/normal SOC oracle | Readiness Incomplete; no executable dummy test |
| ALG-070-TC-08 / TC-09 | `packVoltage_mV` has no assigned value in either independent scenario | Readiness Incomplete; requested actual input values |
| ALG-046-TC-19 / TC-22 | Expected DB read is absent from the stated BAL_Init API; a strategy step may be intended | Requested whether test includes a different/preceding strategy call |
| ALG-046-TC-20-02 / TC-23-02 | INITIALIZED expected but initial state/transition is not specified | Requested state setup; no inferred initialization |
| ALG-046-TC-21-02 / TC-24-02 | STD_OK expected but initializationFinished setup is not specified | Native result recorded separately; failure classified as requirement ambiguity |

All IDs in this table have prefix `F2-LLR-`. Document review topics RV-02,
RV-03, RV-06 and RV-07 are not resolved from current implementation or earlier
conversation policy; the updated DOCX is the selected baseline. DB failure
propagation, final post-spread voltage aggregate consistency and both-invalid
negative-temperature payload policy require independent decisions.

The newly authored additional cases improve specific gaps but do not certify
every clause of the 133 requirements. `requirements-traceability.json` lists
requirements with no linked test. SOA slave-temperature behavior is currently
an empty implementation; meaningful per-sensor diagnostic expectations need a
complete limit/event contract. Hardware behavior, RTOS, target interrupt disable,
watchdog reset and target performance are not verified by these host unit tests.

Test-authoring corrections are recorded without changing product requirements:
SUT call occurs before output state checks; duplicate declarations across
sequential document steps are merged; first-step state is preserved until the
next actual call; selected PL voltage tolerance is 10mV, not the initially
assumed100mV. Initial build/reporting failures and native failures remain in
the corresponding timestamped build directories.
