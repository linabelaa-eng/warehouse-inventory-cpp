#include "WarehouseSystem.h"
#include "AuthManager.h"
#include "User.h"
#include "Manager.h"
#include "Employee.h"
#include "Product.h"
#include "EmployeeRecord.h"
#include "Order.h"
#include "OrderItem.h"
#include "ReportGenerator.h"
#include <iostream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <stdexcept>
#include <iomanip>
using namespace std;

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
    if (!ok) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }
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
    if (!ok) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }
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
        "  1. Add product", "  2. View all products",
        "  3. Edit product", "  4. Delete product"
    };
    printMenu("Product Management", opts, 4);
    bool ok;
    int c = readValidatedInt("Enter choice (1-4): ", "Enter 1, 2, 3, or 4.",
                             [](int v, bool p){ return p && v >= 1 && v <= 4; }, ok);
    if (!ok) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }

    if (c == 1) {
        string id = readValidatedLine("Product ID: ",
            "Format: P followed by 3 digits (e.g. P001).",
            [this](const string& v){ return validateId(v, "Product ID"); });
        if (id.empty()) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }
        if (products_.count(id) && !products_[id].isDeleted()) {
            cerr << "  A product with this ID already exists.\n"; waitKey(); return;
        }

        string name = readValidatedLine("Name: ",
            "1-60 characters, no commas or quotes.",
            [this](const string& v){ return validateName(v, "Product name"); });
        if (name.empty()) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }

        bool qok;
        int qty = readValidatedInt("Quantity: ", "Enter a whole number >= 0.",
                                   [this](int v, bool p){ return validateQuantity(v, p); }, qok);
        if (!qok) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }

        string aisle = readValidatedLine("Aisle (e.g. A1): ",
            "Letters and digits only, up to 10 characters.",
            [this](const string& v){ return validateAisle(v); });
        if (aisle.empty()) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }

        string shelf = readValidatedLine("Shelf (e.g. S2): ",
            "Letters and digits only, up to 10 characters.",
            [this](const string& v){ return validateShelf(v); });
        if (shelf.empty()) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }

        bool pok;
        double price = readValidatedDouble("Price: ", "Enter a number >= 0 (e.g. 9.99).",
                                           [this](double v, bool p){ return validatePrice(v, p); }, pok);
        if (!pok) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }

        products_[id] = Product(id, name, qty, aisle, shelf, price);
        cout << "  Product added successfully.\n";
        saveData();
        waitKey();

    } else if (c == 2) {
        bool any = false;
        cout << "\n  " << left << setw(12) << "ID" << setw(20) << "Name"
             << setw(8) << "Qty" << setw(10) << "Location" << "Price\n  "
             << string(56, '-') << "\n";
        for (const auto& p : products_) {
            if (p.second.isDeleted()) continue;
            any = true;
            cout << "  " << left << setw(12) << p.second.getId()
                 << setw(20) << p.second.getName()
                 << setw(8)  << p.second.getQuantity()
                 << setw(10) << (p.second.getAisle() + "/" + p.second.getShelf())
                 << fixed << setprecision(2) << p.second.getPrice() << "\n";
        }
        if (!any) cout << "  No products in inventory.\n";
        waitKey();

    } else if (c == 3) {
        string id = readValidatedLine("Product ID to edit: ",
            "Format: P followed by 3 digits (e.g. P001).",
            [this](const string& v){ return validateId(v, "Product ID"); });
        if (id.empty()) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }
        if (!products_.count(id) || products_[id].isDeleted()) {
            cerr << "  Product not found.\n"; waitKey(); return;
        }
        Product& p = products_[id];

        string n = readValidatedLine("Name (Enter = keep): ",
            "1-60 characters, no commas or quotes.",
            [this](const string& v){ return v.empty() || validateName(v, "Product name"); });
        if (!n.empty()) p.setName(n);

        bool qok;
        int q = readValidatedInt("Quantity (-1 = keep): ", "Enter a whole number >= 0, or -1 to keep.",
                                 [this](int v, bool p){ return p && (v == -1 || validateQuantity(v, p)); }, qok);
        if (!qok) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }
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
        if (!pok) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }
        if (pr != -1.0) p.setPrice(pr);

        cout << "  Product updated successfully.\n";
        saveData();
        waitKey();

    } else if (c == 4) {
        deleteProduct();
    }
}

// ── Delete product ────────────────────────────────────────────────────────────

