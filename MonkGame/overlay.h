#include <string>
#include <vector>
#include "Room.h"
#include "Dungeon.h"
#include "PlayerCharacter.h"
#pragma once
using namespace std;


	class Overlay{
	public:
		virtual void render();
	};

	class BattleOverlay : public Overlay {
	public:
		void render(string);
	};

	class MapOverlay : public Overlay {
	public:
		void render(Dungeon& dungeon, int currentRoomIndex);
	};

	class CharacterCreationOverlay : public Overlay{
	private:
		char playerName[256];
		char playerDescription[1024];
		int selectedClass = 0; // 0 for none, 1 for Monk, 2 for Barbarian
		PlayerCharacter character = PlayerCharacter("", make_unique<Monk>(), "");
		void modifyCharacter();
	public:
		CharacterCreationOverlay();
		virtual ~CharacterCreationOverlay();
		bool render(bool);
		PlayerCharacter& getCharacter();
	};

		


	
