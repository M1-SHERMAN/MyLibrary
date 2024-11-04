#ifndef SHOP_H_
#define SHOP_H_

#include "player_backpack.h"
#include "potions.h"
#include "ITradeSystem.h"
#include "shop_inventory.h"

#include <memory>
#include <unordered_map>


class Shop : public ITradeSystem
{
private:
	std::unique_ptr<IInventory> shop_inventory_;
	std::unique_ptr<IInventory> player_inventory_;
	std::unordered_map<std::string, std::unique_ptr<IItem>> items_;

public:
	Shop()
	{
		shop_inventory_ = std::make_unique<ShopInventory>();
		player_inventory_ = std::make_unique<PlayerBackpack>();
		initialize_items();
	}

	bool buy_item(const std::string &item_id, const int quantity) override
	{
		const auto it = items_.find(item_id); // find the item in the shop
		if (it == items_.end())
		{
			return false;
		}

		const double total_price = it->second->get_buy_price() * quantity; // it->second points to the item in the shop
		const int shop_inventory = shop_inventory_->get_item_quantity(item_id);
		
		// check if the player has enough money to buy the item
		if (player_inventory_->get_current_money() < total_price)
		{
			std::cout << "You don't have enough money(" << total_price <<") "
						<< "still need " << total_price - player_inventory_->get_current_money() << "\n";
			return false;
		}
		// check if the shop has enough item to sell
		if (shop_inventory < quantity)
		{
			std::cout << "Shop doesn't have enough item, currently have: "
						<< shop_inventory << "\n";
			return false;
		}

		// subtract the total price from the player money
		if (player_inventory_->set_current_money(-total_price))
		{
			// add the total price to the shop money
			shop_inventory_->set_current_money(total_price);
			// add the item to the player inventory
			return player_inventory_->add_item(item_id, quantity);
		}

		return false;
	}

	bool sell_item(const std::string &item_id, const int quantity) override
	{
		const auto it = items_.find(item_id); // find the item in the shop
		if (it == items_.end())
		{
			return false;
		}
		
		double total_price = it->second->get_sell_price() * quantity;
		int player_inventory = player_inventory_->get_item_quantity(item_id);

		// check if the player has enough quantity to sell
		if (player_inventory < quantity)
		{
			std::cout << "You don't have enough item, currently have: "
						<< player_inventory << "\n";
			return false;
		}

		// check if the shop has enough money to buy the items
		if (shop_inventory_->get_current_money() < total_price)
		{
			std::cout << "Shop doesn't have enough money("
						<< shop_inventory_->get_current_money() << ")" << "\n";
			return false;
		}

		if(shop_inventory_->set_current_money(-total_price))
		{
			// add the total price to the player money
			player_inventory_->set_current_money(total_price);
			// remove the item from the player inventory
			return player_inventory_->remove_item(item_id, quantity);
		}
		return false;

	}

	void display_inventory() const override
	{
		std::cout << "Shop inventory: " << "\n";
		std::cout << "Current money: " << shop_inventory_->get_current_money() << "\n";

		for (const auto &item : items_)
		{
			std::cout << "name: " << item.second->get_name() << ", "
					  << "quantity: " << shop_inventory_->get_item_quantity(item.first) << ", "
					  << "type: " << potion_type_to_string(item.second->get_type()) << ", "
					  << "buy price: " << item.second->get_buy_price() << ", "
					  << "sell price: " << item.second->get_sell_price() << "\n";
		}
	}
	
	[[nodiscard]] const IInventory* get_player_backpack() const
	{
		// because we already have an instance of PlayerBackpack, we can return it directly
		return player_inventory_.get();
	}
	

private:
	void initialize_items()
	{
		// add new item here
		// and don't forget to add the item to potion_type class
		items_["hp_potion"] = std::make_unique<Potion>("HP Potion", "hp_potion", potion_type::hp_potion, 100.0);
		items_["mp_potion"] = std::make_unique<Potion>("MP Potion", "mp_potion", potion_type::mp_potion, 150.0);
	}
};

#endif // SHOP_H_
