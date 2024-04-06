#pragma once
#include "Entity.h"
#include <string>
/* Class to add new classes with varying stats.

*/ 
class CharacterClass
{
protected:
	string classDescription;
	string name;
	int hp;
	int maxhp = hp;
	int attack;
public:
	CharacterClass(string _classDescription, string _name, int _hp, int _attack);
	virtual ~CharacterClass();
};

class Monk : public CharacterClass {
public:
	Monk();
	string attackText() const;
	virtual ~Monk();
};

class Barbarian: public CharacterClass {
public:
	Barbarian();
	string attackText() const;
	virtual ~Barbarian();
};

