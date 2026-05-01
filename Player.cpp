#include "Player.h"

//Constructor
Player::Player(const std::string& name, const std::string& description, Room* location)
    : Creature(EntityType::Player, name, description, location)
{

}

//Destructor
Player::~Player()
{
}