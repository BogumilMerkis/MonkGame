#include <string>
#include <cstdlib>
#include "time.h"
#pragma once
using namespace std;

class Entity
{
protected:
	string name;
	int hp;
	int maxhp = hp;
	int attack;
	string description;
public:
	Entity(string _name, int _hp, int _attack, string _description);
	Entity(string _name, int _hp, int _attack);
	Entity();
	void setHp(int newhp);
	virtual ~Entity();
	bool action();
	int getHp() const;
	int getAttack() const;
	void defend();
	int getMaxHp() const;
	bool healHpMax();
	string getName() const;
};

