#ifndef EMPLOYEERECORD_H
#define EMPLOYEERECORD_H

#include <string>
using namespace std;
class EmployeeRecord
{
private:
    string employeeId_;
    string name_;
    bool isDeleted_;
    public:
    EmployeeRecord();
    EmployeeRecord(const std::string& employeeId, const std::string& name);
    string getEmployeeId() const;
    string getName() const;
    void setEmployeeId(const string& employeeId);
    void setName(const string& name);
    bool isDeleted() const;
    void setDeleted(bool deleted);
};
#endif