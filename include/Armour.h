#ifndef ARMOUR_H
#define ARMOUR_H

#include "Item.h"
#include <string>

class Armour : public Item
{
    public:

        enum Slot {TORSO, HEAD, LEGS, N};
        Slot slot;

        int defence;

        Armour(std::string name, std::string description,int defence, Armour::Slot slot)
        {

        this-> defence = defence;
        this-> slot = slot;

        }

        Armour() {}

};

#endif // ARMOUR_H
