#include <string>
#include <vector>
#include "Room.h"
#include "Dungeon.h"
#include "PlayerCharacter.h"
#include <d3d11.h>
#include <windows.h>
#pragma once
using namespace std;

	class Overlay{
	private:
		const string filepath = "./src/images/"; // used for images in the imgui overlays
	public:
		void pop();
		virtual void render();
		bool imageHelper(string fileName, ID3D11Device* g_pd3dDevice);

		
	};
	
	class BattleOverlay : public Overlay {
	private:
		int turnOrder = 1;
	public:
		bool render(Monster* monster, Room* currentRoom, PlayerCharacter& p1, ID3D11Device* g_pd3dDevice);
		void healthBars(Monster* monster, PlayerCharacter& p1);
		void playerTurn(Monster*, PlayerCharacter& p1, bool turn);
		void monsterTurn(Monster*, PlayerCharacter& p1, bool turn);
		void setTurnOrder(int);
	};

	class MapOverlay : public Overlay {
	public:
		bool render(Dungeon& dungeon, int& currentRoomIndex, ID3D11Device* g_pd3dDevice, PlayerCharacter& p1, bool encounter);
	};

	class CharacterCreationOverlay : public Overlay{
	private:
		int numRooms = 8; // Amount of rooms to be generated in the dungeon
		char playerName[256]; // Buffer for player name input
		char playerDescription[1024]; // Buffer for player description input
		int selectedClass = 0; // 0 for none, 1 for Monk, 2 for Barbarian
		PlayerCharacter character;
		void createCharacter(int selectedClass);
	
	public:
		CharacterCreationOverlay();
		virtual ~CharacterCreationOverlay();
		bool render(bool showCharacterCreationWindow, ID3D11Device* g_pd3dDevice);
		PlayerCharacter& getCharacter();
		int getNumRooms() const;
	};
