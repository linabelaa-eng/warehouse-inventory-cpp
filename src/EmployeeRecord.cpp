#include "EmployeeRecord.h"

using namespace std;

EmployeeRecord::EmployeeRecord() : isDeleted_(false) {}

EmployeeRecord::EmployeeRecord(const string& employeeId, const string& name)
    : employeeId_(employeeId), name_(name), isDeleted_(false) {}
string EmployeeRecord::getEmployeeId() const { return employeeId_; }
string EmployeeRecord::getName() const { return name_; }
void EmployeeRecord::setEmployeeId(const string& employeeId) { employeeId_ = employeeId; }
void EmployeeRecord::setName(const string& name) { name_ = name; }
bool EmployeeRecord::isDeleted() const { return isDeleted_; }
void EmployeeRecord::setDeleted(bool deleted) { isDeleted_ = deleted; }