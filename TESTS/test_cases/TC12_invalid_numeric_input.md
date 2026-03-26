# TC12 - Enter text where a number is expected

**Category:** Input Validation
**Priority:** Medium
**Related Use Case:** NFR 4.1
**Type:** Black-box

## Steps
1. Log in as manager
2. Select Add Product
3. When prompted for Quantity, enter: abc

## Expected Result
System displays an error message and prompts for re-entry
without crashing.

## Actual Result
Invalid text input is rejected with an error message and the program remains stable.

## Status
PASS

## Evidence
See /evidence/TC12_pass.png
