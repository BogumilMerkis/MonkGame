#pragma once
#include "Entity.h"
#include <string>
/* Class to add new classes with varying stats.

*/ 
class CharacterClass
{
private:
	string classDescription;
public:
	CharacterClass(string _classDescription, string _name, int _hp, int _attack);
	virtual ~CharacterClass();

};

class Monk : public CharacterClass {
public:
	Monk();
	virtual ~Monk();
};

