# Test Results Summary

| ID    | Test Case                              | Category       | Status |
|-------|----------------------------------------|----------------|--------|
| TC01  | Valid manager login                    | Auth           |        |
| TC02  | Invalid login - lockout after 3 tries  | Auth           |        |
| TC03  | Add product - valid input              | Products       |        |
| TC04  | Add product - duplicate ID             | Products       |        |
| TC05  | Delete product - active order blocked  | Products       |        |
| TC06  | Delete employee - InProgress blocked   | Employees      |        |
| TC07  | Create order - insufficient stock      | Orders         |        |
| TC08  | Delete order - InProgress blocked      | Orders         |        |
| TC09  | Delete order - Completed blocked       | Orders         |        |
| TC10  | Complete order - stock deducted        | Orders         |        |
| TC11  | Employee cannot access manager menu    | Access Control |        |
| TC12  | Invalid numeric input handled          | Validation     |        |
| TC13  | Missing CSV files - auto created       | Reliability    |        |
