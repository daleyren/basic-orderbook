#include <string>

enum OrderType { BUY, SELL };

struct Order {
    int orderId;        // Unique order ID
    std::string userId; // User placing the order
    OrderType type;     // BUY or SELL
    double price;       // Order price
    int quantity;       // Order quantity
    int remainingQty;   // Remaining quantity for partial fills
    long long timestamp; // Timestamp for priority

    Order(int id, const std::string& user, OrderType t, double p, int qty, long long time)
        : orderId(id), userId(user), type(t), price(p), quantity(qty), remainingQty(qty), timestamp(time) {}
};