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
	string attackText;
public:
	CharacterClass(string _name, int _hp, int _attack);
	virtual string getClassDescription() const = 0;
	virtual ~CharacterClass();
	virtual int getStartingHp() const = 0;
	virtual int getStartingAttack() const = 0;
	virtual string getAttackText() const = 0;
	virtual string getDefendText() const = 0;
};

class Monk : public CharacterClass {
private:
	string attackText = " strikes with their fists, dealing " + to_string(attack) + " damage";
	string defendText = " stays back deciding what to do next, recovering 1 HP.";
public:
	Monk();
	string getDefendText() const override;
	string getAttackText() const override;
	string getClassDescription() const override;
	int getStartingHp() const override;
	int getStartingAttack() const override;
	virtual ~Monk();
};

class Barbarian: public CharacterClass {
private:
	string attackText = " brutaly swings their battleaxe, dealing " + to_string(attack) + " damage!";
	string defendText = " stays back, recovering 1 HP.";
public:
	Barbarian();
	string getDefendText() const override;
	string getAttackText()  const override;
	string getClassDescription() const override;
	int getStartingHp() const override;
	int getStartingAttack() const override;
	virtual ~Barbarian();
};

