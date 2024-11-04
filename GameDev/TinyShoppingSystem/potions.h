#ifndef POTIONS_H_
#define POTIONS_H_

#include "potion_type.h"
#include "IItem.h"

#include <string>
#include <iostream>

class Potion : public IItem
{
private:
	std::string name_;
	std::string id_;
	potion_type type_;
	double buy_price_;
	double sell_price_;

public:
	Potion(std::string name, std::string id, potion_type type, double buy_price)
		: name_(std::move(name)),
		  id_(std::move(id)),
		  type_(type),
		  buy_price_(buy_price),
		  sell_price_(buy_price * 0.75) {}

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
};

#endif // POTIONS_H_
