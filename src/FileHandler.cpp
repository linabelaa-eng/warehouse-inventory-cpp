#include "../include/FileHandler.h"
#include "../include/Manager.h"
#include "../include/Employee.h"
#include "../include/Order.h"
#include "../include/OrderItem.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
using namespace std;

FileHandler::FileHandler() : dataDir_("") {}

FileHandler::FileHandler(const string& dataDir) : dataDir_(dataDir) {
    if (!dataDir_.empty() && dataDir_.back() != '/' && dataDir_.back() != '\\')
        dataDir_ += '/';
}

void FileHandler::ensureFileExists(const string& filename, const string& header) {
    if (filename.empty()) return;
    ifstream f(filename);
    if (!f.good()) {
        ofstream out(filename);
        if (!out.good())
            throw runtime_error("Could not create file: " + filename);
        if (!header.empty())
            out << header << "\n";
    }
}

void FileHandler::parseLine(const string& line, vector<string>& fields) {
    fields.clear();
    istringstream iss(line);
    string field;
    while (getline(iss, field, ','))
        fields.push_back(move(field));
}

bool FileHandler::loadUsers(map<string, User*>& out) {
    for (auto& p : out) { delete p.second; }
    out.clear();
    try {
        const string path = dataDir_ + "users.csv";
        ensureFileExists(path, "username,passwordHash,role,employeeId");
        ifstream f(path);
        if (!f.is_open()) return false;
        string line;
        getline(f, line);
        vector<string> fields;
        while (getline(f, line)) {
            if (line.empty()) continue;
            parseLine(line, fields);
            if (fields.size() >= 4) {
                const string& role = fields[2];
                if (role == "Manager")
                    out[fields[0]] = new Manager(fields[0], fields[1]);
                else
                    out[fields[0]] = new Employee(fields[0], fields[1], fields[3]);
            }
        }
        return !f.bad();
    } catch (const exception&) {
        return false;
    }
}

bool FileHandler::saveUsers(const map<string, User*>& data) {
    try {
        ofstream f(dataDir_ + "users.csv");
        if (!f.is_open()) return false;
        f << "username,passwordHash,role,employeeId\n";
        for_each(data.begin(), data.end(), [&f](const map<string, User*>::value_type& p) {
            if (p.second)
                f << p.second->getUsername() << "," << p.second->getPasswordHash() << ","
                  << p.second->getRole() << "," << p.second->getEmployeeId() << "\n";
        });
        return f.good();
    } catch (const exception&) {
        return false;
    }
}

bool FileHandler::loadProducts(map<string, Product>& out) {
    out.clear();
    try {
        const string path = dataDir_ + "products.csv";
        ensureFileExists(path, "id,name,quantity,aisle,shelf,price");
        ifstream f(path);
        if (!f.is_open()) return false;
        string line;
        getline(f, line);
        vector<string> fields;
        while (getline(f, line)) {
            if (line.empty()) continue;
            parseLine(line, fields);
            if (fields.size() >= 6) {
                int qty = 0;
                double pr = 0.0;
                try {
                    qty = stoi(fields[2]);
                    pr  = stod(fields[5]);
                } catch (const invalid_argument&) { continue; }
                  catch (const out_of_range&)     { continue; }
                if (qty < 0) qty = 0;
                if (pr  < 0) pr  = 0;
                out[fields[0]] = Product(fields[0], fields[1], qty, fields[3], fields[4], pr);
            }
        }
        return !f.bad();
    } catch (const exception&) {
        return false;
    }
}

bool FileHandler::saveProducts(const map<string, Product>& data) {
    try {
        ofstream f(dataDir_ + "products.csv");
        if (!f.is_open()) return false;
        f << "id,name,quantity,aisle,shelf,price\n";
        for_each(data.begin(), data.end(), [&f](const map<string, Product>::value_type& p) {
            f << p.second.getId()       << "," << p.second.getName()    << ","
              << p.second.getQuantity() << "," << p.second.getAisle()   << ","
              << p.second.getShelf()    << "," << p.second.getPrice()   << "\n";
        });
        return f.good();
    } catch (const exception&) {
        return false;
    }
}

bool FileHandler::loadEmployees(map<string, EmployeeRecord>& out) {
    out.clear();
    try {
        const string path = dataDir_ + "employees.csv";
        ensureFileExists(path, "employeeId,name");
        ifstream f(path);
        if (!f.is_open()) return false;
        string line;
        getline(f, line);
        vector<string> fields;
        while (getline(f, line)) {
            if (line.empty()) continue;
            parseLine(line, fields);
            if (fields.size() >= 2)
                out[fields[0]] = EmployeeRecord(fields[0], fields[1]);
        }
        return !f.bad();
    } catch (const exception&) {
        return false;
    }
}

bool FileHandler::saveEmployees(const map<string, EmployeeRecord>& data) {
    try {
        ofstream f(dataDir_ + "employees.csv");
        if (!f.is_open()) return false;
        f << "employeeId,name\n";
        for_each(data.begin(), data.end(), [&f](const map<string, EmployeeRecord>::value_type& p) {
            f << p.second.getEmployeeId() << "," << p.second.getName() << "\n";
        });
        return f.good();
    } catch (const exception&) {
        return false;
    }
}

bool FileHandler::loadOrders(map<string, Order>& out) {
    out.clear();
    try {
        string path = dataDir_ + "orders.csv";
        ensureFileExists(path, "orderId,status,assignedEmployeeId");
        ifstream f(path);
        if (!f.is_open()) return false;
        string line;
        getline(f, line);
        vector<string> fields;
        while (getline(f, line)) {
            if (line.empty()) continue;
            parseLine(line, fields);
            if (fields.size() >= 3 && out.find(fields[0]) == out.end())
                out[fields[0]] = Order(fields[0], fields[1], fields[2]);
        }
        path = dataDir_ + "order_items.csv";
        ensureFileExists(path, "orderId,productId,quantity");
        ifstream fi(path);
        if (fi.is_open()) {
            getline(fi, line);
            while (getline(fi, line)) {
                if (line.empty()) continue;
                parseLine(line, fields);
                if (fields.size() >= 3) {
                    auto it = out.find(fields[0]);
                    if (it != out.end()) {
                        int q = 0;
                        try { q = stoi(fields[2]); } catch (const exception&) { continue; }
                        if (q > 0) it->second.addItem(OrderItem(fields[1], q));
                    }
                }
            }
        }
        return !f.bad();
    } catch (const exception&) {
        return false;
    }
}

bool FileHandler::saveOrders(const map<string, Order>& data) {
    try {
        ofstream f(dataDir_ + "orders.csv");
        if (!f.is_open()) return false;
        f << "orderId,status,assignedEmployeeId\n";
        for_each(data.begin(), data.end(), [&f](const map<string, Order>::value_type& p) {
            f << p.second.getOrderId() << "," << p.second.getStatus() << ","
              << p.second.getAssignedEmployeeId() << "\n";
        });
        if (!f.good()) return false;
        ofstream fi(dataDir_ + "order_items.csv");
        if (!fi.is_open()) return false;
        fi << "orderId,productId,quantity\n";
        for_each(data.begin(), data.end(), [&fi](const map<string, Order>::value_type& p) {
            for (const auto& item : p.second.getItems())
                fi << p.second.getOrderId() << "," << item.getProductId() << ","
                   << item.getQuantity() << "\n";
        });
        return fi.good();
    } catch (const exception&) {
        return false;
    }
}