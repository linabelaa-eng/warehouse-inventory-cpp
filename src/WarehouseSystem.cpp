#include "WarehouseSystem.h"
#include "AuthManager.h"
#include "User.h"
#include "Manager.h"
#include "Employee.h"
#include "FileHandler.h"
#include "Product.h"
#include "EmployeeRecord.h"
#include "Order.h"
#include "OrderItem.h"
#include "ReportGenerator.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <iomanip>
#include <functional>
using namespace std;

static const string DATA_DIR = "Testing";

static string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c){ return static_cast<char>(tolower(c)); });
    return s;
}

static string trimWhitespace(const string& s) {
    const string w = " \t\r\n";
    auto start = s.find_first_not_of(w);
    if (start == string::npos) return "";
    auto end = s.find_last_not_of(w);
    return s.substr(start, end - start + 1);
}

WarehouseSystem::WarehouseSystem()
    : authManager_(nullptr), reportGenerator_(nullptr), currentUser_(nullptr) {
    try {
        authManager_     = new AuthManager(&users_);
        reportGenerator_ = new ReportGenerator(&products_, &orders_);
    } catch (const exception& e) {
        if (reportGenerator_) { delete reportGenerator_; reportGenerator_ = nullptr; }
        if (authManager_)     { delete authManager_;     authManager_     = nullptr; }
        throw runtime_error(string("Failed to initialize system: ") + e.what());
    }
}

WarehouseSystem::~WarehouseSystem() {
    for (auto& p : users_) { delete p.second; }
    users_.clear();
    delete reportGenerator_;
    delete authManager_;
}

void WarehouseSystem::loadData() {
    FileHandler fh(DATA_DIR);
    if (fh.loadUsers(users_) && !users_.empty()) {
        // Ensure admin exists and admin/admin always works
        auto it = users_.find("admin");
        if (it == users_.end()) {
            users_["admin"] = new Manager("admin", authManager_->hashPassword("admin"));
            fh.saveUsers(users_);
        } else if (it->second) {
            it->second->setPasswordHash(authManager_->hashPassword("admin"));
            fh.saveUsers(users_);
        }
        fh.loadProducts(products_);
        fh.loadEmployees(employees_);
        fh.loadOrders(orders_);
        cout << "\n  Loaded from data files: " << users_.size()    << " users, "
             << products_.size()  << " products, "
             << employees_.size() << " employees, "
             << orders_.size()    << " orders.\n";
        cout << "  Logins: admin / admin (Manager), employee / employee (Employee).\n";
        return;
    }

    users_.clear(); products_.clear(); employees_.clear(); orders_.clear();

    users_["admin"] = new Manager("admin", authManager_->hashPassword("admin"));
    for (int i = 2; i <= 5; ++i) {
        string u = "manager" + to_string(i);
        users_[u] = new Manager(u, authManager_->hashPassword("admin"));
    }

    for (int i = 1; i <= 50; ++i) {
        string num  = to_string(i);
        string eid  = "E" + string(3 - num.size(), '0') + num;
        string name = "Employee " + num;
        employees_[eid] = EmployeeRecord(eid, name);
        string uname = (i == 1) ? "employee" : "employee" + num;
        users_[uname] = new Employee(uname, authManager_->hashPassword("employee"), eid);
    }

    string pnames[]   = {"Widget","Gadget","Tool","Component","Device",
                         "Module","Sensor","Cable","Adapter","Unit"};
    string variants[] = {"A","B","C","D","E","F","G","H","I","J"};
    string aisles[]   = {"A1","A2","B1","B2","C1","C2","D1","D2"};
    string shelves[]  = {"S1","S2","S3","S4","S5"};
    int idx = 0;
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j) {
            ++idx;
            string num = to_string(idx);
            string pid = "P" + string(3 - num.size(), '0') + num;
            products_[pid] = Product(pid, pnames[i] + " " + variants[j],
                                     10 + (idx*7)%191,
                                     aisles[idx%8], shelves[idx%5],
                                     5.0 + (idx*3)%95 + ((idx%4)*0.25));
        }

    vector<string> empIds, pids;
    for (auto& e : employees_) empIds.push_back(e.first);
    for (auto& p : products_)  pids.push_back(p.first);
    string statuses[] = {"Pending","InProgress","Completed"};

    for (int i = 1; i <= 67; ++i) {
        string num = to_string(i);
        string oid = "ORD" + string(3 - num.size(), '0') + num;
        string status = statuses[i % 3];
        string eid    = (status == "Pending") ? "" : empIds[i % empIds.size()];
        Order ord(oid, status, eid);
        int itemCount = 1 + (i % 3);
        for (int k = 0; k < itemCount; ++k)
            ord.addItem(OrderItem(pids[(i + k*7) % pids.size()], 1 + (k+i)%5));
        orders_[oid] = ord;
    }

    fh.saveUsers(users_);
    fh.saveProducts(products_);
    fh.saveEmployees(employees_);
    fh.saveOrders(orders_);

    cout << "\n  Default logins:\n    Manager:  admin / admin\n    Employee: employee / employee\n";
    cout << "\n  Generated: " << users_.size() << " users, " << products_.size()
         << " products, " << employees_.size() << " employees, " << orders_.size() << " orders.\n";
}

