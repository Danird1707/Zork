#include "Room.h"

//Constructor
Room::Room(const std::string& name, const std::string& description) : Entity(EntityType::Room, name, description) 
{
}

//Destructor
Room::~Room()
{
}