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
		for (int i = 0; i < m_Players.size(); i++) {
			if (m_Players[i].GetEntityID() == entityID) return i;
		}
		return -1;
	}

	Player* Level::GetPlayerForID(int entityID) {
		for (int i = 0; i < m_Players.size(); i++) {
			if (m_Players[i].GetEntityID() == entityID) return &m_Players[i];
		}
		return nullptr;
	}

	void Level::Update() {
		for (int i = 0; i < m_Players.size(); i++) {
			m_Players[i].Update();
		}
	}

	void Level::Tick(){
		for (int i = 0; i < m_Players.size(); i++) {
			m_Players[i].Tick();
		}
	}
}