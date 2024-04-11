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
	string description;
public:
	Entity(string _name, int _hp, int _attack, string _description);
	Entity(string _name, int _hp, int _attack);
	Entity();
	virtual ~Entity();
	virtual void attackAction() const = 0;
	int getHp() const;
	int getAttack() const;
	void defend();
	string getName() const;
};

