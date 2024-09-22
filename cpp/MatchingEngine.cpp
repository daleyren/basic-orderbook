#include "includes/MarketOrder.h"
#include "includes/Order.h"
#include "includes/Orderbook.h"
#include "includes/MatchingEngine.h"
#include <iostream>

void MatchingEngine::matchOrders(OrderBook& book) {
    while (!book.buyOrders.empty() && !book.sellOrders.empty()) {
        auto& bestBuy = book.buyOrders.begin(); // Highest bid
        auto& bestSell = book.sellOrders.begin(); // Lowest ask

        if (bestBuy->first >= bestSell->first) { // Match condition
            Order& buyOrder = bestBuy->second.front();
            Order& sellOrder = bestSell->second.front();

            int fillQuantity = std::min(buyOrder.remainingQty, sellOrder.remainingQty);

            std::cout << "Matched: Buy Order " << buyOrder.orderId << " and Sell Order " << sellOrder.orderId 
                      << " for " << fillQuantity << " units at price " << bestSell->first << std::endl;

            buyOrder.remainingQty -= fillQuantity;
            sellOrder.remainingQty -= fillQuantity;

            if (buyOrder.remainingQty == 0) {
                bestBuy->second.pop_front();
                if (bestBuy->second.empty()) {
                    book.buyOrders.erase(bestBuy);
                }
            }

            if (sellOrder.remainingQty == 0) {
                bestSell->second.pop_front();
                if (bestSell->second.empty()) {
                    book.sellOrders.erase(bestSell);
                }
            }
        } else {
            break;
        }
    }
}
