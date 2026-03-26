# TC02 - Invalid login with lockout after 3 attempts

**Category:** Authentication
**Priority:** High
**Related Use Case:** NFR 2.3
**Type:** Black-box

## Test Data
- Username: wronguser
- Password: wrongpass (entered 3 times)

## Steps
1. Launch the application
2. Enter incorrect credentials
3. Repeat 3 times

## Expected Result
System displays an error after each attempt and terminates
the session after the third failure.

## Actual Result
Invalid credentials are rejected, and after the third failed attempt the program terminates.

## Status
PASS

## Evidence
See /evidence/TC02_pass.png
