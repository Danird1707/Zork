#ifndef WORLD_H
#define WORLD_H

#include <vector>

class Entity;
class Player;


class World {

public:
	World();
	~World();

	void gameloop();

private:
	std::vector<Entity*> entities;
	bool isRunning;
	Player* player;
};

#endif


