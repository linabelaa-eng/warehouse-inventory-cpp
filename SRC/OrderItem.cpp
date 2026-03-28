#include "OrderItem.h"
using namespace std;

OrderItem::OrderItem():quantity_(0){}
OrderItem::OrderItem(const string& productId,int quantity):
productId_(productId),quantity_(quantity){}

string OrderItem::getProductId()const{return productId_;}
int OrderItem::getQuantity()const{return quantity_;}
void OrderItem::setQuantity(int quantity){quantity_ = quantity;}
