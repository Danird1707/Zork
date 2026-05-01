#include "Item.h"

//Constructor
Item::Item(const std::string& name, const std::string& description, bool canOpen)
    : Entity(EntityType::Item, name, description)
{
    m_canOpen = canOpen;
    m_isOpen = false;
}

//Destructor
Item::~Item()
{
}

//Shows if the item can be opened
bool Item::CanOpen() const
{
    return m_canOpen;
}

//Shows if the item is opened
bool Item::IsOpen() const
{
    return m_isOpen;
}

//Opens the container
void Item::Open()
{
    if (m_canOpen) {
        m_isOpen = true;
    }
}