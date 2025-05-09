#include "Room.h"
#include "Dungeon.h"
#include "iostream"
#include "Monster.h"
using namespace std;

int Room::currentRoomNumber = 0;
Room::Room() {
	roomNumber = ++currentRoomNumber;
}
Room::~Room() {}

void Room::addConnectedRoom(Room* room) {
	if (room != nullptr) {
		connectedRooms.push_back(room);
	}
	
}
const vector<Room*>& Room::getConnectedRooms() const {
	return connectedRooms;
}

string Room::describe() const
{
	return "Default room describer";
}

int Room::getRoomNumber() const
{
	return roomNumber;
}


EmptyRoom::EmptyRoom() : Room() {}


string EmptyRoom::describe() const {
	return "This is an empty room";
}

void EmptyRoom::interact(Dungeon& dungeon) {
	// logic for healing hp
}

MonsterRoom::MonsterRoom(unique_ptr<Monster> _monster) : Room(), monster(move(_monster)) {}

Monster* MonsterRoom::getMonster() const
{
	return monster.get();
}

string MonsterRoom::describe() const {
	return "This room contains a " + monster->getName();
}

void MonsterRoom::interact(Dungeon& dungeon) {
	cout << "You encounter a " << monster-> getName() << endl;
}

TreasureRoom::TreasureRoom() : Room() {}

string TreasureRoom::describe() const {
	return  "A large, open treasure room, filled with gold and jewels.";

}

void TreasureRoom::interact(Dungeon& dungeon) {
	cout << "You open the chest gg.";
}
