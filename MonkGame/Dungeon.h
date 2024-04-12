#pragma once
#include <vector>
#include "Room.h"


class Dungeon
{
private:
	vector<Room*> rooms;
public:
	
	Dungeon();
	~Dungeon();

	bool generate(int numRooms);
	void display() const;
	Room* getStartingRoom() const;
	vector<Room*>& getRooms();
};