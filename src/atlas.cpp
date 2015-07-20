#include "atlas.h"
#include "Creature.h"

void buildatlas_creature(std::vector<Creature>& atlas)
{

    // Creature(Name, Health, Str, End, Dex, Hit Rate, Level)
    atlas.push_back(Creature("Rat", 8, 8, 8, 12, 2.0, 1));

    return;
}

void buildatlas_item(std::vector<Item>& atlas)
{
    // Item(Name, Description)
    atlas.push_back(Item("Gold Coin",
        "A small disc made of lustrous metal"));
    atlas.push_back(Item("Iron Key",
        "A heavy iron key with a simple cut"));

    return;
}

void buildatlas_weapon(std::vector<Weapon>& atlas)
{
    // Weapon(Name, Description, Damage, Hit Rate)
    atlas.push_back(Weapon("Iron Dagger",
        "A short blade made of iron with a leather-bound hilt",
        5, 10.0));


    return;
}

void buildatlas_armour(std::vector<Armour>& atlas)
{
    // Armour(Name, Description, Defense, Slot)
    atlas.push_back(Armour("Leather Cuirass",
        "Torso armour made of tanned hide", 4, Armour::Slot::TORSO));

    return;
}

void buildatlas_area(std::vector<Area>& atlas,
    std::vector<Item>& items, std::vector<Weapon>& weapons,
    std::vector<Armour>& armour, std::vector<Creature>& creatures)
{

    atlas.push_back(Area(Dialogue(
        "You are in room 1",
        {"Menu","Go to room 2", "Search"}),
        Inventory(
        {
            std::make_pair(&items[0], 5)

        },
        {
            std::make_pair(&weapons[0], 1)
        },
        {
            std::make_pair(&armour[0], 1)
        }),
        {
        }));

    atlas.push_back(Area(Dialogue(
        "You are in room 2",
        {"Go to room 1", "Search"}),
        Inventory(
        {
            std::make_pair(&items[0], 10),
            std::make_pair(&items[1], 1)
        },
        {
        },
        {
        }),
        {
            &creatures[0]
        }));
/*
        atlas.push_back(Area(Dialogue(
        "Message",
        {"Menu", "Option"}),
        Inventory(
        {
            //items
        },
        {
            //weapons
        },
        {
            //armour
        }),
        {
            //enemies
        }));
*/
    return;
}
