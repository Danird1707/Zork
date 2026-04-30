#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"

class Item : public Entity {
public:
    Item(const std::string& name, const std::string& description);
    ~Item();
};

#endif
