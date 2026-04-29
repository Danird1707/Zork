#include "Room.h"

Room::Room(const std::string& name, const std::string& description) : Entity(EntityType::Room, name, description) 
{
}

Room::~Room()
{
}