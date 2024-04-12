using namespace std;
#include <string>
#include <memory>
#include "Entity.h"
#pragma once

class Monster : public Entity{

public:
	Monster(string _name, int _hp, int _attack);
	virtual ~Monster();
	bool attackAction(bool) override = 0;
};

class Goblin : public Monster {
public:
	Goblin();
	bool attackAction(bool) override;
};

class Zombie : public Monster {
public:
	Zombie();
	bool attackAction(bool) override;
};

class Skeleton : public Monster {
public:
	Skeleton();
	bool attackAction(bool) override;
};

class GiantSpider : public Monster {
public:
	GiantSpider();
	bool attackAction(bool) override;
};

class Factory {
public:
	virtual unique_ptr<Monster> createMonster() = 0;
	virtual ~Factory() {};
};

class GoblinFactory : public Factory {
public:
	unique_ptr<Monster> createMonster() override;
};

class ZombieFactory : public Factory {
public:
	unique_ptr<Monster> createMonster() override;
};

class SkeletonFactory : public Factory {
public:
	unique_ptr<Monster> createMonster() override;
};

class GiantSpiderFactory : public Factory {
	unique_ptr<Monster> createMonster() override;
};