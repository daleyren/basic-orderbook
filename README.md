# basic-orderbook

* **Order Representation** : Implement `Order` struct (user ID, order ID, price, quantity, etc.).
* **Order Book** : Use `std::map` for storing buy/sell orders.
* **Matching Engine** : Focus on basic matching logic (highest bid vs. lowest ask) with partial fills.
* **Order Management** : Implement order addition, cancellation, and status querying.
* **Simple Market Orders** : Execute immediately at best price.

/orderbook
│
├── Order.h
├── OrderBook.h
├── MatchingEngine.h
├── Order.cpp
├── OrderBook.cpp
├── MatchingEngine.cpp
└── main.cpp
