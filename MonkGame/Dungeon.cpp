#include "Dungeon.h"
#include <iostream>
#include <cstdlib>
#include "Room.h"
#include "monster.h"
#include "time.h"
using namespace std;

Dungeon::Dungeon(){}
Dungeon::~Dungeon() {
	for (Room* room : rooms) {
		delete room;
	}
}

bool Dungeon::generate(int numRooms) {
	// Generate room objects and fill vector
	// Generate the dungeon with the treasure room towards the end of the dungeon (at a dead end would be best). 

	rooms.push_back(new EmptyRoom());
	Room* lastRoom = rooms[0];

	// Randomly choose a room to connect
	srand(time(NULL));
	cout << rand();
	// Connect rooms
	for (int i = 0; i <= numRooms - 3; i++) {
		Room* newRoom = nullptr;
		
		int roomType = rand() % 4;
		switch (roomType) {
			case 0:
			case 1:
			case 2:
				newRoom = new EmptyRoom();
				break;
			case 3:
				int monsterType = rand() % 4;
				switch (monsterType) {
					case 0:
						newRoom = new MonsterRoom(make_unique<GoblinFactory>()->createMonster());
						break;
					case 1:
						newRoom = new MonsterRoom(make_unique<ZombieFactory>()->createMonster());
						break;
					case 2:
						newRoom = new MonsterRoom(make_unique<Skeleton>());
						break;
					case 3: 
						newRoom = new MonsterRoom(make_unique<GiantSpider>());
						break;
				}
				break;	
		}

		Room* connectedRoom = nullptr;
		while (!connectedRoom || connectedRoom->getConnectedRooms().size() > 3) {
			connectedRoom = rooms[rand() % rooms.size()];
		}
		
		newRoom->addConnectedRoom(connectedRoom);
		connectedRoom->addConnectedRoom(newRoom);
		rooms.push_back(newRoom);
		lastRoom = newRoom;
	}
	Room* tRoom = new TreasureRoom();
	tRoom->addConnectedRoom(lastRoom);
	lastRoom->addConnectedRoom(tRoom);
	rooms.push_back(tRoom);
	return true;

}

void Dungeon::display() const {
	cout << "Dungeon Layout:\n";
	for (int i = 0; i < rooms.size(); ++i) {
		cout << "Room " << i + 1 << ": ";
		rooms[i]->describe();
		const vector<Room*>& connectedRooms = rooms[i]->getConnectedRooms();
		cout << "Connected Rooms: ";
		for (int j = 0; j < connectedRooms.size(); ++j) {
			if (j != 0) {
				cout << ", ";
			}
			// Get the index of the connected room
			int connectedIndex = find(rooms.begin(), rooms.end(), connectedRooms[j]) - rooms.begin();
			cout << "Room " << connectedIndex + 1;
		}
		cout << endl;
	}
}

Room* Dungeon::getStartingRoom() const {
	return rooms[0]; // Starting room is always the first room in the vector
}

vector<Room*>& Dungeon::getRooms()
{
	return rooms;
}