void WarehouseSystem::saveData() {
    FileHandler fh(DATA_DIR);
    fh.saveUsers(users_);
    fh.saveProducts(products_);
    fh.saveEmployees(employees_);
    fh.saveOrders(orders_);
}

// ── raw input ─────────────────────────────────────────────────────────────────

string WarehouseSystem::readLine(const string& prompt) {
    cout << "  " << prompt << "> ";
    cout.flush();
    string line;
    if (!getline(cin, line)) {
        if (cin.eof()) throw runtime_error("End of input.");
        cin.clear();
        return "";
    }
    return trimWhitespace(line);
}

int WarehouseSystem::readInt(const string& prompt, bool& inputValid) {
    inputValid = false;
    try {
        string s = readLine(prompt);
        size_t pos = 0;
        int v = stoi(s, &pos);
        inputValid = (pos == s.size());
        return v;
    } catch (...) {}
    return 0;
}

double WarehouseSystem::readDouble(const string& prompt, bool& inputValid) {
    inputValid = false;
    try {
        string s = readLine(prompt);
        size_t pos = 0;
        double v = stod(s, &pos);
        inputValid = (pos == s.size());
        return v;
    } catch (...) {}
    return 0.0;
}

// ── validated input helpers ───────────────────────────────────────────────────

string WarehouseSystem::readValidatedLine(const string& prompt,
                                          const string& hint,
                                          function<bool(const string&)> validator,
                                          int maxTries) {
    for (int attempt = 0; attempt < maxTries; ++attempt) {
        string val = readLine(prompt);
        if (validator(val))
            return val;
        int left = maxTries - attempt - 1;
        if (left > 0)
            cout << "  Try again (" << left << " attempt" << (left == 1 ? "" : "s")
                 << " left).  " << hint << "\n";
    }
    return "";
}

int WarehouseSystem::readValidatedInt(const string& prompt,
                                      const string& hint,
                                      function<bool(int, bool)> validator,
                                      bool& ok,
                                      int maxTries) {
    for (int attempt = 0; attempt < maxTries; ++attempt) {
        bool parsed = false;
        int v = readInt(prompt, parsed);
        if (validator(v, parsed)) {
            ok = true;
            return v;
        }
        int left = maxTries - attempt - 1;
        if (left > 0)
            cout << "  Try again (" << left << " attempt" << (left == 1 ? "" : "s")
                 << " left).  " << hint << "\n";
    }
    ok = false;
    return 0;
}

double WarehouseSystem::readValidatedDouble(const string& prompt,
                                            const string& hint,
                                            function<bool(double, bool)> validator,
                                            bool& ok,
                                            int maxTries) {
    for (int attempt = 0; attempt < maxTries; ++attempt) {
        bool parsed = false;
        double v = readDouble(prompt, parsed);
        if (validator(v, parsed)) {
            ok = true;
            return v;
        }
        int left = maxTries - attempt - 1;
        if (left > 0)
            cout << "  Try again (" << left << " attempt" << (left == 1 ? "" : "s")
                 << " left).  " << hint << "\n";
    }
    ok = false;
    return 0.0;
}

// ── UI helpers ────────────────────────────────────────────────────────────────

