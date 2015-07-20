#ifndef AREA_H
#define AREA_H

#include <vector>

#include "Inventory.h"
#include "Creature.h"
#include "Dialogue.h"

class Area
{
    public:

        // Dialogue is run whenever the area is entered
        Dialogue dialogue;

        // Items contained within the area.
        Inventory items;

        // Creatures contained within the area.
        std::vector<Creature*> creatures;

        void search(Creature& player)
        {

            std::cout << "You find:" << std::endl;

            this->items.print();
            player.inventory.merge(&(this->items));
            this->items.clear();

        }

        Area() {}

        Area(Dialogue dialogue, Inventory items,
        std::vector<Creature*> creatures)
        {
            this->dialogue = dialogue;
            this->items = items;
            this->creatures = creatures;
        }

    protected:
    private:
};

#endif // AREA_H
