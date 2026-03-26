# Requirement-Use Case Traceability Matrix

| Requirement                   | UC-01 | UC-02 | UC-05 | UC-09 | UC-13 | UC-17 | UC-18 | Priority |
|-------------------------------|-------|-------|-------|-------|-------|-------|-------|----------|
| Manage products               |  X    |  X    |       |       |       |       |       | High     |
| Manage employees              |       |       |  X    |       |       |       |       | High     |
| Create and assign orders      |       |       |       |  X    |  X    |       |       | High     |
| Employees complete orders     |       |       |       |       |       |  X    |  X    | High     |
| Soft delete with constraints  |  X    |       |  X    |       |  X    |       |       | High     |
| Role-based access control     |       |       |       |       |       |  X    |       | High     |
| Report generation             |       |       |       |       |       |       |       | Medium   |

## Priority Scores
- UC-01 Add Product: High
- UC-09 Create Order: High
- UC-13 Assign Order: High
- UC-18 Complete Order: High
- UC-04 Delete Product: High (soft delete constraint)
- UC-08 Delete Employee: High (soft delete constraint)
- UC-12 Delete Order: High (soft delete constraint)
