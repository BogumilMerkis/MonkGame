#include <string>
#include <vector>
#include "Room.h"
#include "Dungeon.h"
#include "PlayerCharacter.h"
#include <d3d11.h>
#pragma once
using namespace std;


	class Overlay{
	private:
		const string filepath = "./src/images/";
	public:
		virtual void render();
		bool entityImage(string monsterName, ID3D11Device* g_pd3dDevice);
		
	};
	
	class BattleOverlay : public Overlay {
	public:
		void render(Monster* monster, Room* currentRoom, PlayerCharacter& p1);
	};

	class MapOverlay : public Overlay {
	public:
		bool render(Dungeon& dungeon, int& currentRoomIndex, ID3D11Device* g_pd3dDevice, PlayerCharacter& p1);
	};

	class CharacterCreationOverlay : public Overlay{
	private:
		int numRooms = 8; // Amount of rooms to be generated in the dungeon
		char playerName[256]; // Buffer for player name input
		char playerDescription[1024]; // Buffer for player description input
		int selectedClass = 0; // 0 for none, 1 for Monk, 2 for Barbarian
		PlayerCharacter character;
		void createCharacter(int selectedClass);
		void pop();
	public:
		CharacterCreationOverlay();
		virtual ~CharacterCreationOverlay();
		bool render(bool showCharacterCreationWindow, ID3D11Device* g_pd3dDevice);
		PlayerCharacter& getCharacter();
		int getNumRooms() const;
	};

		


	
