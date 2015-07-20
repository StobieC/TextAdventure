#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
#include <string>

class Weapon : public Item
{
    public:

        unsigned damage;
        double hitRate;

        Weapon(std::string name, std::string description, int damage,
         double hitRate) :Item(name,description)
        {

            this->damage = damage;
            this->hitRate = hitRate;

        }

        Weapon() {}

};

#endif // WEAPON_H
