import uuid
import re

class Inventory:
    def __init__(self):
        self.items = {
            "Item 1": 10.0,
            "Item 2": 20.0,
            "Item 3": 15.0
        }

    def get_item_cost(self, item_name):
        cost = self.items.get(item_name)
        if cost is None or cost <= 0.01 or cost > 999999:
            raise ValueError("Invalid cost for item '{}' in the inventory.".format(item_name))
        return cost


class ShoppingCart:
    def __init__(self, customer_id):
        self.cart_id = str(uuid.uuid4())
        self.customer_id = self.validate_customer_id(customer_id)
        self.items = {}

    def get_cart_id(self):
        return self.cart_id

    def get_customer_id(self):
        return self.customer_id

    def get_items(self):
        return self.items.copy()

    def add_item(self, item_name, quantity):
        self.validate_item_name(item_name)
        self.validate_quantity(quantity)
        if item_name in self.items:
            self.items[item_name] += quantity
        else:
            self.items[item_name] = quantity

    def update_item(self, item_name, quantity):
        self.validate_item_name(item_name)
        self.validate_quantity(quantity)
        if item_name in self.items:
            self.items[item_name] = quantity
        else:
            raise ValueError("Item not found in the cart.")

    def remove_item(self, item_name):
        self.validate_item_name(item_name)
        if item_name in self.items:
            del self.items[item_name]
        else:
            raise ValueError("Item not found in the cart.")

    def total_cost(self, inventory):
        total_cost = 0.0
        for item, quantity in self.items.items():
            item_cost = inventory.get_item_cost(item)
            total_cost += item_cost * quantity
        return total_cost

    def validate_customer_id(self, customer_id):
        # Validate customer ID format (3 letters, 5 numbers, 2 letters, a dash, and finally an A or a Q)
        if re.match(r'^[A-Za-z]{3}\d{5}[A-Za-z]{2}[-][AQ]$', customer_id):
            return customer_id
        else:
            raise ValueError("Invalid customer ID.")

    def validate_item_name(self, item_name):
        # length of item name has been fixed to 20 max can be changed again as required.
        if len(item_name) <= 20 and re.match(r'^[A-Za-z0-9 ]+$', item_name):
            return item_name
        else:
            raise ValueError("Invalid item name.")

    def validate_quantity(self, quantity):
        # values has been set to max 10 but can be changed as per requirements.
        if 0 < quantity <= 10:
            return quantity
        else:
            raise ValueError("Invalid quantity.")


# Example usage
inventory = Inventory()
cart = ShoppingCart("ABC12345XY-A")
cart.add_item("Item 1", 2)
cart.add_item("Item 2", 1)
cart.add_item("Item 3", 3)
cart.update_item("Item 1", 5)
cart.remove_item("Item 2")
total_cost = cart.total_cost(inventory)
print("Total Cost:", total_cost)
