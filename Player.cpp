#include "Player.h"

Player::Player(const std::string& name, const std::string& description, Room* location)
    : Creature(EntityType::Player, name, description, location)
{

}

Player::~Player()
{
}