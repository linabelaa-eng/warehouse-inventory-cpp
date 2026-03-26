# TC09 - Delete a Completed order

**Category:** Order Management
**Priority:** High
**Related Use Case:** UC-12
**Type:** Black-box

## Precondition
Order ORD002 exists and has status Completed.

## Steps
1. Log in as manager
2. Select Order Management -> Delete Order
3. Enter Order ID: ORD002

## Expected Result
System displays: Cannot delete a completed order - history must be preserved.

## Actual Result
System rejects deletion and prints: Cannot delete a completed order - history must be preserved.

## Status
PASS

## Evidence
See /evidence/TC09_pass.png
