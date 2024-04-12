#include <string>
#include <vector>
#include "Room.h"
#include "Dungeon.h"
#include "PlayerCharacter.h"
#include <d3d11.h>
#pragma once
using namespace std;


	class Overlay{
	public:
		virtual void render(string);
	};
	
	class BattleOverlay : public Overlay {
	public:
		void render(string) override;
	};

	class MapOverlay : public Overlay {
	public:
		void render(Dungeon& dungeon, int& currentRoomIndex, ID3D11Device* g_pd3dDevice);
		void startBattle(string monsterName, ID3D11Device* g_pd3dDevice);
	};

	class CharacterCreationOverlay : public Overlay{
	private:
		int numRooms = 8; // Amount of rooms to be generated in the dungeon
		char playerName[256]; // Buffer for player name input
		char playerDescription[1024]; // Buffer for player description input
		int selectedClass = 0; // 0 for none, 1 for Monk, 2 for Barbarian
		PlayerCharacter character = PlayerCharacter("", make_unique<Monk>(), ""); // default initialiser
		void modifyCharacter();
		void pop();
	public:
		CharacterCreationOverlay();
		virtual ~CharacterCreationOverlay();
		bool render(bool);
		PlayerCharacter& getCharacter();
		int getNumRooms() const;
	};

		


	
