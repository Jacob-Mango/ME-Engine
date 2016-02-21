#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <array>
#include <time.h>

#include "../Terrain/Terrain.h"
#include "../Rendering/Rendering.h"
#include "../Entity/Player.h"
#include "../Physics/PhysicsEngine.h"

namespace Level {
	class Level {
	private:
		std::vector<Player*> m_Players;
		std::vector<Entity*> m_Entities;

		std::vector<Terrain::Terrain*> m_Terrains;

		int m_SizeTerrain = 8;
		int m_XTerrainGen = 0;
		int m_YTerrainGen = 0;

		PhysicsEngine* m_PhysicsEngine;
	public:
		Level();
		~Level();

		void AddPlayer(Player* p);
		void RemovePlayer(unsigned int entityID);
		unsigned int GetPlayerLevelForID(unsigned int entityID);
		Player* GetPlayerForID(unsigned int entityID);
		std::vector<Player*> GetPlayers();

		void AddEntity(Entity* e);
		void RemoveEntity(unsigned int entityID);
		unsigned int GetEntityLevelForID(unsigned int entityID);
		Entity* GetEntityForID(unsigned int entityID);
		std::vector<Entity*> GetEntities();

		unsigned int GetFreeEntityCode();

		std::vector<Terrain::Terrain*> GetTerrainsToRender();
		float GetHeightUnderPlayer(float x, float z);

		PhysicsEngine* GetPhysicsEngine() {
			return m_PhysicsEngine;
		}

		void Render(Rendering::RenderModule* module, int playerID);
		void Update(bool isServer, float delta);
		void Tick(bool isServer);
	};
}