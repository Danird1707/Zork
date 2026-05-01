#include "Exit.h"
#include <string>


//Constructor
Exit::Exit(Room* source, Room* destination, Direction direction, const std::string& description, bool locked, const std::string& requiredKeyName)
    : Entity(EntityType::Exit, DirectionToString(direction), description){
	m_source = source;
    m_destination = destination;
    m_direction = direction;
    m_description = description;
    m_locked = locked;
    m_requiredKeyName = requiredKeyName;
}

//Destructor
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

//Converts the input directions in direction enum class object
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

//Converts the enum class direction object to a string
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

//Checks if the exit door is open or not
bool Exit::isLocked() const
{
    return m_locked;
}

//Shows if the exit needs a key to open
bool Exit::unlockWith(Entity* key)
{
    if (!m_locked) {
        return true;
    }

    if (key == nullptr) {
        return false;
    }

    if (key->getName() == m_requiredKeyName) {
        m_locked = false;
        return true;
    }

    return false;
}