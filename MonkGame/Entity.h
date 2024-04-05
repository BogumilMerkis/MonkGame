#include <string>
#pragma once
using namespace std;

class Entity
{
protected:
	string name;
	int hp;
	int maxhp = hp;
	int attack;
public:
	Entity(string _name, int _hp, int _attack);
	virtual ~Entity();
	virtual void attackAction() const = 0;
	int getHp();
	int getAttack();
	void defend();
	string getName() const;
};

