# TC08 - Delete an InProgress order

**Category:** Order Management
**Priority:** High
**Related Use Case:** UC-12
**Type:** Black-box

## Precondition
Order ORD001 exists and has status InProgress.

## Steps
1. Log in as manager
2. Select Order Management -> Delete Order
3. Enter Order ID: ORD001

## Expected Result
System displays: Cannot delete an order that is in progress.

## Actual Result
System rejects deletion and prints: Cannot delete an order that is in progress.

## Status
PASS

## Evidence
See /evidence/TC08_pass.png
