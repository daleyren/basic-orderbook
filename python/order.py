import uuid
import datetime

class Order:
    def __init__(self, user_id, order_type, order_side, price, quantity, timestamp):
        '''
        order_id: uuid
        order_type: {'limit', 'market'}
        order_side: {'buy', 'sell'}
        price: float
        quantity: int
        timestamp: datetime
        user_id: uuid
        active: boolean
        '''
        self.__user_id = user_id
        self.__order_type = order_type
        self.__order_side = order_side
        self.__price = price
        self.quantity = quantity
        self.__timestamp = timestamp

        self.__order_id = uuid.uuid4()
        self.active = True

    def get_id(self):
        return self.__order_id

    def set_inactive(self):
        self.active = False

    def is_active(self):
        return self.active



