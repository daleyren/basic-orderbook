from order import Order
import datetime
import heapq
from collections import deque

class Orderbook:
    def __init__(self):
        self.asks = [] # minheap: prices
        self.ask_levels = {} # price: [queue of orders]

        self.bids = [] # maxheap: prices
        self.bid_levels = {} # price: [queue of orders]

        self.orders = {} # order_id : Order 
        self.filled_orders = []

    def match(self):
        while self.bids and self.asks:
            best_bid_price = -self.bids[0]  # Max heap via negative prices
            best_ask_price = self.asks[0]    # Min heap for asks

            if best_bid_price < best_ask_price:
                # No match possible
                break

            best_bid_orders = self.bid_levels[best_bid_price]
            best_ask_orders = self.ask_levels[best_ask_price]

            while best_bid_orders and best_ask_orders:
                # Fetch the next active bid order
                while best_bid_orders:
                    bid_order = best_bid_orders[0]
                    if bid_order.is_active():
                        break
                    else:
                        best_bid_orders.popleft()
                else:
                    # No active bid orders at this price level
                    heapq.heappop(self.bids)
                    del self.bid_levels[best_bid_price]
                    break  # Move to the next price level

                # Fetch the next active ask order
                while best_ask_orders:
                    ask_order = best_ask_orders[0]
                    if ask_order.is_active():
                        break
                    else:
                        best_ask_orders.popleft()
                else:
                    # No active ask orders at this price level
                    heapq.heappop(self.asks)
                    del self.ask_levels[best_ask_price]
                    break  # Move to the next price level

                # Determine the trade quantity
                trade_qty = min(bid_order.quantity, ask_order.quantity)

                # Update order quantities
                bid_order.quantity -= trade_qty
                ask_order.quantity -= trade_qty

                # Optionally record the trade
                trade = {
                    'bid_order_id': bid_order.get_id(),
                    'ask_order_id': ask_order.get_id(),
                    'price': best_ask_price,
                    'quantity': trade_qty,
                    'timestamp': datetime.datetime.now()
                }
                self.filled_orders.append(trade)

                # Check if bid order is fully filled
                if bid_order.quantity == 0:
                    bid_order.set_inactive()
                    best_bid_orders.popleft()
                    if not best_bid_orders:
                        heapq.heappop(self.bids)
                        del self.bid_levels[best_bid_price]
                        break  # Move to the next price level

                # Check if ask order is fully filled
                if ask_order.quantity == 0:
                    ask_order.set_inactive()
                    best_ask_orders.popleft()
                    if not best_ask_orders:
                        heapq.heappop(self.asks)
                        del self.ask_levels[best_ask_price]
                        break  # Move to the next price level

            # End of while best_bid_orders and best_ask_orders
        # End of while self.bids and self.asks


    def add_order(self, user_id, order_type, order_side, quantity, price = None) -> int:
        '''
        Takes in order details -> makes Order object -> updates asks/bids -> returns order id
        '''
        if (not price and order_type == 'limit') or (price and order_type == 'market'):
            raise Exception('Inconsistent parameters: price and order_type')
        
        # Make Order object
        order = Order(
            user_id = user_id,
            order_type = order_type,
            order_side = order_side,
            price = price,
            quantity = quantity,
            timestamp = datetime.datetime.now()
        )
        order_id = order.get_id()

        self.orders[order_id] = order
        
        # Updates Asks/Bids
        if order_side == 'buy':
            if price not in self.bid_levels: # Price does not exists; new deque
                self.bid_levels[price] = deque([])
                heapq.heappush(self.bids, -price)
            self.bid_levels[price].append(order)
        else:
            if price not in self.ask_levels: # Price does not exists; new deque
                self.ask_levels[price] = deque([])
                heapq.heappush(self.asks, price)
            self.ask_levels[price].append(order)

        # Matching Engine
        self.match()

        return order_id
    
    def cancel_order(self, order_id): # Lazy Cancel
        order = self.orders[order_id]
        try:
            order.set_inactive()
            return True
        except Exception as e:
            print('Error Cancelling Order')
        return False


    def modify_order(self, order_id, order_type, order_side, quantity, user_id, price = None):
        pass
    