#include "../include/WarehouseSystem.h"
#include "../include/AuthManager.h"
#include "../include/User.h"
#include "../include/Manager.h"
#include "../include/Employee.h"
#include "../include/Product.h"
#include "../include/EmployeeRecord.h"
#include "../include/Order.h"
#include "../include/OrderItem.h"
#include "../include/ReportGenerator.h"
#include <iostream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <stdexcept>
#include <iomanip>
using namespace std;

// ── convenience macro so every abort looks the same ──────────────────────────
#define ABORT_IF_EMPTY(val) \
    if ((val).empty()) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }
#define ABORT_IF_NOT_OK(ok) \
    if (!(ok)) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }

// ── Manager menu ──────────────────────────────────────────────────────────────

void WarehouseSystem::showManagerMenu() {
    cout << "\n  --- Manager ---\n\n";
    static const string opts[] = {
        "  1. Products", "  2. Employees", "  3. Orders",
        "  4. Assign order", "  5. Reports", "  6. Logout"
    };
    printMenu("Manager Menu", opts, 6);
    bool ok;
    int c = readValidatedInt("Choice (1-6): ", "Enter a number between 1 and 6.",
                             [](int v, bool p){ return p && v >= 1 && v <= 6; }, ok);
    ABORT_IF_NOT_OK(ok);
    if      (c == 1) productManagement();
    else if (c == 2) employeeManagement();
    else if (c == 3) orderManagement();
    else if (c == 4) assignOrder();
    else if (c == 5) reportMenu();
    else if (c == 6) currentUser_ = nullptr;
}

// ── Employee menu ─────────────────────────────────────────────────────────────

void WarehouseSystem::showEmployeeMenu() {
    cout << "\n  --- Employee ---\n\n";
    static const string opts[] = {
        "  1. My orders", "  2. Complete order", "  3. Search products",
        "  4. My report",  "  5. Logout"
    };
    printMenu("Employee Menu", opts, 5);
    bool ok;
    int c = readValidatedInt("Choice (1-5): ", "Enter a number between 1 and 5.",
                             [](int v, bool p){ return p && v >= 1 && v <= 5; }, ok);
    ABORT_IF_NOT_OK(ok);
    if      (c == 1) viewAssignedOrders();
    else if (c == 2) completeOrder();
    else if (c == 3) searchProducts();
    else if (c == 4) generateMyReport();
    else if (c == 5) currentUser_ = nullptr;
}

// ── Product management ────────────────────────────────────────────────────────

