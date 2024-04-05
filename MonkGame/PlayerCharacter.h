#pragma once
#include "Entity.h"
#include <string>
#include "CharacterClass.h"

class PlayerCharacter : public Entity , public CharacterClass
{
private:
	string description;
};

