#include "PlayerCharacter.h"
using namespace std;

void PlayerCharacter::setDescription(string description) const
{
}

PlayerCharacter::PlayerCharacter(string _name, int _hp, int _attack, unique_ptr<CharacterClass> _characterClass) :
	Entity(_name, _hp, _attack), characterClass(move(_characterClass)) {}


void PlayerCharacter::attackAction() const
{
	cout << getName() << characterClass->attackText() << endl;
}

void PlayerCharacter::getClassDescription() const
{
	cout << characterClass->getClassDescription() << endl;
}

