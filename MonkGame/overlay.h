#include <string>
#include <vector>
#include "Room.h"
#include "Dungeon.h"
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

	class CharacterCreationOverlay : public Overlay {

	public:
		void render();
	};

		


	
