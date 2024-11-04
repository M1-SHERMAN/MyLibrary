#ifndef ITRADESYSTEM_H_
#define ITRADESYSTEM_H_

#include <string>
#include "IInventory.h"
class ITradeSystem
{
public:
    virtual ~ITradeSystem() = default;
    virtual bool buy_item(const std::string &item_id, int quantity, IInventory *player_inventory) = 0;
    virtual bool sell_item(const std::string &item_id, int quantity, IInventory *player_inventory) = 0;
};

#endif // ITRADESYSTEM_H_