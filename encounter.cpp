#include "encounter.hpp"


Encounter::Encounter()
{

}


// implement
// delete all entities within this list.
// YOU MUST EXPLICITLY DELETE ALL ENTITIES
// SINCE OUR DICTIONARY HOLDS POINTERS
Encounter::~Encounter()
{
    std::vector<uint32_t> keys;             
    for(auto elem : _encounterDictionary)
        keys.push_back(elem.first);

    for(int i = 0; i < keys.size(); i ++)
    {
        Entity * toDelete = _encounterDictionary.at(keys.at(i));
        delete toDelete;
    }


}

// implement
// inserts a new Entity node with the entity parameter as its
// data.
// HINT: ALL ITEMS ARE INSERTED TO THE BACK OF THIS LIST.
// HINT: You do NOT have a _lastItem in this list, so you will
//       have to locate it every time you add an item to the 
//       back of the list.
void Encounter::AddEntity(Entity *entity)
{
    _encounterDictionary.emplace(entity->UID(), entity);   

    if(entity->UID())  // emplace does not have a boolean output, so I need to check after adding it if it exists in the map
    {
        std::cout << "FAILED TO ADD ENTITY: " << entity->UID() << std::endl;
    }
}


// implement
// output only the specific entities status
// if the entity does not exist, call PrintBadAccessError with
// the entityID in question.
// HINT: use findEntity to find the correct entity.
// HINT: use Entity::OutputStatus() to print the entity's status
void Encounter::PrintEntityStatus(uint32_t entityID) const
{
    if(_encounterDictionary.count(entityID) != 0)
    {
        Entity * tmp = _encounterDictionary.at(entityID);
        tmp->OutputStatus();        


    }
    else
    {
        PrintBadAccessError(entityID);
    }    
}

// implement
// print the status of all entities in the encounter
// between each unit, call Bars() to print bars to make the
// output better
// HINT: You are going to use Entity::OutputStatus() 
void Encounter::PrintAllStatuses() const
{
    std::vector<uint32_t> keys;                 //using strange keys method
    for(auto elem : _encounterDictionary)
        keys.push_back(elem.first);

    for(int i = 0; i < keys.size(); i ++)
    {
        Entity * entity = _encounterDictionary.at(keys.at(i));

        if(entity != nullptr)
        {
            entity->OutputStatus();
        }

        if(i < keys.size() - 1)
        {
            Bars();
        }
    }
}


// provided for you
void Encounter::UseAction(uint32_t attackerUID, uint32_t targetUID, const std::string &spellName, const std::string & args)
{
    if(_encounterDictionary.count(attackerUID) == 0) //edited to use count which is not boolean
    {
        PrintBadAccessError(attackerUID);
    }
    if(_encounterDictionary.count(targetUID) == 0) //edited to use count which is not boolean
    {
        PrintBadAccessError(targetUID);
    }


    Entity *attacker = _encounterDictionary.at(attackerUID);
    Entity *target = _encounterDictionary.at(targetUID);


    if(attacker == nullptr)
    {
        PrintBadAccessError(attackerUID);
        return;
    }

    if(target == nullptr)
    {
        PrintBadAccessError(targetUID);
        return;
    }

    attacker->UseAction(target, spellName, args);

    if(!target->IsAlive())
    {
        attacker->LootAnEntity(target);
        
        if(_encounterDictionary.erase(target->UID()) == 0) 
        {
            std::cout << "REMOVAL FAILED" << std::endl;
        }
        delete target;
    }
}

// provided for you
void Encounter::PrintBadAccessError(uint32_t uid) const
{
    std::cout << "Attempted to access an entity with a UID: " << uid 
              << " that did not exist within the list.  Exiting." << std::endl;
}

void Encounter::Bars() const
{
    std::cout << "--------------------------------" << std::endl;
}