#include<iostream>
#include "World.h"
#include "Entity.h"
#include "Room.h"
#include "Exit.h"
#include "Player.h"
#include "Item.h"
#include <sstream>

using namespace std;

//Constructor
World::World() {
	player = nullptr;
	isRunning = true;
    createWorld();
}

//Destructor
World::~World()
{
    for (Entity* entity : entities) {
        delete entity;
    }

    entities.clear();
}

//The function that creates all the game world
void World::createWorld() {

    //Create the rooms
    Room* hall = new Room("Hall", "You are in a cold stone hall.");
    Room* kitchen = new Room("Kitchen", "You are in an old kitchen.");
    Room* library = new Room("Library", "You are in a dusty library.");
    Room* armory = new Room("Armory", "You are in an old armory. Broken weapons cover the walls.");
    Room* treasureRoom = new Room("Treasure Room", "A quiet room lit by golden light.");

    //Put the rooms in the entity list of the world
    entities.push_back(hall);
    entities.push_back(kitchen);
    entities.push_back(library);
    entities.push_back(armory);
    entities.push_back(treasureRoom);

    //Create the connections between rooms
    Exit* hallToKitchen = new Exit(hall, kitchen, Direction::North, "A passage leading north.");
    Exit* kitchenToHall = new Exit(kitchen, hall, Direction::South, "A passage leading south.");
    Exit* hallToLibrary = new Exit(hall, library, Direction::East, "A wooden door leading east.");
    Exit* libraryToHall = new Exit(library, hall, Direction::West, "A wooden door leading west.");
    Exit* libraryToArmory = new Exit(library, armory, Direction::North, "A narrow passage leading north.");
    Exit* armoryToLibrary = new Exit(armory, library, Direction::South, "A narrow passage leading south.");
    Exit* armoryToTreasure = new Exit(armory, treasureRoom, Direction::East, "A heavy locked door leading east.", true, "special_key");
    Exit* treasureToArmory = new Exit(treasureRoom, armory, Direction::West, "A heavy door leading west.");

    //Add the exits to the entity list
    entities.push_back(hallToKitchen);
    entities.push_back(kitchenToHall);
    entities.push_back(hallToLibrary);
    entities.push_back(libraryToHall);
    entities.push_back(libraryToArmory);
    entities.push_back(armoryToLibrary);
    entities.push_back(armoryToTreasure);
    entities.push_back(treasureToArmory);

    //Define the exits of the rooms
    hall->Add(hallToKitchen);
    kitchen->Add(kitchenToHall);
    hall->Add(hallToLibrary);
    library->Add(libraryToHall);
    library->Add(libraryToArmory);
    armory->Add(armoryToLibrary);
    armory->Add(armoryToTreasure);
    treasureRoom->Add(treasureToArmory);

    //Create the items
    Item* key = new Item("key", "A small rusty key.");
    Item* box = new Item("box", "A wooden box.", true);
    Item* specialKey = new Item("special_key", "A silver key with a star-shaped head.");
    Item* letter = new Item("letter", "A sealed letter rests on a small stone table.", true);
    Item* note = new Item("note", "A folded note with hurried handwriting.");
    Item* lever = new Item("lever", "A small iron lever.");
    Item* lockbox = new Item("lockbox", "A locked metal box.", true);

    //Add items to the world's entity list
    entities.push_back(key);
    entities.push_back(box);
    entities.push_back(specialKey);
    entities.push_back(letter);
    entities.push_back(note);
    entities.push_back(lever);
    entities.push_back(lockbox);

    //Add items to the room entity list
    hall->Add(box);
    kitchen->Add(key);
    treasureRoom->Add(letter);
    box->Add(note);
    kitchen->Add(lever);
    library->Add(lockbox);
    lockbox->Add(specialKey);
    //Create the player and assign where it starts
    player = new Player("player", "The main character.", hall);
    entities.push_back(player);

}

