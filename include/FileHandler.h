#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <map>
#include <vector>
#include "User.h"
#include "Product.h"
#include "EmployeeRecord.h"
#include "Order.h"

using namespace std;

class FileHandler
{
private:
    string dataDir_;
    void ensureFileExists(const string& fileName, const string& header = "");
    void parseLine(const string& line, vector<string>& fields);
public:
    FileHandler();
    explicit FileHandler(const string& dataDir);
    bool loadUsers(map<string,User*>& out);
    bool saveUsers(const map<string,User*>& data);
    bool loadProducts(map<string,Product>& out);
    bool saveProducts(const map<string,Product>& data);
    bool loadEmployees(map<string,EmployeeRecord>& out);
    bool saveEmployees(const map<string,EmployeeRecord>& data);
    bool loadOrders(map<string,Order>& out);
    bool saveOrders(const map<string,Order>& data);
};

#endif //FILEHANDLER_H