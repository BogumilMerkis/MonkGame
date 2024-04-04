#include "Room.h"
#include "Dungeon.h"
#include "iostream"
#include "Monster.h"
using namespace std;

Room::Room(int number) : roomNumber(number) {}
Room::~Room() {}

void Room::addConnectedRoom(Room* room) {
	connectedRooms.push_back(room);
}
const vector<Room*>& Room::getConnectedRooms() const {
	return connectedRooms;
}

void Room::describe() const
{
}

int Room::getRoomNumber() const
{
	return roomNumber;
}


EmptyRoom::EmptyRoom(int number) : Room(number) {}


void EmptyRoom::describe() const {
	cout << "this is an empty room\n";
}

void EmptyRoom::interact(Dungeon& dungeon) {
	// logic for healing hp
}

MonsterRoom::MonsterRoom(int number, unique_ptr<Monster> _monster) : Room(number), monster(move(_monster)) {}

void MonsterRoom::describe() const {
	cout << "This room contains a  " << monster->getName() << endl;
}

void MonsterRoom::interact(Dungeon& dungeon) {
	cout << "You encounter a " << monster-> getName() << endl;
}

TreasureRoom::TreasureRoom(int number) : Room(number) {}

void TreasureRoom::describe() const {
	cout << "A large, open treasure room filled with gold and jewels.";

}

void TreasureRoom::interact(Dungeon& dungeon) {
	cout << "You open the chest gg.";
}
