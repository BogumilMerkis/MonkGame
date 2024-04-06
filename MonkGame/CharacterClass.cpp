#include "CharacterClass.h"


CharacterClass::CharacterClass(string _classDescription, string _name, int _hp, int _attack) : classDescription(_classDescription), name(_name), hp(_hp), maxhp(_hp), attack(_attack)
{
}

CharacterClass::~CharacterClass()
{
}


Monk::Monk() : CharacterClass("Monk", "Disciplined warrior who has honed their bodies and minds into instruments of deadly combat.", 15, 3)
{
}



string Monk::attackText() const
{
	return " strikes with their fists dealing " + to_string(attack) + " Damage";
}


Monk::~Monk()
{
}

Barbarian::Barbarian() : CharacterClass("Barbarian", "A primal warrior, channeling their rage to become a fierce combatant.", 10, 5)
{
}


string Barbarian::attackText() const
{
	return " brutaly swings their battleaxe dealing " + to_string(attack) + " Damage";
}

Barbarian::~Barbarian()
{
}
