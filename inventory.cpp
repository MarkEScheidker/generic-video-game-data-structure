#include "inventory.hpp"


Inventory::~Inventory()
{

}


/// provided
void Inventory::Init(JsonItemBuilder &jsonBuilder, const std::vector<int> & uids)
{
    for(const auto & uid : uids)
    {
        _inventoryData.emplace(uid, {jsonBuilder, static_cast<uint32_t>(uid)});  //emplace not working here, something about being overloaded
    }


}

void Inventory::AddItemToInventory(const Item &item)
{
    _inventoryData.emplace(item.UID(), item);
}


Item Inventory::LootAnItem(uint32_t uid)
{
    if(_inventoryData.count(uid) != 0)
    {
        Item retval = _inventoryData.at(uid);
        _inventoryData.erase(uid);
        return retval;
    }
    return Item{};
}

void Inventory::LootAnotherInventory(Inventory & inventory)
{
    std::vector<uint32_t> itemKeys;            //not the most elegant solution, but the only one I could find
    for(auto elem : inventory._inventoryData)
        itemKeys.push_back(elem.first);

    for(int i = 0; i < itemKeys.size(); i ++)
    {
        Item lootedItem = inventory._inventoryData.at(itemKeys.at(i));
        _inventoryData.emplace(lootedItem.UID(), lootedItem);
        inventory._inventoryData.erase(itemKeys.at(i));
    }

}


bool Inventory::IsEmpty() const
{
    return _inventoryData.empty();

}


// implement
// loops through the list and calls the item to 
// print its contents though the Item::PrintData()
void Inventory::PrintInventory() const
{
    std::vector<uint32_t> keys;                    //using strange keys method
    for(auto elem : _inventoryData)
        keys.push_back(elem.first);

    for(int i = 0; i < keys.size(); i ++)
    {
        uint32_t key = keys.at(i);
        std::cout << _inventoryData.at(key) << std::endl;
    }
}
