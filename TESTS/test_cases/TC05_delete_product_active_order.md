# TC05 - Delete product referenced by an active order

**Category:** Product Management
**Priority:** High
**Related Use Case:** UC-04
**Type:** Black-box

## Precondition
Product P001 exists and is referenced in a Pending or InProgress order.

## Steps
1. Log in as manager
2. Select Product Management -> Delete Product
3. Enter Product ID: P001
4. Confirm deletion

## Expected Result
Deletion is blocked and the relevant order ID is displayed
in an error message.

## Actual Result
Deletion is blocked when the product is referenced by an active order, and the blocking order ID is shown.

## Status
PASS

## Evidence
See /evidence/TC05_pass.png
