#ifndef BACKPACK_MANAGER_H_
#define BACKPACK_MANAGER_H_

#include "player_inventory.h"

#include <memory>

class BackpackManager
{
private:
	std::unique_ptr<IInventory> player_inventory_;
public:
	BackpackManager()
	{
		player_inventory_ = std::make_unique<PlayerInventory>();
	}

	// suggest to use this function to get the player backpack
	[[nodiscard]] const IInventory* get_player_backpack() const
	{
		return player_inventory_.get();
	}

	// only use it when you want to modify the player backpack
	[[nodiscard]] IInventory* get_mutable_player_backpack() const
	{
		return player_inventory_.get();
	}
};

#endif // BACKPACK_MANAGER_H_
