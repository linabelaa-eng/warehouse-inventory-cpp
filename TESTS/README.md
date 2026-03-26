# Test Suite - Warehouse Inventory System

This project includes two testing layers:

1. **Documented UAT/manual tests** in `TESTS/test_cases/*.md`
2. **Executable source-code tests** in `TESTS/test_main.cpp`

## Build and Run (CLion - recommended)

1. Open the project in CLion.
2. Build target `WarehouseTests`.
3. Run `WarehouseTests`.

The runner prints `[PASS]` / `[FAIL]` and exits with:
- `0` when all tests pass
- `1` when any test fails

## Build and Run (Terminal, if CMake is installed)

```powershell
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug --target WarehouseTests
.\cmake-build-debug\WarehouseTests.exe
```

## Executable Test Coverage

`TESTS/test_main.cpp` covers:
- Authentication (`AuthManager` valid/invalid login)
- Product and Order model behaviour
- FileHandler round-trip save/load
- Report file generation and filtering
- Stock deduction on order completion
- Extensive input validator checks (including invalid input cases and expected error messages)

## Current Status

- Executable tests: **PASS** in latest local run.
- UAT test cases are documented per file under `TESTS/test_cases/`.
- Delete-operation UAT cases are now implemented and documented (product, employee, and order delete constraints).

## Testing Documents

- `TESTS/test_cases/`
- `TESTS/test_results_summary.md`
- `TESTS/traceability_matrix.md`
