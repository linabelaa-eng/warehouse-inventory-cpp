// Minimal test runner for Warehouse (framework-free).
#include "../include/AuthManager.h"
#include "../include/Employee.h"
#include "../include/EmployeeRecord.h"
#include "../include/FileHandler.h"
#include "../include/Manager.h"
#include "../include/Order.h"
#include "../include/OrderItem.h"
#include "../include/Product.h"
#include "../include/ReportGenerator.h"
#include "../include/User.h"

#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

static int totalTests = 0;
static int failedTests = 0;
static int expectedErrorChecks = 0;

#define CHECK(expr) do { \
    ++totalTests; \
    if (!(expr)) { \
        ++failedTests; \
        cerr << "[FAIL] " << #expr << " @ " << __FILE__ << ":" << __LINE__ << "\n"; \
    } else { \
        cout << "[PASS] " << #expr << "\n"; \
    } \
} while(0)

static string testDir() {
    const string dir = "TESTS/test_output";
    fs::create_directories(dir);
    return dir + "/";
}

static int countDataRows(const string& csvPath) {
    ifstream f(csvPath);
    if (!f.is_open()) return -1;
    string line;
    getline(f, line); // header
    int rows = 0;
    while (getline(f, line)) {
        if (!line.empty()) ++rows;
    }
    return rows;
}

struct StderrGuard {
    std::streambuf* oldBuf;
    std::ostringstream sink;
    StderrGuard() : oldBuf(std::cerr.rdbuf(sink.rdbuf())) {}
    ~StderrGuard() { std::cerr.rdbuf(oldBuf); }
};

static std::string singleLine(std::string s) {
    for (char& c : s) {
        if (c == '\n' || c == '\r' || c == '\t') c = ' ';
    }
    while (!s.empty() && s.back() == ' ') s.pop_back();
    return s;
}

static void CHECK_ERROR_MESSAGE(const std::function<bool()>& action,
                                const std::string& expectedSnippet,
                                const std::string& label,
                                const std::string& exprText) {
    ++totalTests;
    ++expectedErrorChecks;
    StderrGuard sg;
    const bool ok = action();
    const std::string captured = sg.sink.str();
    const bool hasSnippet = captured.find(expectedSnippet) != std::string::npos;

    if (!ok && hasSnippet) {
        cout << "[PASS-EXPECTED-ERROR][PASS] " << exprText << " " << label << "\n"
             << "    expected snippet: \"" << expectedSnippet << "\"\n"
             << "    actual message  : \"" << singleLine(captured) << "\"\n";
        return;
    }

    ++failedTests;
    cerr << "[FAIL] " << label << " @ " << __FILE__ << ":" << __LINE__ << "\n"
         << "       expected snippet: \"" << expectedSnippet << "\"\n"
         << "       actual captured : \"" << singleLine(captured) << "\"\n"
         << "       return value    : " << (ok ? "true" : "false") << "\n";
}

// Access private validator methods for test coverage only.
#define private public
#include "../include/WarehouseSystem.h"
#undef private

static void testAuth() {
    map<string, User*> users;
    AuthManager auth(&users);
    users["admin"] = new Manager("admin", auth.hashPassword("admin"));
    CHECK(auth.login("admin", "admin") != nullptr);
    CHECK(auth.login("admin", "wrong") == nullptr);
    for (auto& p : users) delete p.second;
}

static void testProductAndOrder() {
    Product p("P001", "Widget", 11, "A1", "S1", 9.99);
    CHECK(p.getStockStatus() == "InStock");
    p.setQuantity(0);
    CHECK(p.getStockStatus() == "OutOfStock");

    Order o("ORD001", "Pending", "");
    o.addItem(OrderItem("P001", 2));
    CHECK(o.getItems().size() == 1);
    o.setStatus("InProgress");
    CHECK(o.getStatus() == "InProgress");
}

static void testFileHandlerRoundTrip() {
    const string dir = testDir();
    FileHandler fh(dir);

    map<string, Product> products;
    products["P001"] = Product("P001", "Widget", 5, "A1", "S1", 10.0);
    CHECK(fh.saveProducts(products));

    map<string, Product> loaded;
    CHECK(fh.loadProducts(loaded));
    CHECK(loaded.count("P001") == 1);
    CHECK(loaded["P001"].getQuantity() == 5);
}

