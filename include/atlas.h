#ifndef ATLAS_H
#define ATLAS_H

#include <vector>

#include "Creature.h"
#include "Item.h"
#include "Weapon.h"
#include "Armour.h"
#include "Area.h"

void buildatlas_creature(std::vector<Creature>& atlas);
void buildatlas_item(std::vector<Item>& atlas);
void buildatlas_weapon(std::vector<Weapon>& atlas);
void buildatlas_armour(std::vector<Armour>& atlas);
void buildatlas_area(std::vector<Area>& atlas,
	std::vector<Item>& items, std::vector<Weapon>& weapons,
	std::vector<Armour>& armour, std::vector<Creature>& creatures);

#endif // ATLAS_H