//Function that keeps the game running
void World::gameloop() {


    std::string input;

    cout << "Welcome to Mini Zork.\n";
    cout << "Type 'help' to see available commands.\n";

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
    //Use the stringstream to get commands with format (command firstArgument connector secondArgument) exemple: "put key in box"
    stringstream ss(input);

    std::string command;
    std::string firstArg;
    std::string connector;
    std::string secondArg;

    ss >> command;
    ss >> firstArg;
    ss >> connector;
    ss >> secondArg;

    //Recieves the command from the player and calls the function to execute the action
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
    else if (command == "open") {
        openItem(firstArg);
    }
    else if (command == "unlock") {
        if (connector == "with") {
            unlockExit(firstArg, secondArg);
        }
        else {
            cout << "Use: unlock direction with key\n";
        }
    }
    else if (command == "read") {
        readItem(firstArg);
    }
    else if (command == "use") {
        if (connector == "on") {
            useItemOn(firstArg, secondArg);
        }
        else {
            cout << "Use: use item on target\n";
        }
    }
    else {
        cout << "I don't understand that command.\n";
    }
}

//This function shows the help guide to the player
void World::showHelp() const {
    cout << "\nAvailable commands:\n";
    cout << "  look                         - Look around the current room.\n";
    cout << "  go north/south/east/west     - Move to another room.\n";
    cout << "  north/south/east/west        - Shortcut for movement.\n";
    cout << "  take item                    - Pick up an item.\n";
    cout << "  drop item                    - Drop an item from your inventory.\n";
    cout << "  inventory or inv             - Show your inventory.\n";
    cout << "  open item                    - Open a container.\n";
    cout << "  read item                    - Read a note or letter.\n";
    cout << "  use item on target           - Use an item on something.\n";
    cout << "  unlock direction with key    - Unlock a locked exit.\n";
    cout << "  quit                         - Exit the game.\n";


    cout << "\nExample commands:\n";
    cout << "  open box\n";
    cout << "  take lever\n";
    cout << "  use lever on lockbox\n";
    cout << "  unlock east with special_key\n";
    cout << "  go east\n";
    cout << "  read letter\n";
}