static void testReports() {
    const string dir = testDir();
    map<string, Product> products;
    products["P001"] = Product("P001", "Widget", 5, "A1", "S1", 10.0);
    map<string, Order> orders;
    orders["ORD001"] = Order("ORD001", "Completed", "E001");
    orders["ORD002"] = Order("ORD002", "Pending", "");
    ReportGenerator rg(&products, &orders);

    const string inv = dir + "inventory.csv";
    const string done = dir + "completed.csv";
    CHECK(rg.generateInventoryReport(inv));
    CHECK(rg.generateCompletedOrdersReport(done));
    CHECK(fs::exists(inv));
    CHECK(fs::exists(done));
}

static void testReportFilteringDetailed() {
    const string dir = testDir();
    map<string, Product> products;
    products["P001"] = Product("P001", "Widget", 20, "A1", "S1", 10.0);

    map<string, Order> orders;
    orders["ORD001"] = Order("ORD001", "Completed", "E001");
    orders["ORD002"] = Order("ORD002", "Completed", "E002");
    orders["ORD003"] = Order("ORD003", "Pending", "");
    orders["ORD004"] = Order("ORD004", "InProgress", "E001");

    ReportGenerator rg(&products, &orders);
    const string pending = dir + "pending_detailed.csv";
    const string employee = dir + "employee_E001.csv";

    CHECK(rg.generatePendingOrdersReport(pending));
    CHECK(rg.generateEmployeeReport(employee, "E001"));
    CHECK(countDataRows(pending) == 2);   // Pending + InProgress
    CHECK(countDataRows(employee) == 2);  // ORD001 + ORD004
}

static void testFileHandlerOrdersRoundTrip() {
    const string dir = testDir();
    FileHandler fh(dir);

    map<string, Order> original;
    Order o1("ORD100", "Pending", "");
    o1.addItem(OrderItem("P001", 2));
    o1.addItem(OrderItem("P002", 1));
    Order o2("ORD101", "Completed", "E001");
    original["ORD100"] = o1;
    original["ORD101"] = o2;

    CHECK(fh.saveOrders(original));

    map<string, Order> loaded;
    CHECK(fh.loadOrders(loaded));
    CHECK(loaded.count("ORD100") == 1);
    CHECK(loaded.count("ORD101") == 1);
    CHECK(loaded["ORD100"].getStatus() == "Pending");
    CHECK(loaded["ORD101"].getStatus() == "Completed");
    CHECK(loaded["ORD101"].getAssignedEmployeeId() == "E001");
    CHECK(loaded["ORD100"].getItems().size() == 2);
}

static void testOrderCompletionStockDeduction() {
    map<string, Product> products;
    products["P001"] = Product("P001", "Widget", 10, "A1", "S1", 5.0);
    products["P002"] = Product("P002", "Gadget", 4, "B1", "S2", 12.0);

    Order order("ORD200", "InProgress", "E001");
    order.addItem(OrderItem("P001", 3));
    order.addItem(OrderItem("P002", 4));

    auto canFulfill = [&](const Order& o) {
        for (const auto& item : o.getItems()) {
            auto it = products.find(item.getProductId());
            if (it == products.end()) return false;
            if (it->second.getQuantity() < item.getQuantity()) return false;
        }
        return true;
    };

    CHECK(canFulfill(order));

    for (const auto& item : order.getItems()) {
        auto it = products.find(item.getProductId());
        it->second.setQuantity(it->second.getQuantity() - item.getQuantity());
    }
    order.setStatus("Completed");

    CHECK(order.getStatus() == "Completed");
    CHECK(products["P001"].getQuantity() == 7);
    CHECK(products["P002"].getQuantity() == 0);
}

