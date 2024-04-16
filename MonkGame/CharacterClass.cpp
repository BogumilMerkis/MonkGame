#include "CharacterClass.h"



CharacterClass::CharacterClass(string _name, int _hp, int _attack)
{
	this->name = _name;
	this->hp = _hp;
	this->maxhp = _hp;
	this->attack = _attack;
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

string Monk::getDefendText() const
{
	return defendText;
}

string Monk::getAttackText() const
{
	return attackText;
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

string Barbarian::getDefendText() const
{
	return defendText;
}

string Barbarian::getAttackText() const
{
	return attackText;
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
