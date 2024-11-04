#ifndef PLAYER_BACKPACK_H
#define PLAYER_BACKPACK_H

#include "IInventory.h"

#include <unordered_map>

class PlayerBackpack : public IInventory
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

	int get_item_quantity(const std::string &item_id) const override
	{
		auto it = items_.find(item_id);
		return it != items_.end() ? it->second : 0;
	}

	double get_current_money() const override
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
};
#endif // PLAYER_BACKPACK_H