static void testInputValidatorsExtensive() {
    StderrGuard noisyOutputGuard; // suppress validator stderr noise in console
    WarehouseSystem ws;

    // validateId - Product
    CHECK(ws.validateId("P001", "Product ID"));
    CHECK(ws.validateId("P999", "Product ID"));
    CHECK_ERROR_MESSAGE([&](){ return ws.validateId("", "Product ID"); }, "cannot be empty",
                        "validateId empty Product ID shows error", "ws.validateId(\"\", \"Product ID\")");
    CHECK(!ws.validateId("P1", "Product ID"));
    CHECK(!ws.validateId("P0001", "Product ID"));
    CHECK(!ws.validateId("p001", "Product ID"));
    CHECK_ERROR_MESSAGE([&](){ return ws.validateId("X001", "Product ID"); }, "Invalid Product ID",
                        "validateId invalid Product format shows error", "ws.validateId(\"X001\", \"Product ID\")");

    // validateId - Employee
    CHECK(ws.validateId("E001", "Employee ID"));
    CHECK(ws.validateId("E050", "Employee ID"));
    CHECK(!ws.validateId("E01", "Employee ID"));
    CHECK(!ws.validateId("EMP001", "Employee ID"));

    // validateId - Order
    CHECK(ws.validateId("ORD001", "Order ID"));
    CHECK(ws.validateId("ORD999", "Order ID"));
    CHECK(!ws.validateId("ORD01", "Order ID"));
    CHECK(!ws.validateId("ord001", "Order ID"));

    // validateName
    CHECK(ws.validateName("Widget A", "Product name"));
    CHECK(ws.validateName("A", "Product name"));
    CHECK_ERROR_MESSAGE([&](){ return ws.validateName("", "Product name"); }, "cannot be empty",
                        "validateName empty shows error", "ws.validateName(\"\", \"Product name\")");
    CHECK_ERROR_MESSAGE([&](){ return ws.validateName("Has,Comma", "Product name"); }, "cannot contain commas",
                        "validateName comma shows error", "ws.validateName(\"Has,Comma\", \"Product name\")");
    CHECK(!ws.validateName("Has\nNewline", "Product name"));
    CHECK(!ws.validateName(string(61, 'X'), "Product name"));
    CHECK(ws.validateName(string(60, 'X'), "Product name"));

    // validateQuantity
    CHECK(ws.validateQuantity(0, true));
    CHECK(ws.validateQuantity(999999, true));
    CHECK_ERROR_MESSAGE([&](){ return ws.validateQuantity(-1, true); }, "cannot be negative",
                        "validateQuantity negative shows error", "ws.validateQuantity(-1, true)");
    CHECK(!ws.validateQuantity(1000000, true));
    CHECK_ERROR_MESSAGE([&](){ return ws.validateQuantity(5, false); }, "valid whole number",
                        "validateQuantity invalid parse shows error", "ws.validateQuantity(5, false)");

    // validatePrice
    CHECK(ws.validatePrice(0.0, true));
    CHECK(ws.validatePrice(9.99, true));
    CHECK(ws.validatePrice(999999.99, true));
    CHECK_ERROR_MESSAGE([&](){ return ws.validatePrice(-0.01, true); }, "cannot be negative",
                        "validatePrice negative shows error", "ws.validatePrice(-0.01, true)");
    CHECK(!ws.validatePrice(1000000.0, true));
    CHECK(!ws.validatePrice(5.0, false));

    // validateAisle
    CHECK(ws.validateAisle("A1"));
    CHECK(ws.validateAisle("B2-3"));
    CHECK_ERROR_MESSAGE([&](){ return ws.validateAisle(""); }, "Aisle cannot be empty",
                        "validateAisle empty shows error", "ws.validateAisle(\"\")");
    CHECK(!ws.validateAisle("A 1"));
    CHECK(!ws.validateAisle("A1,B"));
    CHECK(!ws.validateAisle(string(11, 'X')));

    // validateShelf
    CHECK(ws.validateShelf("S1"));
    CHECK(ws.validateShelf("S12-A"));
    CHECK_ERROR_MESSAGE([&](){ return ws.validateShelf(""); }, "Shelf cannot be empty",
                        "validateShelf empty shows error", "ws.validateShelf(\"\")");
    CHECK(!ws.validateShelf("S 1"));
    CHECK(!ws.validateShelf(string(11, 'S')));

    // validateUsername
    CHECK(ws.validateUsername("alice"));
    CHECK(ws.validateUsername("bob_42"));
    CHECK_ERROR_MESSAGE([&](){ return ws.validateUsername(""); }, "Username cannot be empty",
                        "validateUsername empty shows error", "ws.validateUsername(\"\")");
    CHECK(!ws.validateUsername("ab"));
    CHECK(!ws.validateUsername("has space"));
    CHECK(!ws.validateUsername("has-hyphen"));
    CHECK(!ws.validateUsername(string(31, 'a')));
    CHECK(ws.validateUsername(string(30, 'a')));

    // validatePassword
    CHECK(ws.validatePassword("pass"));
    CHECK(ws.validatePassword("secr3t!@#"));
    CHECK_ERROR_MESSAGE([&](){ return ws.validatePassword(""); }, "Password cannot be empty",
                        "validatePassword empty shows error", "ws.validatePassword(\"\")");
    CHECK(!ws.validatePassword("abc"));
    CHECK(!ws.validatePassword("has,comma"));
    CHECK(!ws.validatePassword(string(51, 'p')));
    CHECK(ws.validatePassword(string(50, 'p')));

    // validateFilePath
    CHECK(ws.validateFilePath("reports/inventory.csv"));
    CHECK(ws.validateFilePath("output.txt"));
    CHECK_ERROR_MESSAGE([&](){ return ws.validateFilePath(""); }, "File path cannot be empty",
                        "validateFilePath empty shows error", "ws.validateFilePath(\"\")");
    CHECK(!ws.validateFilePath("has\"quote.csv"));
    CHECK(!ws.validateFilePath("has\nnewline.csv"));
    CHECK(!ws.validateFilePath(string(261, 'x')));

    // --- Additional invalid input checks ---
    CHECK_ERROR_MESSAGE([&](){ return ws.validateId(" P001", "Product ID"); }, "Invalid Product ID",
                        "validateId leading-space Product ID rejected", "ws.validateId(\" P001\", \"Product ID\")");
    CHECK_ERROR_MESSAGE([&](){ return ws.validateId("P 01", "Product ID"); }, "Invalid Product ID",
                        "validateId embedded-space Product ID rejected", "ws.validateId(\"P 01\", \"Product ID\")");
    CHECK_ERROR_MESSAGE([&](){ return ws.validateId("ORDA01", "Order ID"); }, "Invalid Order ID",
                        "validateId malformed Order ID rejected", "ws.validateId(\"ORDA01\", \"Order ID\")");

    CHECK_ERROR_MESSAGE([&](){ return ws.validateName("Has\"Quote", "Product name"); }, "cannot contain commas",
                        "validateName quote rejected", "ws.validateName(\"Has\\\"Quote\", \"Product name\")");
    CHECK_ERROR_MESSAGE([&](){ return ws.validateName("Has\\Backslash", "Product name"); }, "cannot contain commas",
                        "validateName backslash rejected", "ws.validateName(\"Has\\\\Backslash\", \"Product name\")");

    CHECK_ERROR_MESSAGE([&](){ return ws.validateAisle("A_1"); }, "letters, digits, and hyphens",
                        "validateAisle underscore rejected", "ws.validateAisle(\"A_1\")");
    CHECK_ERROR_MESSAGE([&](){ return ws.validateShelf("S#1"); }, "letters, digits, and hyphens",
                        "validateShelf special-char rejected", "ws.validateShelf(\"S#1\")");

    CHECK_ERROR_MESSAGE([&](){ return ws.validateUsername("bad,name"); }, "letters, digits, and underscores",
                        "validateUsername comma rejected", "ws.validateUsername(\"bad,name\")");
    CHECK_ERROR_MESSAGE([&](){ return ws.validatePassword("bad\"pass"); }, "cannot contain commas",
                        "validatePassword quote rejected", "ws.validatePassword(\"bad\\\"pass\")");

    CHECK_ERROR_MESSAGE([&](){ return ws.validateFilePath("bad'path.csv"); }, "contains invalid characters",
                        "validateFilePath apostrophe rejected", "ws.validateFilePath(\"bad'path.csv\")");
}

int main() {
    cout << "Running WarehouseTests...\n";
    testAuth();
    testProductAndOrder();
    testFileHandlerRoundTrip();
    testReports();
    testReportFilteringDetailed();
    testFileHandlerOrdersRoundTrip();
    testOrderCompletionStockDeduction();
    testInputValidatorsExtensive();
    cout << "\nTotal: " << totalTests
         << ", Failed: " << failedTests
         << ", Expected-error checks: " << expectedErrorChecks << "\n";
    return failedTests == 0 ? 0 : 1;
}