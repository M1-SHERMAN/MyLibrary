#ifndef IINVENTORY_H_
#define IINVENTORY_H_

#include <string>

class IInventory
{
public:
    virtual ~IInventory() = default;
    virtual bool add_item(const std::string &item_id, int quantity) = 0;
    virtual bool remove_item(const std::string &item_id, int quantity) = 0;
    [[nodiscard]] virtual int get_item_quantity(const std::string &item_id) const = 0;
    [[nodiscard]] virtual double get_current_money() const = 0;
    virtual bool set_current_money(double money) = 0;
    virtual void display_inventory() const = 0;
};

#endif // IINVENTORY_H_