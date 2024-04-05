#pragma once
#include "Entity.h"
#include <string>
/* Class to add new classes with varying stats.
A Struct could 
*/ 
class CharacterClass : public Entity
{
private:
	string classDescription;
public:
	CharacterClass(string classDescription);
	virtual ~CharacterClass();

};

class Monk : public CharacterClass {
public:
	Monk();
};

