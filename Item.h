#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"

class Item : public Entity {
public:
    Item(const std::string& name, const std::string& description, bool canOpen = false);
    ~Item();
    bool CanOpen() const;
    bool IsOpen() const;
    void Open();

private:
    bool m_canOpen;
    bool m_isOpen;
};

#endif
