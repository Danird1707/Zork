#include "Exit.h"
#include <string>


Exit::Exit(Room* source, Room* destination, Direction direction, std::string& description) : Entity(EntityType::Exit, DirectionToString(direction), description){
	m_source = source;
}

Exit::~Exit()
{
}

Room* Exit::getDestination() const {
	return m_destination;
}

Room* Exit::getSource() const {
	return m_source;
}

Direction Exit::getDirection() const{
	return m_direction;
}

Direction Exit::StringToDirection(const std::string& text)
{
    if (text == "north") return Direction::North;
    if (text == "south") return Direction::South;
    if (text == "east") return Direction::East;
    if (text == "west") return Direction::West;
    if (text == "up") return Direction::Up;
    if (text == "down") return Direction::Down;

    return Direction::Unknown;
}

std::string Exit::DirectionToString(Direction direction)
{
    switch (direction) {
    case Direction::North:
        return "north";
    case Direction::South:
        return "south";
    case Direction::East:
        return "east";
    case Direction::West:
        return "west";
    case Direction::Up:
        return "up";
    case Direction::Down:
        return "down";
    default:
        return "unknown";
    }
}