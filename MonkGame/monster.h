using namespace std;
#include <string>
#include <memory>
#include "Entity.h"
#pragma once

class Monster : public Entity{
public:
	Monster();
	Monster(string _name, int _hp, int _attack);
	virtual ~Monster();
	virtual string getAttackText() = 0;
	virtual string getDefendText() = 0;
};

class Goblin : public Monster {
private:
	const string attackText = "The Goblin slashes you with it's dagger! Dealing " + to_string(attack) + " damage";
	const string defendText = "The Goblin stays back and decides what to do next, regaining 1hp";
public:
	string getAttackText() override;
	string getDefendText() override;
	Goblin();
	virtual ~Goblin();
};

class Zombie : public Monster {
private:
	const string attackText = "The Zombie attacks you with it's rotting arms! Dealing " + to_string(attack) + " damage";
	const string defendText = "The Zombie stumbles and waits, regaining 1hp";
public:
	string getAttackText() override;
	string getDefendText() override;
	Zombie();
	virtual ~Zombie();
};

class Skeleton : public Monster {
private:
	const string attackText = "The Skeleton shoots you with an arrow! Dealing " + to_string(attack) + " damage";
	const string defendText = "The Skeleton holds back, regaining 1hp";
public:
	string getAttackText() override;
	string getDefendText() override;
	Skeleton();
	virtual ~Skeleton();
};

class GiantSpider : public Monster {
private:
	const string attackText = "The Giant Spider bites you with it's fangs! Dealing " + to_string(attack) + " damage";
	const string defendText = "The Giant Spider waits and spins a web, regaining 1hp";
public:
	string getAttackText() override;
	string getDefendText() override;
	GiantSpider();
	virtual ~GiantSpider();
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
public:
	unique_ptr<Monster> createMonster() override;
};