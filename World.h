#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <string>


class Entity;
class Player;
class Room;

class World {

public:
	World();
	~World();

	void gameloop();

private:
	std::vector<Entity*> entities;
	bool isRunning;
	Player* player;

private:
	void createWorld();
	void parseCommand(const std::string& input);

	void takeItem(const std::string& itemName);
	void dropItem(const std::string& itemName);
	void showInventory() const;
	void look() const;
	void showHelp() const;
	void go(const std::string& directionText);
	void putItemInItem(const std::string& itemName, const std::string& containerName);
	Entity* findInPlayerOrRoom(const std::string& name) const;
	void openItem(const std::string& itemName);
	void unlockExit(const std::string& directionText, const std::string& keyName);
	void readItem(const std::string& itemName);
};

#endif


