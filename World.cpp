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

void World::gameloop() {


	cout << "Welcome to Zork!\n";
	while (isRunning) {
		string playerInput;
		cout << "Insert a number\n";
		cin >> playerInput;
		cout << "Your number is " << playerInput << endl;
	}

}