# Test Suite - Warehouse Inventory System

This project includes:

1. **Documented UAT tests** in `TESTS/test_cases/*.md`
2. **Executable source-code tests** in `TESTS/test_main.cpp`

## Build and Run (CLion - recommended)

Because your PowerShell may not have `cmake` in PATH, run tests from CLion:

1. Open the project in CLion
2. Build the `WarehouseTests` target
3. Run `WarehouseTests`

The runner prints `[PASS]` / `[FAIL]` lines and exits with:
- `0` when all tests pass
- `1` when any test fails

## Build and Run (Terminal, if CMake is installed)

```powershell
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug --target WarehouseTests
.\cmake-build-debug\WarehouseTests.exe
```

## Executable Test Coverage

`TESTS/test_main.cpp` currently covers:
- Authentication (valid/invalid login)
- Product + Order model behaviour
- FileHandler round-trip save/load
- Report generation file creation

## UAT Documentation

Detailed user-level/manual test cases remain in:
- `TESTS/test_cases/`
- `TESTS/test_results_summary.md`
- `TESTS/traceability_matrix.md`
