#ifndef SHOP_INVENTORY_H_
#define SHOP_INVENTORY_H_

#include "IInventory.h"

#include <unordered_map>
#include <iostream>

class ShopInventory : public IInventory
{
private:
	double current_money_{ 1000000 };
	std::unordered_map<std::string, int> items_;
public:
	// no need to override add || remove item functions
	// because we suppose that the shop has infinite items here
	bool add_item(const std::string& item_id, int quantity) override { return true; }
	bool remove_item(const std::string& item_id, int quantity) override { return true; }

	[[nodiscard]] int get_item_quantity(const std::string& item_id) const override
	{
		// shop has infinite items
		return INT32_MAX;
	}

	[[nodiscard]] double get_current_money() const override { return current_money_; }

	bool set_current_money(const double money) override
	{
		current_money_ += money;
		return true;
	}

	void display_inventory() const override
	{
		std::cout << "Shop inventory: (infinite)" << "\n";
		std::cout << "Shop money: " << current_money_ << "\n";
	}
};

#endif // SHOP_INVENTORY_H_