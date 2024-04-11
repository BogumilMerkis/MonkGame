#include "CharacterClass.h"



CharacterClass::CharacterClass(string _name, int _hp, int _attack)
{
	this->name = _name;
	this->hp = _hp;
	this->maxhp = _hp;
	this->attack = _attack;
}

string CharacterClass::attackText() const
{
	return " attacks";
}

string CharacterClass::getClassDescription() const
{
	return "Base class";
}

CharacterClass::~CharacterClass()
{
}

Monk::Monk() : CharacterClass("Monk", 15, 3)
{
}

string Monk::attackText() const
{
	return " strikes with their fists dealing " + to_string(attack) + " Damage";
}

string Monk::getClassDescription() const
{
	return "A disciplined warrior who has honed their body and minds into instruments of deadly combat.";
}

int Monk::getStartingHp() const
{
	return 15;
}

int Monk::getStartingAttack() const
{
	return 3;
}

Monk::~Monk()
{
}

Barbarian::Barbarian() : CharacterClass("Barbarian", 10, 5)
{
}

string Barbarian::attackText() const
{
	return " brutaly swings their battleaxe dealing " + to_string(attack) + " Damage";
}

string Barbarian::getClassDescription() const
{
	return "A primal warrior, channeling their rage to become a fierce combatant.";
}

int Barbarian::getStartingHp() const
{
	return 10;
}

int Barbarian::getStartingAttack() const
{
	return 5;
}

Barbarian::~Barbarian()
{
}