void WarehouseSystem::deleteProduct() {
    sectionTitle("Delete Product");
    string id = readValidatedLine("Product ID to delete: ",
        "Format: P followed by 3 digits (e.g. P001).",
        [this](const string& v){ return validateId(v, "Product ID"); });
    if (id.empty()) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }
    if (!products_.count(id) || products_[id].isDeleted()) {
        cerr << "  Product not found.\n"; waitKey(); return;
    }

    // Block deletion if product is referenced in any active order
    for (const auto& o : orders_) {
        if (o.second.isDeleted() || o.second.getStatus() == "Completed") continue;
        for (const auto& item : o.second.getItems()) {
            if (item.getProductId() == id) {
                cerr << "  Cannot delete: product is part of active order "
                     << o.second.getOrderId() << ".\n";
                waitKey();
                return;
            }
        }
    }

    string confirm = readLine("Are you sure you want to delete " + id + "? (y/n): ");
    if (confirm != "y" && confirm != "Y") {
        cout << "  Deletion cancelled.\n"; waitKey(); return;
    }

    products_[id].setDeleted(true);
    cout << "  Product " << id << " deleted successfully.\n";
    saveData();
    waitKey();
}

// ── Employee management ───────────────────────────────────────────────────────

void WarehouseSystem::employeeManagement() {
    sectionTitle("Employee Management");
    static const string opts[] = {
        "  1. Add employee", "  2. View all employees",
        "  3. Edit employee", "  4. Delete employee"
    };
    printMenu("Employee Management", opts, 4);
    bool ok;
    int c = readValidatedInt("Enter choice (1-4): ", "Enter 1, 2, 3, or 4.",
                             [](int v, bool p){ return p && v >= 1 && v <= 4; }, ok);
    if (!ok) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }

    if (c == 1) {
        string eid = readValidatedLine("Employee ID: ",
            "Format: E followed by 3 digits (e.g. E001).",
            [this](const string& v){ return validateId(v, "Employee ID"); });
        if (eid.empty()) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }
        if (employees_.count(eid) && !employees_[eid].isDeleted()) {
            cerr << "  An employee with this ID already exists.\n"; waitKey(); return;
        }

        string fullName = readValidatedLine("Full name: ",
            "1-60 characters, no commas or quotes.",
            [this](const string& v){ return validateName(v, "Full name"); });
        if (fullName.empty()) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }

        employees_[eid] = EmployeeRecord(eid, fullName);
        cout << "  Employee added.\n";
        saveData();

        string create = readLine("Create login? (y/n): ");
        if (create == "y" || create == "Y") {
            string uname = readValidatedLine("Username: ",
                "3-30 characters, letters/digits/underscores only.",
                [this](const string& v){ return validateUsername(v); });
            if (uname.empty()) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }
            if (users_.count(uname)) { cerr << "  Username already in use.\n"; waitKey(); return; }

            string pwd = readValidatedLine("Password: ",
                "4-50 characters, no commas or quotes.",
                [this](const string& v){ return validatePassword(v); });
            if (pwd.empty()) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }

            authManager_->registerUser(new Employee(uname, authManager_->hashPassword(pwd), eid));
            cout << "  Login account created.\n";
            saveData();
        }
        waitKey();

    } else if (c == 2) {
        bool any = false;
        cout << "\n  " << left << setw(16) << "Employee ID" << setw(24) << "Name"
             << "Role\n  " << string(52, '-') << "\n";
        for (const auto& e : employees_) {
            if (e.second.isDeleted()) continue;
            any = true;
            string role = "-";
            for (const auto& u : users_)
                if (u.second && u.second->getEmployeeId() == e.second.getEmployeeId())
                    { role = u.second->getRole(); break; }
            cout << "  " << left << setw(16) << e.second.getEmployeeId()
                 << setw(24) << e.second.getName() << role << "\n";
        }
        if (!any) cout << "  No employees registered.\n";
        waitKey();

    } else if (c == 3) {
        string eid = readValidatedLine("Employee ID to edit: ",
            "Format: E followed by 3 digits (e.g. E001).",
            [this](const string& v){ return validateId(v, "Employee ID"); });
        if (eid.empty()) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }
        if (!employees_.count(eid) || employees_[eid].isDeleted()) {
            cerr << "  Employee not found.\n"; waitKey(); return;
        }

        string n = readValidatedLine("New name (Enter = keep): ",
            "1-60 characters, no commas or quotes.",
            [this](const string& v){ return v.empty() || validateName(v, "Name"); });
        if (!n.empty()) employees_[eid].setName(n);
        cout << "  Employee updated successfully.\n";
        saveData();
        waitKey();

    } else if (c == 4) {
        deleteEmployee();
    }
}

