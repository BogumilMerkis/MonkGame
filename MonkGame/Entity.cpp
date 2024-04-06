#include "Entity.h"
#include <string>
using namespace std;

Entity::Entity(string _name, int _hp, int _attack) : name(_name), hp(_hp), maxhp(_hp), attack(_attack)
{
}


Entity::~Entity()
{
}

int Entity::getHp()
{
	return hp;
}
int Entity::getAttack()
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

