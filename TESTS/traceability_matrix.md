# Requirement-Use Case Traceability Matrix

| Requirement                          | UC-01 | UC-05 | UC-09 | UC-13 | UC-17 | UC-18 | Priority | Test Mapping |
|--------------------------------------|-------|-------|-------|-------|-------|-------|----------|--------------|
| Manage products                      | X     |       |       |       |       |       | High     | TC03, TC04, TC05 |
| Manage employees                     |       | X     |       |       |       |       | High     | TC06, TC11   |
| Create and assign orders             |       |       | X     | X     |       |       | High     | TC07, TC10   |
| Employees complete orders            |       |       |       |       | X     | X     | High     | TC10, TC11   |
| Role-based access control            |       |       |       |       | X     |       | High     | TC01, TC11   |
| Input validation and error handling  | X     | X     | X     | X     | X     | X     | High     | TC12 + automated validator suite |
| Data persistence / startup recovery  |       |       |       |       |       |       | Medium   | TC13         |
| Report generation                    |       |       |       |       |       |       | Medium   | automated tests (`testReports`, `testReportFilteringDetailed`) |
| Soft delete and status constraints   | X     | X     | X     |       |       |       | High     | TC05, TC06, TC08, TC09 |

## Priority Scores

- UC-01 Add Product: High
- UC-09 Create Order: High
- UC-13 Assign Order: High
- UC-18 Complete Order: High
- Validation and reliability checks: High/Medium based on requirement criticality