void WarehouseSystem::productManagement() {
    sectionTitle("Product Management");
    static const string opts[] = {
        "  1. Add product", "  2. View all products", "  3. Edit product"
    };
    printMenu("Product Management", opts, 3);
    bool ok;
    int c = readValidatedInt("Enter choice (1-3): ", "Enter 1, 2, or 3.",
                             [](int v, bool p){ return p && v >= 1 && v <= 3; }, ok);
    ABORT_IF_NOT_OK(ok);

    if (c == 1) {
        string id = readValidatedLine("Product ID: ",
            "Format: P followed by 3 digits (e.g. P001).",
            [this](const string& v){ return validateId(v, "Product ID"); });
        ABORT_IF_EMPTY(id);
        if (products_.count(id)) { cerr << "  A product with this ID already exists.\n"; waitKey(); return; }

        string name = readValidatedLine("Name: ",
            "1-60 characters, no commas or quotes.",
            [this](const string& v){ return validateName(v, "Product name"); });
        ABORT_IF_EMPTY(name);

        bool qok;
        int qty = readValidatedInt("Quantity: ", "Enter a whole number >= 0.",
                                   [this](int v, bool p){ return validateQuantity(v, p); }, qok);
        ABORT_IF_NOT_OK(qok);

        string aisle = readValidatedLine("Aisle (e.g. A1): ",
            "Letters and digits only, up to 10 characters.",
            [this](const string& v){ return validateAisle(v); });
        ABORT_IF_EMPTY(aisle);

        string shelf = readValidatedLine("Shelf (e.g. S2): ",
            "Letters and digits only, up to 10 characters.",
            [this](const string& v){ return validateShelf(v); });
        ABORT_IF_EMPTY(shelf);

        bool pok;
        double price = readValidatedDouble("Price: ", "Enter a number >= 0 (e.g. 9.99).",
                                           [this](double v, bool p){ return validatePrice(v, p); }, pok);
        ABORT_IF_NOT_OK(pok);

        products_[id] = Product(id, name, qty, aisle, shelf, price);
        cout << "  Product added successfully.\n";
        waitKey();

    } else if (c == 2) {
        if (products_.empty()) { cout << "  No products in inventory.\n"; waitKey(); return; }
        cout << "\n  " << left << setw(12) << "ID" << setw(20) << "Name"
             << setw(8) << "Qty" << setw(10) << "Location" << "Price\n  "
             << string(56, '-') << "\n";
        for (const auto& p : products_)
            cout << "  " << left << setw(12) << p.second.getId()
                 << setw(20) << p.second.getName()
                 << setw(8)  << p.second.getQuantity()
                 << setw(10) << (p.second.getAisle() + "/" + p.second.getShelf())
                 << fixed << setprecision(2) << p.second.getPrice() << "\n";
        waitKey();

    } else if (c == 3) {
        string id = readValidatedLine("Product ID to edit: ",
            "Format: P followed by 3 digits (e.g. P001).",
            [this](const string& v){ return validateId(v, "Product ID"); });
        ABORT_IF_EMPTY(id);
        if (!products_.count(id)) { cerr << "  Product not found.\n"; waitKey(); return; }
        Product& p = products_[id];

        string n = readValidatedLine("Name (Enter = keep): ",
            "1-60 characters, no commas or quotes.",
            [this](const string& v){ return v.empty() || validateName(v, "Product name"); });
        if (!n.empty()) p.setName(n);

        bool qok;
        int q = readValidatedInt("Quantity (-1 = keep): ", "Enter a whole number >= 0, or -1 to keep.",
                                 [this](int v, bool p){ return p && (v == -1 || validateQuantity(v, p)); }, qok);
        ABORT_IF_NOT_OK(qok);
        if (q != -1) p.setQuantity(q);

        string a = readValidatedLine("Aisle (Enter = keep): ",
            "Letters and digits only, up to 10 characters.",
            [this](const string& v){ return v.empty() || validateAisle(v); });
        if (!a.empty()) p.setAisle(a);

        string s = readValidatedLine("Shelf (Enter = keep): ",
            "Letters and digits only, up to 10 characters.",
            [this](const string& v){ return v.empty() || validateShelf(v); });
        if (!s.empty()) p.setShelf(s);

        bool pok;
        double pr = readValidatedDouble("Price (-1 = keep): ", "Enter a number >= 0, or -1 to keep.",
                                        [this](double v, bool p){ return p && (v == -1.0 || validatePrice(v, p)); }, pok);
        ABORT_IF_NOT_OK(pok);
        if (pr != -1.0) p.setPrice(pr);

        cout << "  Product updated successfully.\n";
        waitKey();
    }
}

// ── Employee management ───────────────────────────────────────────────────────

