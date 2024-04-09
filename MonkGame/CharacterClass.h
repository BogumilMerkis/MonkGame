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
	CharacterClass(string _name, int _hp, int _attack);
	virtual string attackText() const;
	virtual string getClassDescription() const;
	virtual ~CharacterClass();
};

class Monk : public CharacterClass {
public:
	Monk();
	string attackText() const;
	string getClassDescription() const;
	virtual ~Monk();
};

class Barbarian: public CharacterClass {
public:
	Barbarian();
	string attackText() const;
	string getClassDescription() const;
	virtual ~Barbarian();
};

