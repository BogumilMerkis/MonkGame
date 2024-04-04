#include <vector>
#include "monster.h"
#pragma once
using namespace std;

class Dungeon;

class Room {
protected:
	vector<Room*> connectedRooms;
	int roomNumber;
	static int currentRoomNumber;
public:
	Room();
	virtual ~Room();

	void addConnectedRoom(Room* room);

	const vector<Room*>& getConnectedRooms() const;

	virtual void describe() const;

	virtual void interact(Dungeon& dungeon) = 0;

	int getRoomNumber() const;
};

class EmptyRoom : public Room {
public:
	EmptyRoom();

	void describe() const override;
	void interact(Dungeon& dungeon) override;
};

class MonsterRoom : public Room {
private:
	unique_ptr<Monster> monster;
public:
	MonsterRoom(unique_ptr<Monster> _monster);

	void describe() const override;
	void interact(Dungeon& dungeon) override;
};

class TreasureRoom : public Room {
public:
	TreasureRoom();

	void describe() const override;
	void interact(Dungeon& dungeon) override;
};