void WarehouseSystem::employeeManagement() {
    sectionTitle("Employee Management");
    static const string opts[] = {
        "  1. Add employee", "  2. View all employees", "  3. Edit employee"
    };
    printMenu("Employee Management", opts, 3);
    bool ok;
    int c = readValidatedInt("Enter choice (1-3): ", "Enter 1, 2, or 3.",
                             [](int v, bool p){ return p && v >= 1 && v <= 3; }, ok);
    ABORT_IF_NOT_OK(ok);

    if (c == 1) {
        string eid = readValidatedLine("Employee ID: ",
            "Format: E followed by 3 digits (e.g. E001).",
            [this](const string& v){ return validateId(v, "Employee ID"); });
        ABORT_IF_EMPTY(eid);
        if (employees_.count(eid)) { cerr << "  An employee with this ID already exists.\n"; waitKey(); return; }

        string fullName = readValidatedLine("Full name: ",
            "1-60 characters, no commas or quotes.",
            [this](const string& v){ return validateName(v, "Full name"); });
        ABORT_IF_EMPTY(fullName);

        employees_[eid] = EmployeeRecord(eid, fullName);
        cout << "  Employee added.\n";

        string create = readLine("Create login? (y/n): ");
        if (create == "y" || create == "Y") {
            string uname = readValidatedLine("Username: ",
                "3-30 characters, letters/digits/underscores only.",
                [this](const string& v){ return validateUsername(v); });
            ABORT_IF_EMPTY(uname);
            if (users_.count(uname)) { cerr << "  Username already in use.\n"; waitKey(); return; }

            string pwd = readValidatedLine("Password: ",
                "4-50 characters, no commas or quotes.",
                [this](const string& v){ return validatePassword(v); });
            ABORT_IF_EMPTY(pwd);

            authManager_->registerUser(new Employee(uname, authManager_->hashPassword(pwd), eid));
            cout << "  Login account created.\n";
        }
        waitKey();

    } else if (c == 2) {
        if (employees_.empty()) { cout << "  No employees registered.\n"; waitKey(); return; }
        cout << "\n  " << left << setw(16) << "Employee ID" << setw(24) << "Name"
             << "Role\n  " << string(52, '-') << "\n";
        for (const auto& e : employees_) {
            string role = "-";
            for (const auto& u : users_)
                if (u.second && u.second->getEmployeeId() == e.second.getEmployeeId())
                    { role = u.second->getRole(); break; }
            cout << "  " << left << setw(16) << e.second.getEmployeeId()
                 << setw(24) << e.second.getName() << role << "\n";
        }
        waitKey();

    } else if (c == 3) {
        string eid = readValidatedLine("Employee ID to edit: ",
            "Format: E followed by 3 digits (e.g. E001).",
            [this](const string& v){ return validateId(v, "Employee ID"); });
        ABORT_IF_EMPTY(eid);
        if (!employees_.count(eid)) { cerr << "  Employee not found.\n"; waitKey(); return; }

        string n = readValidatedLine("New name (Enter = keep): ",
            "1-60 characters, no commas or quotes.",
            [this](const string& v){ return v.empty() || validateName(v, "Name"); });
        if (!n.empty()) employees_[eid].setName(n);
        cout << "  Employee updated successfully.\n";
        waitKey();
    }
}

// ── Order management ──────────────────────────────────────────────────────────

void WarehouseSystem::orderManagement() {
    sectionTitle("Order Management");
    static const string opts[] = {
        "  1. Create order", "  2. View all orders", "  3. Edit order"
    };
    printMenu("Order Management", opts, 3);
    bool ok;
    int c = readValidatedInt("Enter choice (1-3): ", "Enter 1, 2, or 3.",
                             [](int v, bool p){ return p && v >= 1 && v <= 3; }, ok);
    ABORT_IF_NOT_OK(ok);

    if      (c == 1) orderCreate();
    else if (c == 2) {
        if (orders_.empty()) { cout << "  No orders.\n"; waitKey(); return; }
        cout << "\n  " << left << setw(14) << "Order ID" << setw(14) << "Status"
             << "Assigned To\n  " << string(52, '-') << "\n";
        for (const auto& o : orders_)
            cout << "  " << left << setw(14) << o.second.getOrderId()
                 << setw(14) << o.second.getStatus()
                 << (o.second.getAssignedEmployeeId().empty() ? "-" : o.second.getAssignedEmployeeId())
                 << "\n";
        waitKey();
    }
    else if (c == 3) {
        string oid = readValidatedLine("Order ID to edit: ",
            "Format: ORD followed by 3 digits (e.g. ORD001).",
            [this](const string& v){ return validateId(v, "Order ID"); });
        ABORT_IF_EMPTY(oid);
        orderEdit(oid);
    }
}

