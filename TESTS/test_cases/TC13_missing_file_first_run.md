# TC13 - System initialises correctly when CSV files are missing

**Category:** Reliability
**Priority:** Medium
**Related Use Case:** NFR 4.2
**Type:** Black-box

## Precondition
All CSV data files have been deleted from the project directory.

## Steps
1. Delete all CSV files
2. Launch the application

## Expected Result
System starts without crashing and creates the missing
CSV files automatically.

## Actual Result
Application starts and initialises required data files when they are missing.

## Status
PASS

## Evidence
See /evidence/TC13_pass.png
