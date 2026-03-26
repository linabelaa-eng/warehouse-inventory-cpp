#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "User.h"

class Employee : public User {
private:
    string employeeId_;

public:
    Employee();
    Employee(const string &username,const string &passwordHash, const string &employeeId);
    string getRole() const override;
    string getEmployeeId() const override;

};

#endif