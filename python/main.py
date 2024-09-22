from orderbook import Orderbook
import uuid

def main():
  orderbook = Orderbook()
  # Add some limit buy and sell orders
  order_id1 = orderbook.add_order(user_id=uuid.uuid4(), order_type='limit', order_side='buy', price=100, quantity=7)
  order_id2 = orderbook.add_order(user_id=uuid.uuid4(), order_type='limit', order_side='sell', price=95, quantity=5)
  order_id3 = orderbook.add_order(user_id=uuid.uuid4(), order_type='limit', order_side='sell', price=100, quantity=10)
  order_id4 = orderbook.add_order(user_id=uuid.uuid4(), order_type='limit', order_side='sell', price=110, quantity=10)
  order_id5 = orderbook.add_order(user_id=uuid.uuid4(), order_type='limit', order_side='buy', price=120, quantity=20)

  fills = orderbook.filled_orders
  for order in fills:
     print(order)

  pass

if __name__=="__main__":
    main()