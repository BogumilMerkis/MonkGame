#include "Monster.h"
#include <string>
#include <iostream>
#pragma once
using namespace std;

Monster::Monster(string _name, int _hp, int _attack) : Entity(_name, _hp, _attack) {}

Monster::~Monster() {}

string Goblin::getAttackText()
{
	return attackText;
}

string Goblin::getDefendText()
{
	return defendText;
}

string Zombie::getAttackText()
{
	return attackText;
}

string Zombie::getDefendText()
{
	return defendText;
}

string Skeleton::getAttackText()
{
	return attackText;
}

string Skeleton::getDefendText()
{
	return defendText;
}

string GiantSpider::getAttackText()
{
	return attackText;
}

string GiantSpider::getDefendText()
{
	return defendText;
}

Goblin::Goblin() : Monster("Goblin",10,2) {}

Zombie::Zombie() : Monster("Zombie", 8, 3) {}

Skeleton::Skeleton() : Monster("Skeleton", 13, 1) {}

GiantSpider::GiantSpider() : Monster("Giant Spider", 5, 5) {}


unique_ptr<Monster> GoblinFactory::createMonster() {
	return make_unique<Goblin>();
}

unique_ptr<Monster> ZombieFactory::createMonster() {
	return make_unique<Zombie>();
}

unique_ptr<Monster> SkeletonFactory::createMonster() {
	return make_unique<Skeleton>();
}

unique_ptr<Monster> GiantSpiderFactory::createMonster() {
	return make_unique<GiantSpider>();
};
