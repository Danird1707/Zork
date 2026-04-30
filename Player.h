#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"
#include <string>

class Player : public Creature {
public:
	Player(const std::string& m_name, const std::string& m_description, Room* location);
	~Player();

private:
	std::string m_name;
	std::string m_description;
};
#endif