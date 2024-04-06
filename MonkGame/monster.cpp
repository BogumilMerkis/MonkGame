#include "monster.h"
#include "imgui.h"
#include <string>
#include <iostream>
#pragma once
using namespace std;

Monster::Monster(string _name, int _hp, int _attack) : Entity(_name, _hp, _attack) {}

Monster::~Monster() {}

Goblin::Goblin() : Monster("Goblin",10,5) {}


void Goblin::attackAction() const {
	cout << "The Goblin attacks you with it's club!";
}

Zombie::Zombie() :Monster("Zombie", 8, 3) {}

void Zombie::attackAction() const {
	cout << "The Zombie attacks you with it's rotting arms! Dealing "<< attack << " damage.";
}

Skeleton::Skeleton() :Monster("Skeleton", 13, 1) {}


void Skeleton::attackAction() const {
	cout << "The Skeleton shoots you with an arrow! Dealing " << attack << " damage.";
}

GiantSpider::GiantSpider() : Monster("Giant Spider", 6, 4) {}

void GiantSpider::attackAction() const {
	cout << "The Giant Spider bites you with it's fangs! Dealing %s damage", attack;
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
