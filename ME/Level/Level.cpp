#include "Level.h"

namespace Level {

	Level::Level() {

	}
	
	Level::~Level() {

	}

	void Level::AddPlayer(Player p) {
		m_Players.push_back(p);
	}

	void Level::RemovePlayer(int entityID) {
		int p = GetPlayerLevelForID(entityID);
		if (p < 0) return;
		m_Players.erase(m_Players.begin() + p);
	}

	int Level::GetPlayerLevelForID(int entityID) {
		for (unsigned int i = 0; i < m_Players.size(); i++) {
			if (m_Players[i].GetEntityID() == entityID) return i;
		}
		return -1;
	}

	Player* Level::GetPlayerForID(int entityID) {
		for (unsigned int i = 0; i < m_Players.size(); i++) {
			if (m_Players[i].GetEntityID() == entityID) return &m_Players[i];
		}
		return nullptr;
	}

	std::vector<Player> Level::GetPlayers() {
		return m_Players;
	}

	int Level::GetFreePlayerCode() {
		int x = 0;
		for (unsigned int i = 0; i < m_Players.size(); i++) {
			x = m_Players[i].GetEntityID() + 1;
		}
		return x;
	}

	void Level::Update() {
		for (unsigned int i = 0; i < m_Players.size(); i++) {
			m_Players[i].Update();
		}
	}

	void Level::Tick(){
		std::cout << "Players Online: " << std::endl;
		for (unsigned int i = 0; i < m_Players.size(); i++) {
			m_Players[i].Tick();
			std::cout << "	" << m_Players[i].GetEntityID() << std::endl;
		}
	}
}