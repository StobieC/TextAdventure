#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include "Weapon.h"
#include "Armour.h"

#include <list>
#include <utility>
#include <iostream>

class Inventory
{
    public:

        std::list<std::pair<Item*, int>> items;
        std::list<std::pair<Weapon*, int>> weapons;
        std::list<std::pair<Armour*, int>> armour;

        Inventory() {}

        Inventory(std::list<std::pair<Item*, int>> items,
        std::list<std::pair<Weapon*, int>> weapons,
        std::list<std::pair<Armour*, int>> armour)
    {
        this->items = items;
        this->weapons = weapons;
        this->armour = armour;
    }

// Add an item to the inventory, specified by a pointer to it
// from the item atlas
void add_item(Item* item, int count)
{
    // Increase the quantity if the item already exists
    for(auto& it : this->items)
    {
        if(it.first == item) it.second += count;
        return;
    }
    // If the item doesn't already exist in the inventory, then a
    // pair must be created too
    this->items.push_back(std::make_pair(item, count));
}


void add_weapon(Weapon* weapon, int count)
{
    for(auto& it : this->weapons)
    {
        if(it.first == weapon)
        {
            it.second += count;
            return;
        }
    }
    this->weapons.push_back(std::make_pair(weapon, count));
}


void add_armour(Armour* armour, int count)
{
    for(auto& it : this->armour)
    {
        if(it.first == armour)
        {
            it.second += count;
            return;
        }
    }
    this->armour.push_back(std::make_pair(armour, count));
}

// Remove the specified number of items from the inventory
void remove_item(Item* item, int count)
{
    // Iterate through the items, and if they are found then decrease
    // the quantity by the quantity removed
    for(auto& it : this->items)
    {
        if(it.first == item) it.second -= count;
    }
    // Iterate through the list again, and remove any elements from
    // the list that have zero or less for their quantity
    this->items.remove_if([](std::pair<Item*, int>& element)
    {
        return element.second < 1;
    });
}


void remove_weapon(Weapon* weapon, int count)
{
    for(auto& it : this->weapons)
    {
        if(it.first == weapon) it.second -= count;
    }
    this->weapons.remove_if([](std::pair<Weapon*, int>& element)
    {
        return element.second < 1;
    });
}

void remove_armour(Armour* armour, int count)
{
    for(auto& it : this->armour)
    {
        if(it.first == armour) it.second -= count;
    }
    this->armour.remove_if([](std::pair<Armour*, int>& element)
    {
        return element.second < 1;
    });
}

void merge(Inventory* inventory)
{

    if(inventory == this) return;

    // Loop through the items to be added, and add them. Our addition
    // function will take care of everything else for us
    for(auto it : inventory->items)
    {
        this->add_item(it.first, it.second);
    }
    // Do the same for the weapons
    for(auto it : inventory->weapons)
    {
        this->add_weapon(it.first, it.second);
    }
    // Do the same for the armour
    for(auto it : inventory->armour)
    {
        this->add_armour(it.first, it.second);
    }

    return;
}

// Remove all items from the inventory
void clear()
{
    this->items.clear();
    this->weapons.clear();
    this->armour.clear();
}

// Output a list of the items
int print_items(bool label = false)
{
    unsigned int i = 1;

    for(auto it : this->items)
    {
        // Number the items if asked
        if(label) std::cout << i++ << ": ";
        // Output the item name, quantity and description
        std::cout << it.first->name << " (" << it.second << ") - ";
        std::cout << it.first->description << std::endl;
    }

    // Return the number of items outputted, for convenience
    return this->items.size();
}

// Same as for items
int print_weapons(bool label = false)
{
    unsigned int i = 1;

    for(auto it : this->weapons)
    {
        if(label) std::cout << i++ << ": ";
        std::cout << it.first->name << " (" << it.second << ") - ";
        std::cout << it.first->description << std::endl;
    }

    return this->weapons.size();
}

// Same as for items
int print_armour(bool label = false)
{
    unsigned int i = 1;

    for(auto it : this->armour)
    {
        if(label) std::cout << i++ << ": ";
        std::cout << it.first->name << " (" << it.second << ") - ";
        std::cout << it.first->description << std::endl;
    }

    return this->armour.size();
}

// Print the entire inventory; items, then weapons, then armour,
// but if the inventory is empty then output "Nothing"
void print(bool label = false)
{
    if(this->items.size() == 0 &&
        this->weapons.size() == 0 &&
        this->armour.size() == 0)
    {
        std::cout << "Shit all" << std::endl;
    }
    else
    {
        this->print_items(label);
        this->print_weapons(label);
        this->print_armour(label);
    }

    return;
}
};

#endif // INVENTORY_H
