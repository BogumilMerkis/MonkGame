using namespace std;
#include <string>
#include <memory>
#include "Entity.h"
#pragma once

class Monster : public Entity{

public:
	Monster(string _name, int _hp, int _attack);
	virtual ~Monster();
};

class Goblin : public Monster {
public:
	Goblin();
	void attackAction() const;
};

class Zombie : public Monster {
public:
	Zombie();
	void attackAction() const;
};

class Skeleton : public Monster {
public:
	Skeleton();
	void attackAction() const;
};

class GiantSpider : public Monster {
public:
	GiantSpider();
	void attackAction() const;
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