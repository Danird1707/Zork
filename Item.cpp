#include "Item.h"

Item::Item(const std::string& name, const std::string& description)
    : Entity(EntityType::Item, name, description)
{

}

Item::~Item()
{
}