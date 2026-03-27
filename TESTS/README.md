# Tests

This folder contains the **test source code** (`test_main.cpp`): a small executable test runner (no external test framework).

Submission layout (repository root): `SRC/` (application code), `TESTS/` (this folder), `BUILD/` (CMakeLists).

## How to build and run

### CLion

1. Open the project.
2. Build the `WarehouseTests` target.
3. Run `WarehouseTests`.

### Terminal (PowerShell, from the project root)

```powershell
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug --target WarehouseTests
.\cmake-build-debug\WarehouseTests.exe
```

The program prints `[PASS]` / `[FAIL]` for each check. It exits with code `0` if all tests pass, and `1` if any test fails.
