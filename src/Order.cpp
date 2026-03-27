#include "Order.h"

using namespace std;

Order::Order() : isDeleted_(false) {}

Order::Order(const string& orderId, const string& status,
             const string& assignedEmployeeId)
    : orderId_(orderId), status_(status),
      assignedEmployeeId_(assignedEmployeeId), isDeleted_(false) {}
string Order::getOrderId() const { return orderId_; }
string Order::getStatus() const { return status_; }
string Order::getAssignedEmployeeId() const { return assignedEmployeeId_; }
list<OrderItem>& Order::getItems() { return items_; }
const list<OrderItem>& Order::getItems() const { return items_; }

void Order::setStatus(const string& status) { status_ = status; }
void Order::setAssignedEmployeeId(const string& employeeId) { assignedEmployeeId_ = employeeId; }
void Order::addItem(const OrderItem& orderItem)
{
    items_.push_back(orderItem);
}
void Order::clearItems(){items_.clear();}
bool Order::isDeleted() const { return isDeleted_; }
void Order::setDeleted(bool deleted) { isDeleted_ = deleted; }