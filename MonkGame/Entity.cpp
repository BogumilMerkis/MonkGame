#include "Entity.h"
#include <string>
using namespace std;

bool Entity::action()
{
	srand(time(NULL));
	return (rand()%1000) % 2;
}

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

void Entity::setHp(int newhp)
{
	this->hp = newhp;
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

int Entity::getMaxHp() const
{
	return maxhp;
}

bool Entity::healHpMax()
{
	hp = maxhp;
	return true;
}

string Entity::getName() const 
{
	return name;
}

