# Power arithmetic regression archive

`test_redundancy_power_arithmetic.c` contains the 13 PSTUnit cases added for
the integer power arithmetic correction from 2026-10-14. The target remains
`src/app/application/redundancy/redundancy.c`; these cases are not tests of a
separate production file named `power_fix.c`.

The corrected source SHA256 recorded with that run is
`533d42853bf4f9717862fccc960e729921f625b2ab8d8a24613de5bd14e895cd`.
Its historical pre-fix source SHA256 is
`8cd338327a83e2daf405b436046d6dd77bff951a1013e6f7b3d2a4a3bdd588db`.
These recorded historical files are distinct from the restored stock v1.11.0
hash. The corresponding original patch is preserved as `redundancy.patch`.

The contract is exact int64 multiplication of int32 current and voltage,
division by 1,000,000 with truncation toward zero, and invalidation/exclusion
when the result does not fit int32. A rejected result preserves the previous
numeric string power. Cases cover positive/negative/zero, fractional truncation,
exact int32 limits and out-of-range extremes.

These expectations are preserved without adaptation to stock v1.11.0.
The default runner's explicit source list excludes this directory. To activate
this archive later, first review/implement its production policy and select the
corrected source revision in a separate regression build; do not apply the patch
automatically or modify expectations to match the observed code.

The external dependencies and host compatibility come from the module's
`../../stubs/` and the shared `support/host/`. The relative SUT include resolves
to the repository production source. The historical suite/case IDs (`power_fix`)
remain unchanged.