// ── Delete employee ───────────────────────────────────────────────────────────

void WarehouseSystem::deleteEmployee() {
    sectionTitle("Delete Employee");
    string eid = readValidatedLine("Employee ID to delete: ",
        "Format: E followed by 3 digits (e.g. E001).",
        [this](const string& v){ return validateId(v, "Employee ID"); });
    if (eid.empty()) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }
    if (!employees_.count(eid) || employees_[eid].isDeleted()) {
        cerr << "  Employee not found.\n"; waitKey(); return;
    }

    // Block deletion if employee has any active InProgress orders
    for (const auto& o : orders_) {
        if (o.second.isDeleted()) continue;
        if (o.second.getAssignedEmployeeId() == eid &&
            o.second.getStatus() == "InProgress") {
            cerr << "  Cannot delete: employee has active order "
                 << o.second.getOrderId() << " in progress.\n";
            waitKey();
            return;
        }
    }

    string confirm = readLine("Are you sure you want to delete " + eid + "? (y/n): ");
    if (confirm != "y" && confirm != "Y") {
        cout << "  Deletion cancelled.\n"; waitKey(); return;
    }

    employees_[eid].setDeleted(true);
    cout << "  Employee " << eid << " deleted successfully.\n";
    saveData();
    waitKey();
}

// ── Order management ──────────────────────────────────────────────────────────

void WarehouseSystem::orderManagement() {
    sectionTitle("Order Management");
    static const string opts[] = {
        "  1. Create order", "  2. View all orders",
        "  3. Edit order",   "  4. Delete order"
    };
    printMenu("Order Management", opts, 4);
    bool ok;
    int c = readValidatedInt("Enter choice (1-4): ", "Enter 1, 2, 3, or 4.",
                             [](int v, bool p){ return p && v >= 1 && v <= 4; }, ok);
    if (!ok) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }

    if      (c == 1) orderCreate();
    else if (c == 2) {
        bool any = false;
        cout << "\n  " << left << setw(14) << "Order ID" << setw(14) << "Status"
             << "Assigned To\n  " << string(52, '-') << "\n";
        for (const auto& o : orders_) {
            if (o.second.isDeleted()) continue;
            any = true;
            cout << "  " << left << setw(14) << o.second.getOrderId()
                 << setw(14) << o.second.getStatus()
                 << (o.second.getAssignedEmployeeId().empty() ? "-" : o.second.getAssignedEmployeeId())
                 << "\n";
        }
        if (!any) cout << "  No orders.\n";
        waitKey();
    }
    else if (c == 3) {
        string oid = readValidatedLine("Order ID to edit: ",
            "Format: ORD followed by 3 digits (e.g. ORD001).",
            [this](const string& v){ return validateId(v, "Order ID"); });
        if (oid.empty()) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }
        if (!orders_.count(oid) || orders_[oid].isDeleted()) {
            cerr << "  Order not found.\n"; waitKey(); return;
        }
        orderEdit(oid);
    }
    else if (c == 4) deleteOrder();
}

// ── Delete order ──────────────────────────────────────────────────────────────

void WarehouseSystem::deleteOrder() {
    sectionTitle("Delete Order");
    string oid = readValidatedLine("Order ID to delete: ",
        "Format: ORD followed by 3 digits (e.g. ORD001).",
        [this](const string& v){ return validateId(v, "Order ID"); });
    if (oid.empty()) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }
    if (!orders_.count(oid) || orders_[oid].isDeleted()) {
        cerr << "  Order not found.\n"; waitKey(); return;
    }

    const Order& ord = orders_[oid];

    // Only Pending orders can be deleted
    if (ord.getStatus() == "Completed") {
        cerr << "  Cannot delete a completed order — history must be preserved.\n";
        waitKey(); return;
    }
    if (ord.getStatus() == "InProgress") {
        cerr << "  Cannot delete an order that is in progress.\n";
        waitKey(); return;
    }

    string confirm = readLine("Are you sure you want to delete " + oid + "? (y/n): ");
    if (confirm != "y" && confirm != "Y") {
        cout << "  Deletion cancelled.\n"; waitKey(); return;
    }

    orders_[oid].setDeleted(true);
    cout << "  Order " << oid << " deleted successfully.\n";
    saveData();
    waitKey();
}

