#ifndef PLAYER_BACKPACK_H
#define PLAYER_BACKPACK_H

#include "../interface/IInventory.h"

#include <unordered_map>
#include <iostream>

class PlayerInventory : public IInventory
{

private:
	double current_money_{1000};
	std::unordered_map<std::string, int> items_;

public:
	bool add_item(const std::string &item_id, int quantity) override
	{
		if (quantity <= 0)
		{
			return false;
		}
		items_[item_id] += quantity;
		return true;
	}

	bool remove_item(const std::string &item_id, int quantity) override
	{
		if (quantity <= 0 || items_[item_id] < quantity)
		{
			return false;
		}
		items_[item_id] -= quantity;
		return true;
	}

	[[nodiscard]] int get_item_quantity(const std::string &item_id) const override
	{
		const auto it = items_.find(item_id);
		return it != items_.end() ? it->second : 0;
	}

	[[nodiscard]] double get_current_money() const override
	{
		return current_money_;
	}

	bool set_current_money(double money) override
	{
		if (current_money_ + money < 0)
		{
			return false;
		}
		current_money_ += money;
		return true;
	}

	void display_inventory() const override
	{
		std::cout << "Your backpack: " << "\n";
		std::cout << "Current money: " << current_money_ << "\n";

		std::cout << "Current items: " << "\n";
		for (const auto &item : items_)
		{
			if(item.second > 0)
			{
				std::cout << "Item: " << item.first
						  << ", Quantity: " << item.second << "\n";
			}
		}
	}
	
};
#endif // PLAYER_BACKPACK_H