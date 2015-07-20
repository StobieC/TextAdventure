#ifndef CREATURE_H
#define CREATURE_H

#include "Inventory.h"
#include "Weapon.h"
#include "Armour.h"

#include <string>

class Creature
{
    public:

    std::string name;
    std::string className;

    int health;
    int maxHealth;
    int str; //damage
    int endurance; //determines max health
    int dex; //determines speed
    double hitRate;

    unsigned int level;
    unsigned int exp;

    // Items that the creature possesses
    Inventory inventory;

    // Currently equipped weapon. Used as a pointer to an atlas entry
    Weapon* equippedWeapon;

    // Armour currently equipped into each slot
    Armour* equippedArmour[Armour::Slot::N];

        Creature() {

        this->equippedArmour[Armour::Slot::HEAD]=nullptr;
        this->equippedArmour[Armour::Slot::TORSO]=nullptr;
        this->equippedArmour[Armour::Slot::LEGS]=nullptr;
        this->equippedWeapon = nullptr;
        this->level =1;
        this->exp =0;

        }


        Creature(std::string name, int health, int str, int endurance, int dex, double hitRate,
		unsigned int level = 1, std::string className = "")
	{
		this->name = name;
		this->health = health;
		this->maxHealth = health;
		this->str = str;
		this->endurance = endurance;
		this->dex = dex;
		this->hitRate = hitRate;
		this->className = className;
		this->equippedArmour[Armour::Slot::HEAD] = nullptr;
        this->equippedArmour[Armour::Slot::TORSO] = nullptr;
        this->equippedArmour[Armour::Slot::LEGS] = nullptr;
		this->equippedWeapon = nullptr;
		this->level = level;
		this->exp = 0;
	}

	void equipWeapon(Weapon* weapon)
	{
        this->equippedWeapon = weapon;
	}

	// Equip the armour into it's correct slot. A slightly more useful
    // function!
    void equipArmour(Armour* armour)
    {
        this->equippedArmour[(int)armour->slot] = armour;

        return;
    }

    //calculates the experience required to level
    unsigned int expToLevel(unsigned int level)
    {
    return 128 * level * level;
    }

    bool levelUp()
    {

        if (this ->exp >= expToLevel(this->level+1)) {
            ++level;

            unsigned int healthBoost = 0;
            unsigned int strBoost = 0;
            unsigned int enduranceBoost = 0;
            unsigned int dexBoost =0 ;

            if(level %3 == 0) {
                healthBoost = 10 + (rand() % 4) + this->endurance /4;
            }
            else {
                healthBoost = this->endurance /4;
            }

            // Fighter favours strength
			if(this->className == "Fighter")
			{
				strBoost = 1;
				enduranceBoost = 1;
				if(rand() % 2 == 0) dexBoost = 1;
			}
			// Rogues favour dex
			else if(this->className == "Rogue")
			{
				enduranceBoost = 1;
				dexBoost = 1;
				if(rand() % 2 == 0) strBoost = 1;
			}

			// Adjust all of the variables accordingly
			this->maxHealth += healthBoost;
			this->str += strBoost;
			this->endurance += enduranceBoost;
			this->dex += dexBoost;

			// Tell the user that they grew a level, what the boosts where
			// and what their stats are now
			std::cout << this->name << " grew to level " << level << "!\n";
			std::cout << "Health +" << healthBoost << " -> " << this->maxHealth << std::endl;
			std::cout << "Str +" << strBoost << " -> " << this->str << std::endl;
			std::cout << "End +" << enduranceBoost << " -> " << this->endurance << std::endl;
			std::cout << "Dex +" << dexBoost << " -> " << this->dex<< std::endl;
			std::cout << "----------------\n";

			return true;
		}
		return false;

        }

    };







#endif //CREATURE_H