void WarehouseSystem::waitKey() {
    cout << "  [Press Enter to continue]";
    cout.flush();
    string tmp;
    getline(cin, tmp);
    cout << "\n";
}

void WarehouseSystem::sectionTitle(const string& title) {
    cout << "\n  " << title << "\n  " << string(title.size() + 2, '-') << "\n\n";
}

void WarehouseSystem::printMenu(const string& title, const string items[], int n) {
    const int boxWidth  = 44;
    const string line   = "  +" + string(boxWidth - 2, '-') + "+\n";
    const int textWidth = boxWidth - 4;
    cout << "\n" << line;
    cout << "  | " << left << setw(textWidth) << title << " |\n";
    cout << line;
    for (int i = 0; i < n; ++i)
        cout << "  | " << left << setw(textWidth) << items[i] << " |\n";
    cout << line << "\n";
}

void WarehouseSystem::run() {
    while (true) {
        try {
            runLoginAndMenuLoop();
        } catch (const runtime_error& e) {
            cerr << "\n  [!] " << e.what() << "\n";
            waitKey();
            currentUser_ = nullptr;
        } catch (const exception& e) {
            cerr << "\n  [!] Error: " << e.what() << "\n";
            waitKey();
            currentUser_ = nullptr;
        }
    }
}

void WarehouseSystem::runLoginAndMenuLoop() {
    // Login screen
    cout << "\n";
    cout << "  +" << string(46, '=') << "+\n";
    cout << "  |" << string(46, ' ') << "|\n";
    cout << "  |" << "     WAREHOUSE INVENTORY SYSTEM" << string(14, ' ') << "|\n";
    cout << "  |" << string(46, ' ') << "|\n";
    cout << "  |" << "     Sign in to continue" << string(21, ' ') << "|\n";
    cout << "  |" << string(46, ' ') << "|\n";
    cout << "  +" << string(46, '=') << "+\n\n";

    string user = readLine("Username");
    string pass = readLine("Password");
    cout << "\n";

    if (user.empty() || pass.empty()) {
        cerr << "  [!] Username and password cannot be empty.\n";
        waitKey();
        return;
    }
    currentUser_ = authManager_->login(user, pass);
    if (!currentUser_) {
        cerr << "  [!] Invalid username or password. Please try again.\n";
        waitKey();
        return;
    }

    // Welcome message
    string welcomeText = currentUser_->getUsername() + " (" + currentUser_->getRole() + ")";
    if (welcomeText.size() > 33) welcomeText = welcomeText.substr(0, 30) + "...";
    cout << "  +" << string(46, '-') << "+\n";
    cout << "  |  Welcome, " << left << setw(33) << welcomeText << "|\n";
    cout << "  +" << string(46, '-') << "+\n\n";

    if (currentUser_->getRole() == "Manager")
        while (currentUser_) showManagerMenu();
    else
        while (currentUser_) showEmployeeMenu();

    saveData();
    currentUser_ = nullptr;
    cout << "\n  +" << string(46, '-') << "+\n";
    cout << "  |  You have been logged out. Goodbye!" << string(12, ' ') << "|\n";
    cout << "  +" << string(46, '-') << "+\n\n";
}

list<Product> WarehouseSystem::findProductsByNameOrId(const string& query) {
    list<Product> result;
    const string q = toLower(query);
    for_each(products_.begin(), products_.end(),
             [&result, &q](const map<string, Product>::value_type& p) {
        if (toLower(p.second.getId()).find(q)   != string::npos ||
            toLower(p.second.getName()).find(q) != string::npos)
            result.push_back(p.second);
    });
    return result;
}

bool WarehouseSystem::canFulfillOrder(const Order& order) const {
    const list<OrderItem>& items = order.getItems();
    return all_of(items.begin(), items.end(), [this](const OrderItem& item) {
        auto it = products_.find(item.getProductId());
        return it != products_.end() && it->second.getQuantity() >= item.getQuantity();
    });
}

void WarehouseSystem::deductStock(const Order& order) {
    for_each(order.getItems().begin(), order.getItems().end(),
             [this](const OrderItem& item) {
        auto it = products_.find(item.getProductId());
        if (it != products_.end())
            it->second.setQuantity(it->second.getQuantity() - item.getQuantity());
    });
}