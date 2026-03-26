# TC10 - Complete order and verify stock is deducted

**Category:** Order Management
**Priority:** High
**Related Use Case:** UC-18, NFR 3.2
**Type:** Black-box

## Precondition
Order ORD003 is assigned to employee E001 with status InProgress.
Product P001 has quantity 10.

## Steps
1. Log in as employee E001
2. Select Complete Order
3. Enter Order ID: ORD003
4. Log in as manager and view product P001

## Expected Result
Order is marked Completed. Product P001 stock is reduced
by the correct quantity.

## Actual Result
Assigned employee completes the order successfully, and product quantity is reduced accordingly.

## Status
PASS

## Evidence
See /evidence/TC10_pass.png
