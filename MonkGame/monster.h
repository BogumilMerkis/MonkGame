using namespace std;
#include <string>
#include <memory>
#pragma once

class Monster {
protected:
	string name;
	int hp;
	int maxhp = hp;
	int attack;
public:
	Monster(string _name, int _hp, int _attack);
	virtual void attackAction() const = 0;
	int getHp();
	int getAttack();
	void defend();
	string getName() const;
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