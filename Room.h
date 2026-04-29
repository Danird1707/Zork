#ifndef ROOM_H
#define ROOM_H

#include "Entity.h"

class Room : public Entity {
public:
	Room(const std::string& name, const std::string& description);
	~Room();
};
#endif
