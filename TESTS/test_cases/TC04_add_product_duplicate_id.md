# TC04 - Add product with duplicate ID

**Category:** Product Management
**Priority:** High
**Related Use Case:** UC-01, NFR 3.1
**Type:** Black-box

## Test Data
- Product ID: P001 (already exists in the system)

## Steps
1. Log in as manager
2. Select Product Management -> Add Product
3. Enter Product ID: P001

## Expected Result
System rejects the entry and displays a duplicate ID error message.

## Actual Result
System blocks the duplicate Product ID and shows an error message.

## Status
PASS

## Evidence
See /evidence/TC04_pass.png
