#ifndef EXIT_H
#define EXIT_H

#include "Entity.h"
#include <string>
class Room;

enum class Direction {
    North,
    South,
    East,
    West,
    Up,
    Down,
    Unknown
};

class Exit: public Entity {
public:
    Exit(Room* source, Room* destination, Direction direction, const std::string& description, bool locked = false, const std::string& requiredKeyName = "");
    ~Exit();
    Room* getSource() const;
    Room* getDestination() const;
    Direction getDirection() const;
    bool isLocked() const;
    bool unlockWith(Entity* key);

    static Direction StringToDirection(const std::string& text);
    static std::string DirectionToString(Direction direction);

private:
	Room* m_source;
	Room* m_destination;
    Direction m_direction;
    std::string m_description;
    bool m_locked;
    std::string m_requiredKeyName;
};


#endif