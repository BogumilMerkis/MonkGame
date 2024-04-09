#pragma once
#include "Entity.h"
#include <string>
#include "CharacterClass.h"
#include <memory>
#include <iostream>
using namespace std;

class PlayerCharacter : public Entity
{
private:
	unique_ptr<CharacterClass> characterClass;
	const string description;
public:
	PlayerCharacter(string _name, int _hp, int _attack, unique_ptr<CharacterClass> _characterClass);
	void setDescription(string description) const;
	void attackAction() const override;
	void getClassDescription() const;
	
};

