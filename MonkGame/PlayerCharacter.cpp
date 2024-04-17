#include "PlayerCharacter.h"
#include <stdexcept>
using namespace std;


PlayerCharacter::PlayerCharacter(const string& playerName, unique_ptr<CharacterClass> characterClass, const string& description) :
    Entity(playerName, characterClass->getStartingHp(), characterClass->getStartingAttack()),
    characterClass(move(characterClass)),
    playerName(playerName)
{
}

PlayerCharacter::PlayerCharacter() : Entity("", 1, 0)
{
}

string PlayerCharacter::getClassDescription()
{
    return characterClass->getClassDescription();
}

string PlayerCharacter::getAttackText()
{
    return characterClass->getAttackText();
}

string PlayerCharacter::getDefendText()
{
    return characterClass->getDefendText();
}

void PlayerCharacter::setPlayerName(char* playerName)
{
    this->name = playerName;
}

void PlayerCharacter::setDescription(char* description)
{
    this->description = description;
}

void PlayerCharacter::setCharacterClass(unique_ptr<CharacterClass> characterClass)
{
    this->characterClass = move(characterClass);
}

PlayerCharacter PlayerCharacter::createPlayerCharacter(string playerName, string playerDescription, int classSelected) {

    unique_ptr<CharacterClass> chosenClass;
    switch (classSelected) {
    case 1: {
        chosenClass = make_unique<Monk>();
        break;
    }
    case 2: {
        chosenClass = make_unique<Barbarian>();
        break;
    }
    default: {
        // Handle invalid class selection
        throw invalid_argument("Invalid class selected.");
    }
    }
    
    if (!chosenClass) {
        // Handle error if chosenClass is nullptr
        throw runtime_error("Failed to initialize character class.");
    }
    

    return PlayerCharacter(move(playerName), move(chosenClass), move(playerDescription));
}
