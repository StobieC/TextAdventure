#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>
#include <cstdlib>
#include <ctime>

#include "Creature.h"
#include "Dialogue.h"
#include "Item.h"
#include "Area.h"
#include "Armour.h"
#include "Item.h"
#include "Weapon.h"
#include "atlas.h"
#include "Battle.h"

Creature dialogue_newchar();
void dialogue_menu(Creature& player);
int main(void)
{

    std::vector<Creature> creatureAtlas;
    std::vector<Item> itemAtlas;
    std::vector<Weapon> weaponAtlas;
    std::vector<Armour> armourAtlas;
    std::vector<Area> areaAtlas;

    // Build the atlases
    buildatlas_creature(creatureAtlas);
    buildatlas_item(itemAtlas);
    buildatlas_weapon(weaponAtlas);
    buildatlas_armour(armourAtlas);
    buildatlas_area(areaAtlas, itemAtlas, weaponAtlas,
    armourAtlas, creatureAtlas);
    Creature player;

	srand(time(NULL));

// Main game menu dialogue
	int result = Dialogue(
		"▒▒▒░░░░░░░░░░▄▐░░░░\n"
		"▒░░░░░░▄▄▄░░▄██▄░░░\n"
		"░░░░░░▐▀█▀▌░░░░▀█▄░\n"
        "░░░░░░▐█▄█▌░░░░░░▀█▄\n"
        "░░░░░░░▀▄▀░░░▄▄▄▄▄▀▀\n"
        "░░░░░▄▄▄██▀▀▀▀░░░░░\n"
        "░░░░█▀▄▄▄█░▀▀░░░░░░\n"
        "░░░░▌░▄▄▄▐▌▀▀▀░░░░░\n"
        "░▄░▐░░░▄▄░█░▀▀░░░░░\n"
        "░▀█▌░░░▄░▀█▀░▀░░░░░\n"
        "░░░░░░░░▄▄▐▌▄▄░░░░░\n"
        "░░░░░░░░▀███▀█░▄░░░\n"
        "░░░░░░░▐▌▀▄▀▄▀▐▄░░░\n"
        "░░░░░░░▐▀░░░░░░▐▌░░\n"
        "░░░░░░░█░░░░░░░░█░░\n"
        "░░░░░░▐▌░░░░░░░░░█░\n"
,
		{"New Game", "Quit"}).activate();

switch(result)
	{
		case 1: player = dialogue_newchar(); break;
		default: return 0; break;
	}

	// Set the current area to be the first area in the atlas, essentially
	// placing the player there upon game start
	Area* currentArea = &(areaAtlas[0]);

	// Play the game until a function breaks the loop and closes it
	while(1)
	{

		if(player.health <= 0)
		{
			std::cout << "\t----YOU DIED----\n    Game Over\n";
			return 0;
		}


		//Starts a fight if there is a creature in the area atlas
		if(currentArea->creatures.size() > 0)
		{
		    for(int i = currentArea->creatures.size() - 1; i >= 0; --i)
		    {
			    Battle(&player, currentArea->creatures[i]).run();
			    // Remove the creature from the area
			    currentArea->creatures.pop_back();
		    }
        }

		// Activate the current area's dialogue
		result = currentArea->dialogue.activate();

		if(currentArea == &(areaAtlas[0]))
		{
			switch(result)
			{
				// Open the menu
				case 1:
					dialogue_menu(player);
					break;
				case 2:
				// Move to area 1
					currentArea = &(areaAtlas[1]);
					break;
				case 3:
				// Search the area
					currentArea->search(player);
					break;
				default:
					break;
			}
		}
		else if(currentArea == &(areaAtlas[1]))
		{
			switch(result)
			{
				// Open the menu
				case 0:
					dialogue_menu(player);
					break;
				// Move to area 0
				case 1:
					currentArea = &(areaAtlas[0]);
					break;
				// Search the area
				case 2:
					currentArea->search(player);
					break;
				default:
					break;
			}
		}
	}

	return 0;
}

