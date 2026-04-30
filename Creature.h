#ifndef CREATURE_H
#define CREATURE_H

#include "Entity.h"
#include <string>

class Room;
class Creature : public Entity {

public:

	Creature(EntityType type, const std::string& name, const std::string& description, Room* location);
	~Creature();
	Room* getLocation() const;
	void SetLocation(Room* location);

protected:
	Room* m_location;
};

#endif