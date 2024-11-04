# System Architecture Overview

This is a simple potion shop system, built for learning purposes.
The system implements a potion shop using interface-based communication between components.

The core interfaces are:

- `ITradeSystem`: Handles trading operations
- `IInventory`: Manages inventory and money
- `IItem`: Defines item properties

# Interface Communication Flow

## 1. Shop to Inventory Communication

The `Shop` class communicates with player's inventory through the `IInventory` interface:

```cpp:GameDev/TinyShoppingSystem/shop.h
class Shop : public ITradeSystem {
private:
    std::unique_ptr<IInventory> inventory_;  // Composition using interface
    // ... other members ...
}
```

Key interactions:

- Money management: `get_current_money()`, `set_current_money()`
- Item management: `add_item()`, `remove_item()`

## 2. Shop to Items Communication

Items are accessed through the `IItem` interface:

```cpp:GameDev/TinyShoppingSystem/shop.h
private:
    std::unordered_map<std::string, std::unique_ptr<IItem>> items_;
```

Key interactions:

- Price queries: `get_buy_price()`, `get_sell_price()`
- Item information: `get_name()`, `get_id()`, `get_type()`

## 3. Trading System Interface

The shop implements `ITradeSystem` to standardize trading operations:

```cpp:GameDev/TinyShoppingSystem/ITradeSystem.h
class ITradeSystem {
public:
    virtual bool buy_item(const std::string &item_id, int quantity) = 0;
    virtual bool sell_item(const std::string &item_id, int quantity) = 0;
    virtual void display_inventory() const = 0;
};
```

# Benefits of Interface-Based Design

1. **Loose Coupling**

   - `Shop` class doesn't depend on concrete implementations
   - Easy to swap implementations (e.g., different inventory systems)

2. **Extensibility**

   - New item types can be added by implementing `IItem`
   - Different inventory systems can be created by implementing `IInventory`

3. **Testability**
   - Interfaces can be mocked for unit testing
   - Components can be tested in isolation

# Implementation Example

Adding a new potion type:

```cpp
// 1. Add new type to enum
enum class potion_type {
    mp_potion,
    hp_potion,
    stamina_potion  // New type
};

// 2. Create potion instance
items_["stamina_potion"] = std::make_unique<Potion>(
    "Stamina Potion",
    "stamina_potion",
    potion_type::stamina_potion,
    200.0
);
```
