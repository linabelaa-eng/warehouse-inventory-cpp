#include"../include/ReportGenerator.h"
#include"../include/Product.h"
#include"../include/Order.h"
#include <fstream>
#include <algorithm>
#include <stdexcept>
using namespace std;
ReportGenerator::ReportGenerator(map<string, Product>* products, map<string, Order>* orders)
    : products_(products), orders_(orders) {
    if (!products_ || !orders_)
        throw invalid_argument("ReportGenerator: products and orders pointers must not be null.");
}
bool ReportGenerator::generateInventoryReport(const string& path){
    if (!products_)return false;
    if (path.empty())return false;
    try{
        ofstream f(path);
        if (!f.is_open())return false;
        f<<"id,name,quantity,aisle,shelf,price\n";
        for_each(products_->begin(),products_->end(),[&f](const map<string, Product>::value_type& p){
            f << p.second.getId() << "," << p.second.getName() << "," << p.second.getQuantity()
              << "," << p.second.getAisle() << "," << p.second.getShelf() << "," << p.second.getPrice() << "\n";
        });
        return f.good();}
    catch (const exception&) {
        return false;
    }
}
bool ReportGenerator::generateCompletedOrdersReport(const string& path) {
    if (!orders_) return false;
    if (path.empty()) return false;
    try {
        ofstream f(path);
        if (!f.is_open()) return false;
        f << "orderId,status,assignedEmployeeId\n";
        for_each(orders_->begin(), orders_->end(), [&f](const map<string, Order>::value_type& p) {
            if (p.second.getStatus() == "Completed")
                f << p.second.getOrderId() << "," << p.second.getStatus() << "," << p.second.getAssignedEmployeeId() << "\n";
        });
        return f.good();
    } catch (const exception&) {
        return false;
    }
}

bool ReportGenerator::generatePendingOrdersReport(const string& path) {
    if (!orders_) return false;
    if (path.empty()) return false;
    try {
        ofstream f(path);
        if (!f.is_open()) return false;
        f << "orderId,status,assignedEmployeeId\n";
        for_each(orders_->begin(), orders_->end(), [&f](const map<string, Order>::value_type& p) {
            const string& st = p.second.getStatus();
            if (st == "Pending" || st == "InProgress")
                f << p.second.getOrderId() << "," << p.second.getStatus() << "," << p.second.getAssignedEmployeeId() << "\n";
        });
        return f.good();
    } catch (const exception&) {
        return false;
    }
}

bool ReportGenerator::generateEmployeeReport(const string& path, const string& employeeId) {
    if (!orders_) return false;
    if (path.empty()) return false;
    try {
        ofstream f(path);
        if (!f.is_open()) return false;
        f << "orderId,status,assignedEmployeeId\n";
        for_each(orders_->begin(), orders_->end(), [&f, &employeeId](const map<string, Order>::value_type& p) {
            if (p.second.getAssignedEmployeeId() == employeeId)
                f << p.second.getOrderId() << "," << p.second.getStatus() << "," << p.second.getAssignedEmployeeId() << "\n";
        });
        return f.good();
    } catch (const exception&) {
        return false;
    }
}
