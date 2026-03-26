# TC06 - Delete employee with an order in progress

**Category:** Employee Management
**Priority:** High
**Related Use Case:** UC-08
**Type:** Black-box

## Precondition
Employee E001 exists and has an order currently InProgress.

## Steps
1. Log in as manager
2. Select Employee Management -> Delete Employee
3. Enter Employee ID: E001

## Expected Result
Deletion is blocked and the relevant order ID is displayed
in an error message.

## Actual Result
Deletion is blocked when the employee has an assigned order with status InProgress, and the order ID is shown.

## Status
PASS

## Evidence
See /evidence/TC06_pass.png
