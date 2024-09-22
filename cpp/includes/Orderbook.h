#include <map>
#include <list>
#include "Order.h"

class OrderBook {
public:
    void addOrder(const Order& order);
    bool cancelOrder(int orderId, OrderType type);
    bool queryOrderStatus(int orderId, OrderType type) const;
    void displayOrders() const;

    std::map<double, std::list<Order>, std::greater<double>> buyOrders;
    std::map<double, std::list<Order>, std::less<double>> sellOrders;
};
