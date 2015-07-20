#ifndef ITEM_H
#define ITEM_H

#include <string>


class Item
{
    public:

        std::string name;
        std::string description;

        Item(std::string name, std::string description)
        {

        this->name= name;
        this->description=description;

        }

        Item()
        {
        }

};

#endif // ITEM_H
