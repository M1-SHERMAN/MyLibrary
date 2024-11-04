#ifndef SHOP_MANAGER_H_
#define SHOP_MANAGER_H_

#include "shop.h"
#include "../player/backpack_manager.h"

#include <iostream>

class ShopManager
{
private:
	Shop shop_;
	BackpackManager backpack_manager_;
	bool is_quit_ = false;
	
public:
	static void display_menu()
	{
		using std::cout;
		cout << "--------------Main Menu--------------" << "\n";
		cout << "1. Buy HP potion" << "\n";
		cout << "2. Buy MP potion" << "\n";
		cout << "3. Sell HP potion" << "\n";
		cout << "4. Sell MP potion" << "\n";
		cout << "5. Show money and potion(shop)" << "\n";
		cout << "6. Show money and potion(player)" << "\n";
		cout << "7. Quit" << "\n";
		cout << "------------------------------------" << "\n";
		cout << "Choose your action(input 1-7): ";
	}

	[[nodiscard]] bool is_quit() const
	{
		return is_quit_;
	}

	void on_update()
	{
		int action;
		std::cin >> action;
		on_input(action);
	}

	void run()
	{
		std::cout << "------Welcome to the potion shop------" << "\n";
		while (!is_quit_)
		{
			display_menu();
			on_update();
		}
	}
	
	void on_input(const int action)
	{
		using std::cin;
		using std::cout;
		
		int quantity;
		switch (action)
		{
		case 1:
			cout << "Buying HP potion, please enter quantity: ";
			cin >> quantity;
			if (quantity <= 0)
			{
				cout << "Invalid quantity, please enter a positive number" << "\n";

				cout << "Press any key to continue...\n";
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin.get();
				break;
			}

			if (shop_.buy_item("hp_potion", quantity, backpack_manager_.get_mutable_player_backpack()))
			{
				cout << "You have bought " << quantity << " HP potions" << "\n";
			}
			else
			{
				cout << "Buying HP potion failed" << "\n";
			}
			
			cout << "Press any key to continue...\n";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin.get();
			break;
		case 2:
			cout << "Buying MP potion, please enter quantity: ";
			cin >> quantity;
			if (quantity <= 0)
			{
				cout << "Invalid quantity, please enter a positive number" << "\n";

				cout << "Press any key to continue...\n";
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin.get();
				break;
			}
			if (shop_.buy_item("mp_potion", quantity, backpack_manager_.get_mutable_player_backpack()))
			{
				cout << "You have bought " << quantity << " MP potions" << "\n";
			}
			else
			{
				cout << "Buying MP potion failed" << "\n";
			}
			
			cout << "Press any key to continue...\n";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin.get();
			break;
		case 3:
			cout << "Selling HP potion, please enter quantity: ";
			cin >> quantity;
			if (quantity <= 0)
			{
				cout << "Invalid quantity, please enter a positive number" << "\n";

				cout << "Press any key to continue...\n";
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin.get();
				break;
			}
			if (shop_.sell_item("hp_potion", quantity, backpack_manager_.get_mutable_player_backpack()))
			{
				cout << "You have sold " << quantity << " HP potions" << "\n";
			}
			else
			{
				cout << "Selling HP potion failed" << "\n";
			}

			cout << "Press any key to continue...\n";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin.get();
			break;
		case 4:
			cout << "Selling MP potion, please enter quantity: ";
			cin >> quantity;
			if (quantity <= 0)
			{
				cout << "Invalid quantity, please enter a positive number" << "\n";

				cout << "Press any key to continue...\n";
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin.get();
				break;
			}
			if (shop_.sell_item("mp_potion", quantity, backpack_manager_.get_mutable_player_backpack()))
			{
				cout << "You have sold " << quantity << " MP potions" << "\n";
			}
			else
			{
				cout << "Selling MP potion failed" << "\n";
			}

			cout << "Press any key to continue...\n";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin.get();
			break;
		case 5:
			shop_.get_shop_inventory()->display_inventory();
			
			cout << "Press any key to continue...\n";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin.get();
			break;
		case 6:
			backpack_manager_.get_player_backpack()->display_inventory();

			cout << "Press any key to continue...\n";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin.get();
			break;
		case 7:
			is_quit_ = true;
			break;
		default:
			cout << "Invalid action, please enter number between 1- 6" << "\n";

			cout << "Press any key to continue...\n";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin.get();
			break;
		}
	}
};

#endif // SHOP_MANAGER_H_