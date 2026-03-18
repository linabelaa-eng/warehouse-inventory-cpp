
#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H
#include <string>
#include <map>
using namespace std;
class Product;
class Order;

class ReportGenerator {
    private:
    map<string,Product>* products_;
    map<string, Order>* orders_;
public:
    ReportGenerator(map<string,Product>* products, map<string,Order>* orders);
    bool generateInventoryReport(const string& path);
    bool generateCompletedOrdersReport(const string& path);
    bool generatePendingOrdersReport(const string& path);
    bool generateEmployeeReport(const string& path,const string& employeeId);
};

#endif