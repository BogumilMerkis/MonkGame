#include "monster.h"
#include "imgui.h"
#include <string>
#include <iostream>
#pragma once
using namespace std;

Monster::Monster(string _name, int _hp, int _attack) : Entity(_name, _hp, _attack) {}

Monster::~Monster() {}

Goblin::Goblin() : Monster("Goblin",10,5) {}


bool Goblin::attackAction(bool)  {
	cout << "The Goblin attacks you with it's club!";
	return true;
}

Zombie::Zombie() :Monster("Zombie", 8, 3) {}

bool Zombie::attackAction(bool) {
	cout << "The Zombie attacks you with it's rotting arms! Dealing "<< attack << " damage.";
	return true;
}

Skeleton::Skeleton() :Monster("Skeleton", 13, 1) {}


bool Skeleton::attackAction(bool)  {
	cout << "The Skeleton shoots you with an arrow! Dealing " << attack << " damage.";
	return true;
}

GiantSpider::GiantSpider() : Monster("Giant Spider", 6, 4) {}

bool GiantSpider::attackAction(bool) {
	cout << "The Giant Spider bites you with it's fangs! Dealing %s damage", attack;
	return true;
}

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
}
