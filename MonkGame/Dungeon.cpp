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

void Dungeon::generate() {
	// Generate room objects and fill vector
	// Generate the dungeon with the treasure room towards the end of the dungeon (at a dead end would be best). 

	rooms.push_back(new EmptyRoom());
	rooms.push_back(new EmptyRoom());
	rooms.push_back(new EmptyRoom());
	rooms.push_back(new EmptyRoom());
	rooms.push_back(new EmptyRoom());
	rooms.push_back(new EmptyRoom());
	rooms.push_back(new EmptyRoom());
	rooms.push_back(new EmptyRoom());
	rooms.push_back(new EmptyRoom());
	rooms.push_back(new EmptyRoom());
	rooms.push_back(new EmptyRoom());
	rooms.push_back(new MonsterRoom(make_unique<Goblin>()));
	rooms.push_back(new MonsterRoom(make_unique<Zombie>()));
	rooms.push_back(new MonsterRoom(make_unique<GiantSpider>()));
	rooms.push_back(new MonsterRoom(make_unique<GiantSpider>()));
	
	// Randomly choose a room to connect
	srand(time(NULL));
	// Connect rooms
	for (int i = 0; i < rooms.size() -1; ++i) {
		
		int connectIndex = rand() % rooms.size() - 1;
		
		// Ensure the room is not already connected and is not the same room
		while (connectIndex == i || find(rooms[i]->getConnectedRooms().begin(), rooms[i]->getConnectedRooms().end(), rooms[connectIndex]) != rooms[i]->getConnectedRooms().end()
		|| (abs(int(connectIndex % 3 - i % 3))) == 1 && abs(int(connectIndex / 3 - i / 3)) == 1){
			connectIndex = rand() % rooms.size();
		}
		// Connect the rooms bidirectionally
		rooms[i]->addConnectedRoom(rooms[connectIndex]);
		rooms[connectIndex]->addConnectedRoom(rooms[i]);
	}
	rooms.push_back(new TreasureRoom());
	int treasureIndex = rooms.size() - 1;
	int connectIndex = rand() % (rooms.size());
	rooms[treasureIndex]->addConnectedRoom(rooms[connectIndex]);
	rooms[connectIndex]->addConnectedRoom(rooms[treasureIndex]);

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
