# TC07 - Create order with insufficient stock

**Category:** Order Management
**Priority:** High
**Related Use Case:** UC-09, NFR 3.2
**Type:** Black-box

## Test Data
- Order ID: ORD099
- Product ID: P001 (available stock: 2)
- Quantity requested: 50

## Steps
1. Log in as manager
2. Select Order Management -> Create Order
3. Enter Order ID: ORD099
4. Enter Product ID: P001, Quantity: 50

## Expected Result
Order is rejected with an insufficient stock error message.

## Actual Result
Order creation is rejected with an insufficient stock message.

## Status
PASS

## Evidence
See /evidence/TC07_pass.png
