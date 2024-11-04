#ifndef SHOP_INVENTORY_H_
#define SHOP_INVENTORY_H_

#include "../interface/IInventory.h"
#include "../interface/IItem.h"
#include "../item/potion_type.h"

#include <unordered_map>
#include <iostream>

class ShopInventory : public IInventory
{
private:
	double current_money_{ 1000000 };
	std::unordered_map<std::string, int> items_;
	const std::unordered_map<std::string, std::unique_ptr<IItem>> &items_ptr_;
public:
	explicit ShopInventory(const std::unordered_map<std::string, std::unique_ptr<IItem>> &items)
		: items_ptr_(items) {}

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
};

#endif // SHOP_INVENTORY_H_