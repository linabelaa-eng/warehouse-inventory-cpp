# Tests

This folder contains the **test source code** (`test_main.cpp`): a small executable test runner

Expected submission layout (repository root): **`SRC/`** (application code), **`TESTS/`** (this folder), **`BUILD/`** (CMake lists for targets).

## How to build and run

### CLion

1. Open the project (folder that contains the root `CMakeLists.txt`).
2. Build the **`WarehouseTests`** target.
3. Run **`WarehouseTests`**.

The program prints `[PASS]` / `[FAIL]` for each check. It exits with code **`0`** if all tests pass, and **`1`** if any test fails.
