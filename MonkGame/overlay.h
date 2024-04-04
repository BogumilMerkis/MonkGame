#include <string>
#include <vector>
#include "Room.h"
#include "Dungeon.h"
#pragma once
using namespace std;


	class overlay{
	
	public:
		virtual void render();
	
	};

	class BattleOverlay : public overlay {
	public:
		void render(string);
	};

	class MapOverlay : public overlay {
	public:
		void render(Dungeon& dungeon, int currentRoomIndex);
	};

		


	
