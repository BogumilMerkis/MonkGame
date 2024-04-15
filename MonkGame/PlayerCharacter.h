#pragma once
#include "Entity.h"
#include <string>
#include "CharacterClass.h"
#include <memory>
#include <iostream>
using namespace std;

class PlayerCharacter : public Entity
{
protected:
	string playerName;
	unique_ptr<CharacterClass> characterClass;
	string description;
public:
	void setDescription(char* description);
	PlayerCharacter();
	PlayerCharacter(const string& playerName, unique_ptr<CharacterClass> characterClass, const string& description);
	bool attackAction(bool) override;
	void getClassDescription();
	void setPlayerName(char* playerName);
	void setCharacterClass(unique_ptr<CharacterClass> characterClass);

	PlayerCharacter createPlayerCharacter(string playerName,string playerDescription, int classSelected);

	
};

