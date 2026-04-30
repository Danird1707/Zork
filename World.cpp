#include "World.h"
#include<iostream>


using namespace std;

World::World() {
	player = nullptr;
	isRunning = true;
}

World::~World()
{
    for (Entity* entity : entities) {
        delete entity;
    }

    entities.clear();
}

void World::createWorld() {

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

//This function shows the actual ubication of the player
void World::look() const {
    cout << "You are in this room";
}