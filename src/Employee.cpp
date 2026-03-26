#include "../include/Employee.h"
 Employee::Employee():User(),employeeId_(""){}
 Employee::Employee(const string& username, const string& passwordHash, const string& employeeId)    : User(username, passwordHash), employeeId_(employeeId) {}
 string Employee::getRole() const{ return "Employee"; }
 string Employee::getEmployeeId() const{return employeeId_;}

