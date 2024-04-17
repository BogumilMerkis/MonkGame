#include <vector>
#include "Monster.h"
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

	virtual string describe() const;

	virtual void interact(Dungeon& dungeon) = 0;

	int getRoomNumber() const;
};

class EmptyRoom : public Room {
public:
	EmptyRoom();

	string describe() const override;
	void interact(Dungeon& dungeon) override;
};

class MonsterRoom : public Room {
private:
	unique_ptr<Monster> monster;
public:
	MonsterRoom(unique_ptr<Monster> _monster);
	Monster* getMonster() const;
	string describe() const override;
	void interact(Dungeon& dungeon) override;
	void setDescription(string descrpition);
};

class TreasureRoom : public Room {
public:
	TreasureRoom();

	string describe() const override;
	void interact(Dungeon& dungeon) override;
};