#pragma once

#include <vector>
#include <iostream>
#include <string>

#include "../Physics/Physics.h"
#include "../Entity/Player.h"

namespace Level {
	class Level {
	private:
		std::vector<Player> m_Players;
	public:
		Level();
		~Level();

		void AddPlayer(Player p);
		void RemovePlayer(int entityID);
		int GetPlayerLevelForID(int entityID);
		Player* GetPlayerForID(int entityID);
		std::vector<Player> GetPlayers();

		int GetFreePlayerCode();

		void Update();
		void Tick();
	};
}