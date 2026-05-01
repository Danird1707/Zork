#include<iostream>
#include "World.h"
#include "Entity.h"
#include "Room.h"
#include "Exit.h"
#include "Player.h"
#include "Item.h"
#include <sstream>

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

    //Create the connections between rooms
    Exit* hallToKitchen = new Exit(hall, kitchen, Direction::North, "A passage leading north.");
    Exit* kitchenToHall = new Exit(kitchen, hall, Direction::South, "A passage leading south.");

    Exit* hallToLibrary = new Exit(hall, library, Direction::East, "A wooden door leading east.");
    Exit* libraryToHall = new Exit(library, hall, Direction::West, "A wooden door leading west.");

    entities.push_back(hallToKitchen);
    entities.push_back(kitchenToHall);
    entities.push_back(hallToLibrary);
    entities.push_back(libraryToHall);

    //Define the exits of the rooms
    hall->Add(hallToKitchen);
    kitchen->Add(kitchenToHall);
    hall->Add(hallToLibrary);
    library->Add(libraryToHall);

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

    cout << "Welcome to Mini Zork.\n";
    cout << "Type 'help' to see available commands.\n";

    look();

    while (isRunning) {
        cout << "\n> ";
        std::getline(cin, input);

        if (!input.empty()) {
            parseCommand(input);
        }
    }
}

//This function recognises the input command of the player
void World::parseCommand(const std::string& input)
{
    //Use the stringstream to get commands with format (action, entity)
    stringstream ss(input);

    std::string command;
    std::string firstArg;
    std::string connector;
    std::string secondArg;

    ss >> command;
    ss >> firstArg;
    ss >> connector;
    ss >> secondArg;

    if (command == "quit") {
        isRunning = false;
        cout << "Goodbye.\n";
    }
    else if (command == "help") {
        showHelp();
    }
    else if (command == "look") {
        look();
    }
    else if (command == "take" || command == "pickup") {
        takeItem(firstArg);
    }
    else if (command == "drop") {
        dropItem(firstArg);
    }
    else if (command == "inventory" || command == "inv") {
        showInventory();
    }
    else if (command == "go") {
        go(firstArg);
    }
    else if (
        command == "north" || command == "south" || command == "east" ||  
        command == "west" || command == "up" || command == "down") {
        go(command);
    }
    else if (command == "put") {
        if (connector == "in") {
            putItemInItem(firstArg, secondArg);
        }
        else {
            cout << "Use: put item in container\n";
        }
    }
    else {
        cout << "I don't understand that command.\n";
    }
}

//This function shows the help guide to the player
void World::showHelp() const {
    cout << "Here is the help";
}

//This function shows the actual ubication of the player and the entities in the room
void World::look() const {
    Room* currentRoom = player->getLocation();

    cout << "\n" << currentRoom->getName() << "\n";
    cout << currentRoom->getDescription() << "\n";

    cout << "\nYou see:\n";

    bool foundSomething = false;

    for (Entity* entity : currentRoom->GetContains()) {
        if (entity->getType() == EntityType::Item) {
            cout << "- " << entity->getName() << "\n";
            foundSomething = true;
        }
    }

    if (!foundSomething) {
        cout << "Nothing interesting.\n";
    }
}

void World::takeItem(const std::string& itemName)
{
    if (itemName.empty()) {
        cout << "Take what?\n";
        return;
    }

    Room* currentRoom = player->getLocation();

    Entity* entity = currentRoom->Find(itemName);

    if (entity == nullptr) {
        cout << "There is nothing here.\n";
        return;
    }

    if (entity->getType() != EntityType::Item) {
        cout << "You can't take that.\n";
        return;
    }

    currentRoom->Remove(entity);
    player->Add(entity);

    cout << "You picked up the " << entity->getName() << ".\n";
}

void World::dropItem(const std::string& itemName)
{
    if (itemName.empty()) {
        cout << "Drop what?\n";
        return;
    }

    Entity* entity = player->Find(itemName);

    if (entity == nullptr) {
        cout << "You don't have " << itemName << ".\n";
        return;
    }

    player->Remove(entity);
    player->getLocation()->Add(entity);

    cout << "You dropped the " << entity->getName() << ".\n";
}

void World::showInventory() const
{
    const std::list<Entity*>& inventory = player->GetContains();

    if (inventory.empty()) {
        cout << "Your inventory is empty.\n";
        return;
    }

    cout << "You are carrying:\n";

    for (Entity* entity : inventory) {
        if (entity->getType() == EntityType::Item) {
            cout << "- " << entity->getName() << "\n";
        }
    }
}

//Function for moving
void World::go(const std::string& directionText)
{
    Room* currentRoom = player->getLocation();
    if (directionText.empty()) {
        cout << "Go where?\n";
        return;
    }

    Direction direction = Exit::StringToDirection(directionText);

    if (direction == Direction::Unknown) {
        cout << "That is not a valid direction.\n";
        return;
    }


    for (Entity* entity : currentRoom->GetContains()) {
        if (entity->getType() == EntityType::Exit) {
            Exit* exit = static_cast<Exit*>(entity);

            if (exit->getDirection() == direction) {
                player->SetLocation(exit->getDestination());
                look();
                return;
            }
        }
    }
    cout << "You can't go that way.\n";
}

//Auxiliar function for find the the container where put an object
Entity* World::findInPlayerOrRoom(const std::string& name) const
{
    Entity* entity = player->Find(name);

    if (entity != nullptr) {
        return entity;
    }

    return player->getLocation()->Find(name);
}

void World::putItemInItem(const std::string& itemName, const std::string& containerName)
{
    if (itemName.empty() || containerName.empty()) {
        cout << "Use: put item in container\n";
        return;
    }

    Entity* item = player->Find(itemName);

    if (item == nullptr) {
        cout << "You don't have " << itemName << ".\n";
        return;
    }

    if (item->getType() != EntityType::Item) {
        cout << "You can't put that inside anything.\n";
        return;
    }

    Entity* container = findInPlayerOrRoom(containerName);

    if (container == nullptr) {
        cout << "There is no " << containerName << " here.\n";
        return;
    }

    if (container->getType() != EntityType::Item) {
        cout << "That is not a container.\n";
        return;
    }

    if (item == container) {
        cout << "You can't put something inside itself.\n";
        return;
    }

    player->Remove(item);
    container->Add(item);

    cout << "You put the " << item->getName()
        << " inside the " << container->getName() << ".\n";
}