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

	void Level::AddEntity(Entity e) {
		e.SetEntityID(GetFreeEntityCode());
		m_Entities.push_back(e);
	}

	void Level::RemoveEntity(int entityID) {
		int p = GetEntityLevelForID(entityID);
		if (p < 0) return;
		m_Entities.erase(m_Entities.begin() + p);
	}

	int Level::GetEntityLevelForID(int entityID) {
		for (unsigned int i = 0; i < m_Entities.size(); i++) {
			if (m_Entities[i].GetEntityID() == entityID) return i;
		}
		return -1;
	}

	Entity* Level::GetEntityForID(int entityID) {
		for (unsigned int i = 0; i < m_Entities.size(); i++) {
			if (m_Entities[i].GetEntityID() == entityID) return &m_Entities[i];
		}
		return nullptr;
	}

	std::vector<Entity> Level::GetEntities() {
		return m_Entities;
	}

	int Level::GetFreeEntityCode() {
		int x = 0;
		for (unsigned int i = 0; i < m_Entities.size(); i++) {
			for (unsigned int j = 0; j =m_Players.size(); j++) {
				int y = 0;
				if (m_Players[j].GetEntityID() < m_Entities[i].GetEntityID()) y = m_Entities[i].GetEntityID() + 1;
				else y = m_Players[j].GetEntityID();
				if (y > x) x = y;
			}
		}
		return x;
	}

	std::vector<Terrain::Terrain> Level::GetTerrainsToRender() {
		return m_Terrains;
	}

	void Level::Render(Rendering::RenderModule* module, int playerID) {
		for (unsigned int i = 0; i < m_Players.size(); i++) {
			if (m_Players[i].GetEntityID() == playerID) continue;
			module->AddModelToRender(m_Players[i].GetModelID(), m_Players[i].GetPosition(), m_Players[i].GetRotation(), glm::vec3(1.0f));
		}
		for (unsigned int i = 0; i < m_Entities.size(); i++) {
			module->AddModelToRender(m_Entities[i].GetModelID(), m_Entities[i].GetPosition(), m_Entities[i].GetRotation(), glm::vec3(1.0f));
		}

		if (m_Terrains.size() == 0) {
			float h[T_VERTEXCOUNT * T_VERTEXCOUNT] = { 0 };
			m_Terrains.push_back(Terrain::Terrain(glm::vec2(0, 0), h));
		}
	}

	void Level::Update() {
		for (unsigned int i = 0; i < m_Players.size(); i++) {
			m_Players[i].Update();
		}
		for (unsigned int i = 0; i < m_Entities.size(); i++) {
			m_Entities[i].Update();
		}
	}

	void Level::Tick() {
		std::cout << "Players Online: " << std::endl;
		for (unsigned int i = 0; i < m_Players.size(); i++) {
			m_Players[i].Tick();
			std::cout << "	" << m_Players[i].GetEntityID() << std::endl;
		}
	}
}