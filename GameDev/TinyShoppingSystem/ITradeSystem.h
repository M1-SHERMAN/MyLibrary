#ifndef ITRADESYSTEM_H_
#define ITRADESYSTEM_H_

#include <string>

class ITradeSystem
{
public:
    virtual ~ITradeSystem() = default;
    virtual bool buy_item(const std::string &item_id, int quantity) = 0;
    virtual bool sell_item(const std::string &item_id, int quantity) = 0;
    virtual void display_inventory() const = 0;
};

#endif // ITRADESYSTEM_H_