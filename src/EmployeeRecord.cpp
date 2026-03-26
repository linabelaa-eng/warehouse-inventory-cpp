#include "../include/EmployeeRecord.h"
using namespace std;

EmployeeRecord::EmployeeRecord() {}

EmployeeRecord::EmployeeRecord(const string& employeeId, const string& name)
    : employeeId_(employeeId), name_(name) {}

string EmployeeRecord::getEmployeeId() const { return employeeId_; }
string EmployeeRecord::getName() const { return name_; }
void EmployeeRecord::setEmployeeId(const string& employeeId) { employeeId_ = employeeId; }
void EmployeeRecord::setName(const string& name) { name_ = name; }