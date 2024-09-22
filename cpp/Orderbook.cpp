#include "includes/MarketOrder.h"
#include "includes/Order.h"
#include "includes/Orderbook.h"
#include "includes/MatchingEngine.h"
#include <iostream>

void OrderBook::addOrder(const Order& order) {
    if (order.type == BUY) {
        buyOrders[order.price].push_back(order);
    } else {
        sellOrders[order.price].push_back(order);
    }
}

bool OrderBook::cancelOrder(int orderId, OrderType type) {
    auto& orders = (type == BUY) ? buyOrders : sellOrders;
    for (auto& [price, orderList] : orders) {
        for (auto it = orderList.begin(); it != orderList.end(); ++it) {
            if (it->orderId == orderId) {
                orderList.erase(it);
                if (orderList.empty()) {
                    orders.erase(price);
                }
                return true;
            }
        }
    }
    return false;
}

bool OrderBook::queryOrderStatus(int orderId, OrderType type) const {
    const auto& orders = (type == BUY) ? buyOrders : sellOrders;
    for (const auto& [price, orderList] : orders) {
        for (const auto& order : orderList) {
            if (order.orderId == orderId) {
                std::cout << "Order " << orderId << " found. Remaining quantity: " << order.remainingQty << std::endl;
                return true;
            }
        }
    }
    std::cout << "Order " << orderId << " not found." << std::endl;
    return false;
}

void OrderBook::displayOrders() const {
    std::cout << "Buy Orders:\n";
    for (const auto& [price, orders] : buyOrders) {
        std::cout << "Price: " << price << "\n";
        for (const auto& order : orders) {
            std::cout << "  Order ID: " << order.orderId << ", Remaining Qty: " << order.remainingQty << "\n";
        }
    }
    
    std::cout << "\nSell Orders:\n";
    for (const auto& [price, orders] : sellOrders) {
        std::cout << "Price: " << price << "\n";
        for (const auto& order : orders) {
            std::cout << "  Order ID: " << order.orderId << ", Remaining Qty: " << order.remainingQty << "\n";
        }
    }
}
