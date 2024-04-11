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
	virtual string attackText() const = 0;
	virtual string getClassDescription() const = 0;
	virtual ~CharacterClass();
	virtual int getStartingHp() const = 0;
	virtual int getStartingAttack() const = 0;
};

class Monk : public CharacterClass {
public:
	Monk();
	string attackText() const override;
	string getClassDescription() const override;
	int getStartingHp() const override;
	int getStartingAttack() const override;
	virtual ~Monk();
};

class Barbarian: public CharacterClass {
public:
	Barbarian();
	string attackText() const override;
	string getClassDescription() const override;
	int getStartingHp() const override;
	int getStartingAttack() const override;
	virtual ~Barbarian();
};