void WarehouseSystem::orderCreate() {
    sectionTitle("Create Order");
    string oid = readValidatedLine("Order ID: ",
        "Format: ORD followed by 3 digits (e.g. ORD001).",
        [this](const string& v){ return validateId(v, "Order ID"); });
    ABORT_IF_EMPTY(oid);
    if (orders_.count(oid)) { cerr << "  An order with this ID already exists.\n"; waitKey(); return; }

    Order ord(oid, "Pending", "");
    cout << "  Add items (leave Product ID empty when done).\n";
    while (true) {
        string pid = readLine("  Product ID (empty = done): ");
        if (pid.empty()) break;
        if (!validateId(pid, "Product ID"))  { continue; }
        if (!products_.count(pid))           { cerr << "  Product not found.\n"; continue; }
        bool ok;
        int q = readValidatedInt("  Quantity: ", "Enter a whole number > 0.",
                                 [this](int v, bool p){ return validateQuantity(v, p) && v > 0; }, ok);
        if (!ok) { cerr << "  Skipping item.\n"; continue; }
        ord.addItem(OrderItem(pid, q));
    }
    if (ord.getItems().empty()) { cerr << "  Order must have at least one item.\n"; waitKey(); return; }
    if (!canFulfillOrder(ord))  { cerr << "  Insufficient stock for one or more items.\n"; waitKey(); return; }

    orders_[oid] = ord;
    cout << "  Order created successfully.\n";
    waitKey();
}

void WarehouseSystem::orderEdit(const string& oid) {
    sectionTitle("Edit Order");
    if (!orders_.count(oid))             { cerr << "  Order not found.\n"; waitKey(); return; }
    Order& ord = orders_[oid];
    if (ord.getStatus() == "Completed")  { cerr << "  Cannot edit a completed order.\n"; waitKey(); return; }

    Order backup = ord;
    ord.clearItems();
    cout << "  Re-add items (leave Product ID empty when done).\n";
    while (true) {
        string pid = readLine("  Product ID (empty = done): ");
        if (pid.empty()) break;
        if (!validateId(pid, "Product ID"))  { continue; }
        if (!products_.count(pid))           { cerr << "  Product not found.\n"; continue; }
        bool ok;
        int q = readValidatedInt("  Quantity: ", "Enter a whole number > 0.",
                                 [this](int v, bool p){ return validateQuantity(v, p) && v > 0; }, ok);
        if (!ok) { cerr << "  Skipping item.\n"; continue; }
        ord.addItem(OrderItem(pid, q));
    }
    if (ord.getItems().empty() || !canFulfillOrder(ord)) {
        orders_[oid] = backup;
        cerr << (ord.getItems().empty() ? "  No items entered." : "  Insufficient stock.")
             << " Order reverted.\n";
        waitKey();
        return;
    }
    cout << "  Order updated successfully.\n";
    waitKey();
}

void WarehouseSystem::assignOrder() {
    sectionTitle("Assign Order");
    string oid = readValidatedLine("Order ID: ",
        "Format: ORD followed by 3 digits (e.g. ORD001).",
        [this](const string& v){ return validateId(v, "Order ID"); });
    ABORT_IF_EMPTY(oid);
    if (!orders_.count(oid)) { cerr << "  Order not found.\n"; waitKey(); return; }
    if (orders_[oid].getStatus() == "Completed") { cerr << "  Cannot reassign a completed order.\n"; waitKey(); return; }

    string eid = readValidatedLine("Employee ID: ",
        "Format: E followed by 3 digits (e.g. E001).",
        [this](const string& v){ return validateId(v, "Employee ID"); });
    ABORT_IF_EMPTY(eid);
    if (!employees_.count(eid)) { cerr << "  Employee not found.\n"; waitKey(); return; }

    orders_[oid].setAssignedEmployeeId(eid);
    orders_[oid].setStatus("InProgress");
    cout << "  Order " << oid << " assigned to " << eid << ".\n";
    waitKey();
}

// ── Employee actions ──────────────────────────────────────────────────────────

void WarehouseSystem::viewAssignedOrders() {
    sectionTitle("My Assigned Orders");
    const string eid = currentUser_->getEmployeeId();
    list<pair<string,string>> rows;
    for (const auto& o : orders_)
        if (o.second.getAssignedEmployeeId() == eid)
            rows.push_back({o.second.getOrderId(), o.second.getStatus()});
    if (rows.empty()) { cout << "  You have no assigned orders.\n"; waitKey(); return; }
    cout << "\n  " << left << setw(16) << "Order ID" << "Status\n  " << string(36, '-') << "\n";
    for (const auto& r : rows)
        cout << "  " << left << setw(16) << r.first << r.second << "\n";
    waitKey();
}

