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
    public:
    Product();
    Product(const string& id, const string& name, int quantity,const string& aisle, const string& shelf, double price);
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
    string getStockStatus() const;

};
#endif