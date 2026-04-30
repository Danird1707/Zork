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
    Exit(Room* source, Room* destination, Direction direction, std::string& description);
    ~Exit();
    Room* getSource() const;
    Room* getDestination() const;
    Direction getDirection() const;

    static Direction StringToDirection(const std::string& text);
    static std::string DirectionToString(Direction direction);

private:
	Room* m_source;
	Room* m_destination;
    Direction m_direction;
    std::string m_description;
};

#endif