# Tiny Shopping System - Learning Project

This is a simple shopping system built for learning purposes.

## 1. Interface Design & Dependency Injection

### 1.1 Core Interfaces

The system defines three main interfaces:

- `ITradeSystem`: Trading operations interface

```6:13:GameDev/TinyShoppingSystem/interface/ITradeSystem.h
class ITradeSystem
{
public:
    virtual ~ITradeSystem() = default;
	virtual bool buy_item(const std::string &item_id, int quantity, IInventory *player_inventory) = 0;
	virtual bool sell_item(const std::string &item_id, int quantity, IInventory *player_inventory) = 0;
};
```

- `IInventory`: Inventory management interface

```6:16:GameDev/TinyShoppingSystem/interface/IInventory.h
class IInventory
{
public:
    virtual ~IInventory() = default;
    virtual bool add_item(const std::string &item_id, int quantity) = 0;
    virtual bool remove_item(const std::string &item_id, int quantity) = 0;
    [[nodiscard]] virtual int get_item_quantity(const std::string &item_id) const = 0;
    [[nodiscard]] virtual double get_current_money() const = 0;
    virtual bool set_current_money(double money) = 0;
    virtual void display_inventory() const = 0;
};
```

- `IItem`: Item properties interface

```6:15:GameDev/TinyShoppingSystem/interface/IItem.h
class IItem
{
public:
    virtual ~IItem() = default;
    [[nodiscard]] virtual std::string get_name() const = 0;
    [[nodiscard]] virtual std::string get_id() const = 0;
    [[nodiscard]] virtual potion_type get_type() const = 0;
    [[nodiscard]] virtual double get_buy_price() const = 0;
    [[nodiscard]] virtual double get_sell_price() const = 0;
};
```

### 1.2 Dependency Injection Implementation

The `Shop` class uses smart pointers and interfaces for dependency injection:

```15:18:GameDev/TinyShoppingSystem/shop/shop.h
private:
	std::unique_ptr<IInventory> shop_inventory_;
	std::unordered_map<std::string, std::unique_ptr<IItem>> items_;
```

## 2. Modern C++ Features

### 2.1 Smart Pointers

- Using `std::unique_ptr` for automatic resource management
- Preventing memory leaks

```21:26:GameDev/TinyShoppingSystem/shop/shop.h
	Shop()
	{
		shop_inventory_ = std::make_unique<ShopInventory>(items_);
		initialize_items();
	}
```

### 2.2 Override Keyword

- Explicitly marking virtual function overrides
- Preventing accidental signature mismatches

```27:50:GameDev/TinyShoppingSystem/item/potions.h
	[[nodiscard]] std::string get_name() const override
	{
		return name_;
	}

	[[nodiscard]] std::string get_id() const override
	{
		return id_;
	}

	[[nodiscard]] potion_type get_type() const override
	{
		return type_;
	}

	[[nodiscard]] double get_buy_price() const override
	{
		return buy_price_;
	}

	[[nodiscard]] double get_sell_price() const override
	{
		return sell_price_;
	}
```

### 2.3 [[nodiscard]] Attribute

- Ensuring return values are not ignored

```12:13:GameDev/TinyShoppingSystem/interface/IInventory.h
    [[nodiscard]] virtual int get_item_quantity(const std::string &item_id) const = 0;
    [[nodiscard]] virtual double get_current_money() const = 0;
```

### 2.4 Const Member Functions

- Guaranteeing function won't modify object state

```104:117:GameDev/TinyShoppingSystem/shop/shop_inventory.h
	void display_inventory() const override
	{
		std::cout << "Shop inventory: " << "\n";
		std::cout << "Current money: " << get_current_money() << "\n";

		for (const auto &item : items_ptr_)
		{
			std::cout << "name: " << item.second->get_name() << ", "
					  << "quantity: " << get_item_quantity(item.first) << ", "
					  << "type: " << potion_type_to_string(item.second->get_type()) << ", "
					  << "buy price: " << item.second->get_buy_price() << ", "
					  << "sell price: " << item.second->get_sell_price() << "\n";
		}
	}
```

## 3. System Architecture Features

### 3.1 Loose Coupling

- Component decoupling through interface separation
- Easy implementation swapping
- Facilitates unit testing

### 3.2 Extensibility

- New item types can be added by implementing `IItem`
- New inventory systems can be easily added

## 4. Key Learning Points Summary

1. Interface Design Principles

   - Interface Segregation
   - Dependency Inversion
   - Programming to Interfaces

2. Modern C++ Best Practices

   - Resource management with smart pointers
   - Explicit function semantics
   - Const correctness

3. Object-Oriented Design

   - Composition over inheritance
   - Interface-based polymorphism
   - Single Responsibility Principle

4. Implementation Examples
   - Clean separation of concerns
   - Type-safe enum classes
   - RAII principles through smart pointers
