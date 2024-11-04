#ifndef SHOP_H_
#define SHOP_H_

#include "player_backpack.h"
#include "potions.h"
#include "ITradeSystem.h"

#include <memory>
#include <unordered_map>

class Shop : public ITradeSystem
{
private:
	std::unique_ptr<IInventory> inventory_;
	std::unordered_map<std::string, std::unique_ptr<IItem>> items_;

public:
	Shop()
	{
		inventory_ = std::make_unique<PlayerBackpack>();
		initialize_items();
	}

	bool buy_item(const std::string &item_id, int quantity) override
	{
		auto it = items_.find(item_id);
		if (it == items_.end())
		{
			return false;
		}

		double total_price = it->second->get_buy_price() * quantity;
		if (inventory_->get_current_money() < total_price)
		{
			return false;
		}

		if (inventory_->set_current_money(-total_price))
		{
			return inventory_->add_item(item_id, quantity);
		}

		return false;
	}

	bool sell_item(const std::string &item_id, int quantity) override
	{
		auto it = items_.find(item_id);
		if (it == items_.end())
		{
			return false;
		}

		double total_price = it->second->get_sell_price() * quantity;
		if (inventory_->set_current_money(total_price))
		{
			return inventory_->remove_item(item_id, quantity);
		}
		return false;
	}

	void display_inventory() const override
	{
		std::cout << "Current money: " << inventory_->get_current_money() << "\n";

		for (const auto &item : items_)
		{
			std::cout << "name: " << item.second->get_name() << ", "
					  << "quantity: " << inventory_->get_item_quantity(item.first) << ", "
					  << "type: " << potion_type_to_string(item.second->get_type()) << ", "
					  << "buy price: " << item.second->get_buy_price() << ", "
					  << "sell price: " << item.second->get_sell_price() << "\n";
		}
	}

private:
	void initialize_items()
	{
		items_["hp_potion"] = std::make_unique<Potion>("HP Potion", "hp_potion", potion_type::hp_potion, 100.0);
		items_["mp_potion"] = std::make_unique<Potion>("MP Potion", "mp_potion", potion_type::mp_potion, 150.0);
	}
};

#endif // SHOP_H_
