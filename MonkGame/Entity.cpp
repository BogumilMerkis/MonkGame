#include "Entity.h"
#include <string>
using namespace std;

Entity::Entity(string _name, int _hp, int _attack, string _description) : name(_name), hp(_hp), maxhp(_hp), attack(_attack)
{
}

Entity::Entity(string _name, int _hp, int _attack) : name(_name), hp(_hp), maxhp(_hp), attack(_attack)
{
}

Entity::Entity()
{
	this->name = "";
	this->attack = 0;
	this->maxhp = 0;
	this->hp = 0;
	this->description = "";
}

Entity::~Entity()
{
}


int Entity::getHp() const
{
	return hp;
}
int Entity::getAttack() const
{
	return attack;
}
void Entity::defend()
{
	if (hp < maxhp)
		hp += 1;
}

string Entity::getName() const 
{
	return name;
}