void WarehouseSystem::completeOrder() {
    sectionTitle("Complete Order");
    string oid = readValidatedLine("Order ID to complete: ",
        "Format: ORD followed by 3 digits (e.g. ORD001).",
        [this](const string& v){ return validateId(v, "Order ID"); });
    ABORT_IF_EMPTY(oid);
    if (!orders_.count(oid)) { cerr << "  Order not found.\n"; waitKey(); return; }
    Order& ord = orders_[oid];
    if (ord.getAssignedEmployeeId() != currentUser_->getEmployeeId()) {
        cerr << "  This order is not assigned to you.\n"; waitKey(); return;
    }
    if (ord.getStatus() == "Completed") { cerr << "  Order is already completed.\n"; waitKey(); return; }
    if (!canFulfillOrder(ord))          { cerr << "  Insufficient stock.\n"; waitKey(); return; }
    deductStock(ord);
    ord.setStatus("Completed");
    cout << "  Order completed successfully.\n";
    waitKey();
}

void WarehouseSystem::searchProducts() {
    sectionTitle("Search Products");
    string query = readValidatedLine("Search by name or ID: ",
        "Enter at least 1 character.",
        [](const string& v){ return !v.empty() && v.size() <= 60; });
    ABORT_IF_EMPTY(query);

    list<Product> results = findProductsByNameOrId(query);
    if (results.empty()) { cout << "  No products match your search.\n"; waitKey(); return; }
    cout << "\n  " << left << setw(12) << "ID" << setw(20) << "Name"
         << setw(8) << "Qty" << setw(10) << "Location" << "Price\n  "
         << string(56, '-') << "\n";
    for (const auto& p : results)
        cout << "  " << left << setw(12) << p.getId()
             << setw(20) << p.getName()
             << setw(8)  << p.getQuantity()
             << setw(10) << (p.getAisle() + "/" + p.getShelf())
             << fixed << setprecision(2) << p.getPrice() << "\n";
    waitKey();
}

// ── Reports ───────────────────────────────────────────────────────────────────

void WarehouseSystem::reportMenu() {
    sectionTitle("Reports");
    static const string opts[] = {
        "  1. Inventory report", "  2. Completed orders report",
        "  3. Pending orders report", "  4. Back"
    };
    printMenu("Reports", opts, 4);
    bool ok;
    int c = readValidatedInt("Choice (1-4): ", "Enter a number between 1 and 4.",
                             [](int v, bool p){ return p && v >= 1 && v <= 4; }, ok);
    ABORT_IF_NOT_OK(ok);
    if (c == 4) return;

    string path = readValidatedLine("Save to file (e.g. reports/inventory.csv): ",
        "Enter a valid file path, no quotes or newlines.",
        [this](const string& v){ return validateFilePath(v); });
    ABORT_IF_EMPTY(path);

    if (!reportGenerator_) { cerr << "  Report generator not available.\n"; waitKey(); return; }
    bool done = false;
    if      (c == 1) done = reportGenerator_->generateInventoryReport(path);
    else if (c == 2) done = reportGenerator_->generateCompletedOrdersReport(path);
    else if (c == 3) done = reportGenerator_->generatePendingOrdersReport(path);

    cout << (done ? "  Report saved to " + path + "\n" : "  Failed to save report.\n");
    waitKey();
}

void WarehouseSystem::generateMyReport() {
    if (!currentUser_) return;
    string eid = currentUser_->getEmployeeId();
    if (eid.empty()) { cerr << "  No employee ID for this account.\n"; waitKey(); return; }
    if (!reportGenerator_) { cerr << "  Report generator not available.\n"; waitKey(); return; }

    string path = readValidatedLine("Save my report to (e.g. my_orders.csv): ",
        "Enter a valid file path.",
        [this](const string& v){ return v.empty() || validateFilePath(v); });
    if (path.empty()) path = "my_orders_" + eid + ".csv";

    if (reportGenerator_->generateEmployeeReport(path, eid))
        cout << "  Report saved to " << path << "\n";
    else
        cerr << "  Failed to save report.\n";
    waitKey();
}