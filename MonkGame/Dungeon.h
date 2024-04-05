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

	void generate();
	void display() const;
	Room* getStartingRoom() const;
	vector<Room*>& getRooms();
};