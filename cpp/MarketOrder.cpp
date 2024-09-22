#include "includes/MarketOrder.h"
#include "includes/Order.h"
#include "includes/Orderbook.h"
#include "includes/MatchingEngine.h"
#include <iostream>

void MarketOrder::executeMarketOrder(OrderBook& book, OrderType type, int quantity) {
    if (type == BUY) {
        while (quantity > 0 && !book.sellOrders.empty()) {
            auto& bestSell = book.sellOrders.begin();
            Order& sellOrder = bestSell->second.front();

            int fillQuantity = std::min(quantity, sellOrder.remainingQty);
            quantity -= fillQuantity;
            sellOrder.remainingQty -= fillQuantity;

            std::cout << "Market Buy: Bought " << fillQuantity << " units at " << bestSell->first << std::endl;

            if (sellOrder.remainingQty == 0) {
                bestSell->second.pop_front();
                if (bestSell->second.empty()) {
                    book.sellOrders.erase(bestSell);
                }
            }
        }
        if (quantity > 0) {
            std::cout << "Market Buy Order not fully filled. Remaining quantity: " << quantity << std::endl;
        }
    } else if (type == SELL) {
        while (quantity > 0 && !book.buyOrders.empty()) {
            auto& bestBuy = book.buyOrders.begin();
            Order& buyOrder = bestBuy->second.front();

            int fillQuantity = std::min(quantity, buyOrder.remainingQty);
            quantity -= fillQuantity;
            buyOrder.remainingQty -= fillQuantity;

            std::cout << "Market Sell: Sold " << fillQuantity << " units at " << bestBuy->first << std::endl;

            if (buyOrder.remainingQty == 0) {
                bestBuy->second.pop_front();
                if (bestBuy->second.empty()) {
                    book.buyOrders.erase(bestBuy);
                }
            }
        }
        if (quantity > 0) {
            std::cout << "Market Sell Order not fully filled. Remaining quantity: " << quantity << std::endl;
        }
    }
}
