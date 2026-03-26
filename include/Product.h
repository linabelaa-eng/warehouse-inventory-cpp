#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
using namespace std;
class Product
{
private:
    string id_;
    string name_;
    int quantity_;
    string aisle_;
    string shelf_;
    double price_;
    bool isDeleted_;
    public:
    Product();
    Product(const std::string& id, const std::string& name, int quantity,const std::string& aisle, const std::string& shelf, double price);
    string getId() const;
    string getName() const;
    int getQuantity() const;
    string getAisle() const;
    string getShelf() const;
    double getPrice() const;
    void setName(const string& name);
    void setQuantity(int quantity);
    void setAisle(const string& aisle);
    void setShelf(const string& shelf);
    void setPrice(double price);
    bool isDeleted() const;
    void setDeleted(bool deleted);
    string getStockStatus() const;

};
#endif