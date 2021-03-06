#include "Level.h"

namespace Level {

	Level::Level() {
		m_PhysicsEngine = new PhysicsEngine();
	}
	
	Level::~Level() {
	}

	void Level::AddPlayer(Player* p) {
		m_Players.push_back(p);
	}

	void Level::RemovePlayer(unsigned int entityID) {
		int p = GetPlayerLevelForID(entityID);
		if (p < 0) return;
		m_Players.erase(m_Players.begin() + p);
	}

	unsigned int Level::GetPlayerLevelForID(unsigned int entityID) {
		for (unsigned int i = 0; i < m_Players.size(); i++) {
			if (m_Players[i]->GetEntityID() == entityID) return i;
		}
		return -1;
	}

	Player* Level::GetPlayerForID(unsigned int entityID) {
		for (unsigned int i = 0; i < m_Players.size(); i++) {
			if (m_Players[i]->GetEntityID() == entityID) return m_Players[i];
		}
		return nullptr;
	}

	std::vector<Player*> Level::GetPlayers() {
		return m_Players;
	}

	void Level::AddEntity(Entity* e) {
		m_Entities.push_back(e);
	}

	void Level::RemoveEntity(unsigned int entityID) {
		int p = GetEntityLevelForID(entityID);
		if (p < 0) return;
		m_Entities.erase(m_Entities.begin() + p);
	}

	unsigned int Level::GetEntityLevelForID(unsigned int entityID) {
		for (unsigned int i = 0; i < m_Entities.size(); i++) {
			if (m_Entities[i]->GetEntityID() == entityID) return i;
		}
		return -1;
	}

	Entity* Level::GetEntityForID(unsigned int entityID) {
		for (unsigned int i = 0; i < m_Entities.size(); i++) {
			if (m_Entities[i]->GetEntityID() == entityID) return m_Entities[i];
		}
		return nullptr;
	}

	std::vector<Entity*> Level::GetEntities() {
		return m_Entities;
	}

	unsigned int Level::GetFreeEntityCode() {
		unsigned int x = 0;
		unsigned int lowest = 0;
		for (unsigned int i = 0; i < m_Entities.size(); i++) {
			x = m_Entities[i]->GetEntityID() + 1;
			if (x < lowest) lowest = x;
			if (x == lowest) lowest += 1;
		}
		for (unsigned int i = 0; i < m_Players.size(); i++) {
			x = m_Players[i]->GetEntityID() + 1;
			if (x < lowest) lowest = x;
			if (x == lowest) lowest += 1;
		}
		return x;
	}

	std::vector<Terrain::Terrain*> Level::GetTerrainsToRender() {
		return m_Terrains;
	}

	void Level::Render(Rendering::RenderModule* module, int playerID) {
		for (unsigned int i = 0; i < m_Players.size(); i++) {
			// if (m_Players[i]->GetEntityID() == playerID) continue;
			module->AddModelToRender(m_Players[i]->GetModelID(), m_Players[i]->GetPosition(), m_Players[i]->GetRotation(), glm::vec3(1.0f));
		}
		for (unsigned int i = 0; i < m_Entities.size(); i++) {
			module->AddModelToRender(m_Entities[i]->GetModelID(), m_Entities[i]->GetPosition(), m_Entities[i]->GetRotation(), glm::vec3(1.0f));
		}
	}

	void Level::Update(bool isServer, float delta) {
		for (unsigned int i = 0; i < m_Players.size(); i++) {
			m_Players[i]->Update(m_Terrains, delta, isServer);
		}
		for (unsigned int i = 0; i < m_Entities.size(); i++) {
			m_Entities[i]->Update(m_Terrains, delta, isServer);
		}
		if (m_XTerrainGen < m_SizeTerrain && m_YTerrainGen < m_SizeTerrain) {
			unsigned int seed = (unsigned int)(1111111111 * 1.51332512f);
			m_Terrains.push_back(new Terrain::Terrain(m_PhysicsEngine, glm::vec2(m_XTerrainGen, m_YTerrainGen), isServer, seed));

			m_XTerrainGen++;

			if (m_XTerrainGen == m_SizeTerrain) {
				m_XTerrainGen = 0;
				m_YTerrainGen++;
			}
		}
		m_PhysicsEngine->Simulate(delta);
	}

	void Level::Tick(bool isServer) {
		std::cout << "Players Online: " << std::endl;
		for (unsigned int i = 0; i < m_Players.size(); i++) {
			m_Players[i]->Tick();
			std::cout << "	" << m_Players[i]->GetEntityID() << std::endl;
		}
		std::cout << "Entities: " << std::endl;
		for (unsigned int i = 0; i < m_Entities.size(); i++) {
			m_Entities[i]->Tick();
			std::cout << "	" << m_Entities[i]->GetEntityID() << std::endl;
		}
	}
}