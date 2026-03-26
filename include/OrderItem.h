#ifndef ORDERITEM_H
#define ORDERITEM_H
#include <string>
using namespace std;
class OrderItem
{
    private:
    string productId_;
    int quantity_;
    public:
    OrderItem();
    OrderItem(const string& productId,int quantity);
    string getProductId() const;
    int getQuantity() const;
    void setQuantity(int quantity);

};
#endif