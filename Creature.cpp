#include "Creature.h"
#include <string>

Creature::Creature(EntityType type, const std::string& name, const std::string& description, Room* location) 
	: Entity(EntityType::Creature, name, description) 
{
	m_location = location;
}

Creature::~Creature() {

}

Room* Creature::getLocation() const {
	return m_location;
}

void Creature::SetLocation(Room* location) {
	m_location = location;
}