void WarehouseSystem::orderCreate() {
    sectionTitle("Create Order");
    string oid = readValidatedLine("Order ID: ",
        "Format: ORD followed by 3 digits (e.g. ORD001).",
        [this](const string& v){ return validateId(v, "Order ID"); });
    if (oid.empty()) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }
    if (orders_.count(oid) && !orders_[oid].isDeleted()) {
        cerr << "  An order with this ID already exists.\n"; waitKey(); return;
    }

    Order ord(oid, "Pending", "");
    cout << "  Add items (leave Product ID empty when done).\n";
    while (true) {
        string pid = readLine("  Product ID (empty = done): ");
        if (pid.empty()) break;
        if (!validateId(pid, "Product ID"))                          { continue; }
        if (!products_.count(pid) || products_[pid].isDeleted())     { cerr << "  Product not found.\n"; continue; }
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
    saveData();
    waitKey();
}

void WarehouseSystem::orderEdit(const string& oid) {
    sectionTitle("Edit Order");
    if (!orders_.count(oid) || orders_[oid].isDeleted()) { cerr << "  Order not found.\n"; waitKey(); return; }
    Order& ord = orders_[oid];
    if (ord.getStatus() == "Completed") { cerr << "  Cannot edit a completed order.\n"; waitKey(); return; }

    Order backup = ord;
    ord.clearItems();
    cout << "  Re-add items (leave Product ID empty when done).\n";
    while (true) {
        string pid = readLine("  Product ID (empty = done): ");
        if (pid.empty()) break;
        if (!validateId(pid, "Product ID"))                          { continue; }
        if (!products_.count(pid) || products_[pid].isDeleted())     { cerr << "  Product not found.\n"; continue; }
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
    saveData();
    waitKey();
}

void WarehouseSystem::assignOrder() {
    sectionTitle("Assign Order");
    string oid = readValidatedLine("Order ID: ",
        "Format: ORD followed by 3 digits (e.g. ORD001).",
        [this](const string& v){ return validateId(v, "Order ID"); });
    if (oid.empty()) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }
    if (!orders_.count(oid) || orders_[oid].isDeleted()) { cerr << "  Order not found.\n"; waitKey(); return; }
    if (orders_[oid].getStatus() == "Completed") { cerr << "  Cannot reassign a completed order.\n"; waitKey(); return; }

    string eid = readValidatedLine("Employee ID: ",
        "Format: E followed by 3 digits (e.g. E001).",
        [this](const string& v){ return validateId(v, "Employee ID"); });
    if (eid.empty()) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }
    if (!employees_.count(eid) || employees_[eid].isDeleted()) { cerr << "  Employee not found.\n"; waitKey(); return; }

    orders_[oid].setAssignedEmployeeId(eid);
    orders_[oid].setStatus("InProgress");
    cout << "  Order " << oid << " assigned to " << eid << ".\n";
    saveData();
    waitKey();
}

// ── Employee actions ──────────────────────────────────────────────────────────

void WarehouseSystem::viewAssignedOrders() {
    sectionTitle("My Assigned Orders");
    const string eid = currentUser_->getEmployeeId();
    list<pair<string,string>> rows;
    for (const auto& o : orders_)
        if (!o.second.isDeleted() && o.second.getAssignedEmployeeId() == eid)
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
    if (oid.empty()) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }
    if (!orders_.count(oid) || orders_[oid].isDeleted()) { cerr << "  Order not found.\n"; waitKey(); return; }
    Order& ord = orders_[oid];
    if (ord.getAssignedEmployeeId() != currentUser_->getEmployeeId()) {
        cerr << "  This order is not assigned to you.\n"; waitKey(); return;
    }
    if (ord.getStatus() == "Completed") { cerr << "  Order is already completed.\n"; waitKey(); return; }
    if (!canFulfillOrder(ord))          { cerr << "  Insufficient stock.\n"; waitKey(); return; }
    deductStock(ord);
    ord.setStatus("Completed");
    cout << "  Order completed successfully.\n";
    saveData();
    waitKey();
}

void WarehouseSystem::searchProducts() {
    sectionTitle("Search Products");
    string query = readValidatedLine("Search by name or ID: ",
        "Enter at least 1 character.",
        [](const string& v){ return !v.empty() && v.size() <= 60; });
    if (query.empty()) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }

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
    if (!ok) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }
    if (c == 4) return;

    string path = readValidatedLine("Save to file (e.g. reports/inventory.csv): ",
        "Enter a valid file path, no quotes or newlines.",
        [this](const string& v){ return validateFilePath(v); });
    if (path.empty()) { cerr << "  Too many invalid attempts. Returning to menu.\n"; waitKey(); return; }

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