// Create a new character
Creature dialogue_newchar()
{

	std::cout << "\n Choose your name" << std::endl;
	std::string name;
	std::cin >> name;

	int result = Dialogue(
		"\n Choose your class",
		{"Fighter", "Rogue"}).activate();

	switch(result)
	{
		// Fighter class favours health and strength
		case 1:
			return Creature(name, 35, 20, 10, 5, 10.0, 1, "Fighter");
			break;

		// Rogue class favours dexterity and hit rate
		case 2:
			return Creature(name, 30, 5, 10, 20, 15.0, 1, "Fighter");
			break;

		default:
			return Creature(name, 30, 10, 10, 10, 10.0, 1, "Adventurer");
		break;
	}
}

void dialogue_menu(Creature& player)
{
	// Output the menu
	int result = Dialogue(
		"Menu\n \n====",
		{"Items", "Equipment", "Character"}).activate();

	switch(result)
	{
		// Print the items that the player owns
		case 1:
			std::cout << "Items\n=====\n \n";
			player.inventory.print();
			std::cout << "----------------\n";
			break;

		case 2:
		{
			std::cout << "Equipment\n=========\n \n";
			std::cout << "Head: "
				<< (player.equippedArmour[Armour::Slot::HEAD] != nullptr ?
					player.equippedArmour[Armour::Slot::HEAD]->name : "Nothing")
				<< std::endl;
			std::cout << "Torso: "
				<< (player.equippedArmour[Armour::Slot::TORSO] != nullptr ?
					player.equippedArmour[Armour::Slot::TORSO]->name : "Nothing")
				<< std::endl;
			std::cout << "Legs: "
				<< (player.equippedArmour[Armour::Slot::LEGS] != nullptr ?
					player.equippedArmour[Armour::Slot::LEGS]->name : "Nothing")
				<< std::endl;
			std::cout << "Weapon: "
				<< (player.equippedWeapon != nullptr ?
					player.equippedWeapon->name : "Nothing")
				<< std::endl;

			int result2 = Dialogue(
				"",
				{"Equip Armour", "Equip Weapon", "Close"}).activate();

			// Equipping armour
			if(result2 == 1)
			{
				int userInput = 0;


				int numItems = player.inventory.print_armour(true);
				if(numItems == 0) break;

				while(!userInput)
				{
					// Choose a piece of armour to equip
					std::cout << "Equip which item?" << std::endl;
					std::cin >> userInput;

					// Equipment is numbered but is stored in a list,
					// so the number must be converted into a list element
					if(userInput >= 1 && userInput <= numItems)
					{
						int i = 1;

						for(auto it : player.inventory.armour)
						{
							if(i++ == userInput)
							{
								// Equip the armour if it is found
								player.equipArmour(it.first);
								break;
							}
						}
					}
				}
			}

			else if(result2 == 2)
			{
				int userInput = 0;
				int numItems = player.inventory.print_weapons(true);

				if(numItems == 0) break;

				while(!userInput)
				{
					std::cout << "Equip which item?" << std::endl;
					std::cin >> userInput;
					if(userInput >= 1 && userInput <= numItems)
					{
						int i = 1;

						for(auto it : player.inventory.weapons)
						{
							if(i++ == userInput)
							{
								player.equipWeapon(it.first);
								break;
							}
						}
					}
				}
			}
			std::cout << "----------------\n";
			break;
		}
		// Output the character information, including name, class, stats, level, and experience
		case 3:
			std::cout << "Character\n=========\n";
			std::cout << player.name;
			if(player.className != "") std::cout << " the " << player.className;
			std::cout << std::endl;

			std::cout << "HP: " << player.health << " / " << player.maxHealth << std::endl;
			std::cout << "Str: " << player.str << std::endl;
			std::cout << "End: " << player.endurance << std::endl;
			std::cout << "Dex: " << player.dex << std::endl;
			std::cout << "Lvl: " << player.level << " (" << player.exp;
			std::cout <<  " / " << player.expToLevel(player.level+1) << ")" << std::endl;
			std::cout << "----------------\n";
			break;
		default:
			break;
	}

	return;
}
