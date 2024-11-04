#include <iostream>

#include "shop.h"

int main(int argc, char *argv[])
{
	using std::cin;
	using std::cout;

	cout << "Welcome to the potion shop" << "\n";
	Shop shop;
	bool is_quit = false;
	while (!is_quit)
	{
		cout << "--------------Main Menu--------------" << "\n";
		cout << "1. Buy HP potion" << "\n";
		cout << "2. Buy MP potion" << "\n";
		cout << "3. Sell HP potion" << "\n";
		cout << "4. Sell MP potion" << "\n";
		cout << "5. Show money and potion" << "\n";
		cout << "6. Quit" << "\n";
		cout << "Choose your action(input 1-6): ";
		int action;
		int quantity;
		cin >> action;
		switch (action)
		{
		case 1:
			cout << "Buying HP potion, please enter quantity: ";
			cin >> quantity;
			shop.buy_item("hp_potion", quantity);
			cout << "You have bought " << quantity << " HP potions" << "\n";
			
			cout << "Press any key to continue...\n";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin.get();
			break;
		case 2:
			cout << "Buying MP potion, please enter quantity: ";
			cin >> quantity;
			shop.buy_item("mp_potion", quantity);
			cout << "You have bought " << quantity << " MP potions" << "\n";
			
			cout << "Press any key to continue...\n";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin.get();
			break;
		case 3:
			cout << "Selling HP potion, please enter quantity: ";
			cin >> quantity;
			shop.sell_item("hp_potion", quantity);
			cout << "You have sell " << quantity << " HP potions" << "\n";

			cout << "Press any key to continue...\n";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin.get();
			break;
		case 4:
			cout << "Selling MP potion, please enter quantity: ";
			cin >> quantity;
			shop.sell_item("mp_potion", quantity);
			cout << "You have sell " << quantity << " MP potions" << "\n";

			cout << "Press any key to continue...\n";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin.get();
			break;
		case 5:
			shop.display_inventory();
			
			cout << "Press any key to continue...\n";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin.get();
			break;
		case 6:
			is_quit = true;
			break;
		default:
			cout << "Invalid action, please enter number between 1- 6" << "\n";

			cout << "Press any key to continue...\n";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin.get();
			break;
		}
	}
	return 0;
}