//This function shows the actual ubication of the player and the entities in the room
void World::look() const {
    if (player == nullptr) {
        cout << "ERROR: player is null.\n";
        return;
    }

    Room* currentRoom = player->getLocation();

    if (currentRoom == nullptr) {
        cout << "ERROR: player location is null.\n";
        return;
    }

    cout << "\n" << currentRoom->getName() << "\n";
    cout << currentRoom->getDescription() << "\n";

    cout << "\nExits:\n";

    bool foundExit = false;

    for (Entity* entity : currentRoom->GetContains()) {
        if (entity->getType() == EntityType::Exit) {
            Exit* exit = static_cast<Exit*>(entity);
            cout << "- " << Exit::DirectionToString(exit->getDirection()) << "\n";
            foundExit = true;
        }
    }

    if (!foundExit) {
        cout << "- none\n";
    }

    cout << "\nYou see:\n";

    bool foundSomething = false;

    for (Entity* entity : currentRoom->GetContains()) {
        if (entity->getType() == EntityType::Item) {
            cout << "- " << entity->getName() << ": "
                << entity->getDescription() << "\n";

            Item* item = static_cast<Item*>(entity);

            if (item->CanOpen()) {
                if (item->IsOpen()) {
                    if (item->GetContains().empty()) {
                        cout << "  It is open and empty.\n";
                    }
                    else {
                        cout << "  It contains:\n";

                        for (Entity* contained : item->GetContains()) {
                            cout << "  - " << contained->getName() << "\n";
                        }
                    }
                }
            }

            foundSomething = true;
        }
    }

    if (!foundSomething) {
        cout << "- nothing interesting\n";
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

//Function to drop an item
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

//Shows the inventory
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

                if (exit->isLocked()) {
                    cout << "The door is locked.\n";
                    return;
                }
                player->SetLocation(exit->getDestination());
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

//Function to put an item inside another.
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

//Function for open Items and reveal what is inside
void World::openItem(const std::string& itemName)
{
    if (itemName.empty()) {
        cout << "Open what?\n";
        return;
    }

    Entity* entity = player->Find(itemName);

    if (entity == nullptr) {
        entity = player->getLocation()->Find(itemName);
    }

    if (entity == nullptr) {
        cout << "There is no " << itemName << " here.\n";
        return;
    }

    if (entity->getType() != EntityType::Item) {
        cout << "You can't open that.\n";
        return;
    }

    Item* item = static_cast<Item*>(entity);

    if (!item->CanOpen()) {
        cout << "You can't open the " << item->getName() << ".\n";
        return;
    }

    if (item->IsOpen()) {
        cout << "The " << item->getName() << " is already open.\n";
        return;
    }

    if (item->getName() == "lockbox") {
        cout << "The lockbox is sealed shut. You need something to force it open.\n";
        return;
    }
    item->Open();

    cout << "You open the " << item->getName() << ".\n";

    if (item->GetContains().empty()) {
        cout << "It is empty.\n";
        return;
    }

    cout << "Something falls out:\n";

    while (!item->GetContains().empty()) {
        Entity* contained = item->GetContains().front();

        item->Remove(contained);
        player->getLocation()->Add(contained);

        cout << "- " << contained->getName() << "\n";
    }
}

//Function that unlocks key closed doors
void World::unlockExit(const std::string& directionText, const std::string& keyName)
{
    Direction direction = Exit::StringToDirection(directionText);

    if (direction == Direction::Unknown) {
        cout << "That is not a valid direction.\n";
        return;
    }

    Entity* key = player->Find(keyName);

    if (key == nullptr) {
        cout << "You don't have the " << keyName << ".\n";
        return;
    }

    Room* currentRoom = player->getLocation();

    for (Entity* entity : currentRoom->GetContains()) {
        if (entity->getType() == EntityType::Exit) {
            Exit* exit = static_cast<Exit*>(entity);

            if (exit->getDirection() == direction) {
                if (exit->unlockWith(key)) {
                    cout << "You unlock the door.\n";
                }
                else {
                    cout << "The key does not fit.\n";
                }

                return;
            }
        }
    }

    cout << "There is no door that way.\n";
}

//Function for read notes in items
void World::readItem(const std::string& itemName)
{
    if (itemName.empty()) {
        cout << "Read what?\n";
        return;
    }

    Entity* entity = player->Find(itemName);

    if (entity == nullptr) {
        entity = player->getLocation()->Find(itemName);
    }

    if (entity == nullptr) {
        cout << "You don't see any " << itemName << " here.\n";
        return;
    }

    if (entity->getName() == "note") {
        cout << "The note says:\n";
        cout << "\"Find the special key. Only it can open the treasure room.\"\n";
        return;
    }

    if (entity->getName() == "letter") {
        cout << "The letter says:\n";
        cout << "\"Congratulations, adventurer. You have completed the game.\"\n";
        cout << "\nYou win!\n";
        isRunning = false;
        return;
    }

    cout << "There is nothing useful written on it.\n";
}

//Function to use items with other items.
void World::useItemOn(const std::string& itemName, const std::string& targetName)
{
    if (itemName.empty() || targetName.empty()) {
        cout << "Use: use item on target\n";
        return;
    }

    Entity* item = player->Find(itemName);

    if (item == nullptr) {
        cout << "You don't have the " << itemName << ".\n";
        return;
    }

    Entity* target = player->Find(targetName);

    if (target == nullptr) {
        target = player->getLocation()->Find(targetName);
    }

    if (target == nullptr) {
        cout << "There is no " << targetName << " here.\n";
        return;
    }

    if (itemName == "lever" && targetName == "lockbox") {
        if (target->getType() != EntityType::Item) {
            cout << "That won't work.\n";
            return;
        }

        Item* lockbox = static_cast<Item*>(target);

        if (lockbox->IsOpen()) {
            cout << "The lockbox is already open.\n";
            return;
        }

        lockbox->Open();

        cout << "You force the lockbox open with the lever.\n";

        if (lockbox->GetContains().empty()) {
            cout << "It is empty.\n";
            return;
        }

        cout << "Something falls out:\n";

        while (!lockbox->GetContains().empty()) {
            Entity* contained = lockbox->GetContains().front();

            lockbox->Remove(contained);
            player->getLocation()->Add(contained);

            cout << "- " << contained->getName() << "\n";
        }

        return;
    }

    cout << "Nothing happens.\n";
}