#ifndef IITEM_H_
#define IITEM_H_

#include <string>

class IItem
{
public:
    virtual ~IItem() = default;
    [[nodiscard]] virtual std::string get_name() const = 0;
    [[nodiscard]] virtual std::string get_id() const = 0;
    [[nodiscard]] virtual potion_type get_type() const = 0;
    [[nodiscard]] virtual double get_buy_price() const = 0;
    [[nodiscard]] virtual double get_sell_price() const = 0;
};

#endif // IITEM_H_