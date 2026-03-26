# Test Results Summary

| ID    | Test Case                              | Category       | Status |
|-------|----------------------------------------|----------------|--------|
| TC01  | Valid manager login                    | Auth           | PASS   |
| TC02  | Invalid login - lockout after 3 tries  | Auth           | PASS   |
| TC03  | Add product - valid input              | Products       | PASS   |
| TC04  | Add product - duplicate ID             | Products       | PASS   |
| TC05  | Delete product - active order blocked  | Products       | PASS   |
| TC06  | Delete employee - InProgress blocked   | Employees      | PASS   |
| TC07  | Create order - insufficient stock      | Orders         | PASS   |
| TC08  | Delete order - InProgress blocked      | Orders         | PASS   |
| TC09  | Delete order - Completed blocked       | Orders         | PASS   |
| TC10  | Complete order - stock deducted        | Orders         | PASS   |
| TC11  | Employee cannot access manager menu    | Access Control | PASS   |
| TC12  | Invalid numeric input handled          | Validation     | PASS   |
| TC13  | Missing CSV files - auto created       | Reliability    | PASS   |

## Notes

- Delete flows are now implemented using soft delete rules and status constraints.
- Validator behaviour and expected error messages are covered in `TESTS/test_main.cpp`.
