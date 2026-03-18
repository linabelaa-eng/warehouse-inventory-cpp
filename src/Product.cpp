#include "../include/Product.h"
using namespace std;
Product::Product(){}
Product::Product(const string& id, const string& name, int quantity,const string& aisle, const string& shelf, double price): id_(id), name_(name), quantity_(quantity), aisle_(aisle), shelf_(shelf), price_(price) {}

string Product::getId() const{return id_;}
string Product::getName() const{return name_;}
int Product::getQuantity() const{return quantity_;}
string Product::getAisle() const{return aisle_;}
string Product::getShelf() const{return shelf_;}
double Product::getPrice() const{return price_;}
void Product::setName(const string& name){name_ = name; }
void Product::setQuantity(int quantity){
    if (quantity < 0) {
        quantity_ = 0;
        } else {quantity_ = quantity;}
}
void Product::setAisle(const string& aisle){aisle_ = aisle;}
void Product::setShelf(const string& shelf){shelf_ = shelf;}
void Product::setPrice(double price){price_ = price;}
string Product::getStockStatus() const {
    if (quantity_ == 0)  return "OutOfStock";
    if (quantity_ <= 10) return "LowStock";
    return "InStock";
}


