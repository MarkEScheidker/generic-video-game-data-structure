#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "stack.hpp"
//#include "dictionary.hpp"
#include "item.hpp"
//#include "vector.hpp"
#include <vector>
#include <map>


class Inventory
{
public: 
    Inventory() = default;
    ~Inventory();

    void Init(JsonItemBuilder &jsonBuilder, const std::vector<int> &uids);
    Item LootAnItem(uint32_t uid);
    void AddItemToInventory(const Item &item);
    void LootAnotherInventory(Inventory & inventory);

    bool IsEmpty() const;

    void PrintInventory() const;

private:

    std::map<uint32_t, Item> _inventoryData;
};


#endif
