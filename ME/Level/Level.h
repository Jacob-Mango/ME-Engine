#pragma once

#include <vector>
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

		void Update();
		void Tick();
	};
}