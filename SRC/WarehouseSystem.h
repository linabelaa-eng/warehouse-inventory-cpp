#ifndef WAREHOUSESYSTEM_H
#define WAREHOUSESYSTEM_H

#include <string>
#include <map>
#include <list>
#include <utility>
#include <functional>
using namespace std;

class User;
class Product;
class EmployeeRecord;
class Order;
class AuthManager;
class ReportGenerator;

class WarehouseSystem {
    private:
    map<string, User*>          users_;
    map<string, Product>        products_;
    map<string, EmployeeRecord> employees_;
    map<string, Order>          orders_;
    AuthManager*                authManager_;
    ReportGenerator*            reportGenerator_;
    User*                       currentUser_;

    // Manager employee menus and feature screens
    void showManagerMenu();
    void showEmployeeMenu();
    void productManagement();
    void deleteProduct();
    void employeeManagement();
    void deleteEmployee();
    void orderManagement();
    void deleteOrder();
    void orderCreate();
    void orderEdit(const string& oid);
    void assignOrder();
    void viewAssignedOrders();
    void completeOrder();
    void searchProducts();
    void reportMenu();
    void generateMyReport();

    // Search and order stock rules
    list<Product> findProductsByNameOrId(const string& query);
    bool          canFulfillOrder(const Order& order) const;
    void          deductStock(const Order& order);

    // Console input
    string readLine(const string& prompt);
    int    readInt(const string& prompt, bool& inputValid);
    double readDouble(const string& prompt, bool& inputValid);
    void   waitKey();
    void   sectionTitle(const string& t);
    void   printMenu(const string& title, const string items[], int n);
    void   runLoginAndMenuLoop();

    // retries up to maxTries times
    string readValidatedLine(const string& prompt,
                             const string& hint,
                             function<bool(const string&)> validator,
                             int maxTries = 3);

    int    readValidatedInt(const string& prompt,
                            const string& hint,
                            function<bool(int, bool)> validator,
                            bool& ok,
                            int maxTries = 3);

    double readValidatedDouble(const string& prompt,
                               const string& hint,
                               function<bool(double, bool)> validator,
                               bool& ok,
                               int maxTries = 3);
public:
    WarehouseSystem();
    ~WarehouseSystem();
    void run();
    void loadData();
    void saveData();
    bool validateId(const string& id, const string& label);
    bool validateName(const string& name, const string& label);
    bool validateQuantity(int qty, bool inputValid);
    bool validatePrice(double price, bool inputValid);
    bool validateAisle(const string& aisle);
    bool validateShelf(const string& shelf);
    bool validateUsername(const string& username);
    bool validatePassword(const string& password);
    bool validateFilePath(const string& path);
};

#endif