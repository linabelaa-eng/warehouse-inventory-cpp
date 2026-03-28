#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <list>
#include "OrderItem.h"
class Order
{
private:
    string orderId_;
    string status_;
    string assignedEmployeeId_;
    list<OrderItem> items_;
    bool isDeleted_;
    public:
    Order();
    Order(const string& orderId, const string& status,
        const string& assignedEmployeeId= "");
    string getOrderId() const;
    string getStatus() const;
    string getAssignedEmployeeId() const;
    list<OrderItem>& getItems();
   const list<OrderItem>& getItems()const;
    void setStatus(const string& status);
    void setAssignedEmployeeId(const string& assignedEmployeeId);
    void addItem(const OrderItem& orderItem);
    void clearItems();
    bool isDeleted() const;
    void setDeleted(bool deleted);


};
#endif
