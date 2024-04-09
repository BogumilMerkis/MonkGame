#include "CharacterClass.h"

CharacterClass::CharacterClass(string _name, int _hp, int _attack) : name(_name), hp(_hp), maxhp(_hp), attack(_attack)
{
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
	return "A disciplined warrior who has honed their bodies and minds into instruments of deadly combat.";
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

Barbarian::~Barbarian()
{
}
