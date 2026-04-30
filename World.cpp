#include<iostream>
#include "World.h"
#include "Entity.h"
#include "Room.h"
#include "Exit.h"
#include "Player.h"
#include "Item.h"
using namespace std;

World::World() {
	player = nullptr;
	isRunning = true;
    createWorld();
}

World::~World()
{
    for (Entity* entity : entities) {
        delete entity;
    }

    entities.clear();
}

void World::createWorld() {

    //Create the rooms
    Room* hall = new Room("Hall", "You are in a cold stone hall.");
    Room* kitchen = new Room("Kitchen", "You are in an old kitchen.");
    Room* library = new Room("Library", "You are in a dusty library.");

    //Put the rooms in the entity list of the world
    entities.push_back(hall);
    entities.push_back(kitchen);
    entities.push_back(library);

    //Create the objects
    Item* key = new Item("key", "A small rusty key.");
    Item* box = new Item("box", "A wooden box.");
    
    //Add items to the world's entity list
    entities.push_back(key);
    entities.push_back(box);
    //Add items to the room entity list
    hall->Add(box);
    kitchen->Add(key);

    //Create the player and assign where it starts
    player = new Player("player", "The main character.", hall);
    entities.push_back(player);

}

void World::gameloop() {


    std::string input;

    std::cout << "Welcome to Mini Zork.\n";
    std::cout << "Type 'help' to see available commands.\n";

    look();

    while (isRunning) {
        std::cout << "\n> ";
        cin >> input;

        if (!input.empty()) {
            parseCommand(input);
        }
    }
}

//This function recognises the input command of the player
void World::parseCommand(const std::string& input)
{
    if (input == "quit") {
        isRunning = false;
        std::cout << "Goodbye.\n";
    }
    else if (input == "help") {
        showHelp();
    }
    else if (input == "look") {
        look();
    }
    else {
        std::cout << "I don't understand that command.\n";
    }
}

//This function shows the help guide to the player
void World::showHelp() const {
    cout << "Here is the help";
}

//This function shows the actual ubication of the player and the entities in the room
void World::look() const {
    Room* currentRoom = player->getLocation();

    std::cout << "\n" << currentRoom->getName() << "\n";
    std::cout << currentRoom->getDescription() << "\n";

    std::cout << "\nYou see:\n";

    bool foundSomething = false;

    for (Entity* entity : currentRoom->GetContains()) {
        if (entity->getType() == EntityType::Item) {
            std::cout << "- " << entity->getName() << "\n";
            foundSomething = true;
        }
    }

    if (!foundSomething) {
        std::cout << "Nothing interesting.\n";
    }
}