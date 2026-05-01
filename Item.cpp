#include "Item.h"

Item::Item(const std::string& name, const std::string& description, bool canOpen)
    : Entity(EntityType::Item, name, description)
{
    m_canOpen = canOpen;
    m_isOpen = false;
}

Item::~Item()
{
}

bool Item::CanOpen() const
{
    return m_canOpen;
}

bool Item::IsOpen() const
{
    return m_isOpen;
}

void Item::Open()
{
    if (m_canOpen) {
        m_isOpen = true;
    }
}