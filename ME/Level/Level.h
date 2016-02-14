#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <array>

#include "../Rendering/Rendering.h"
#include "../Physics/Physics.h"
#include "../Entity/Player.h"

#define MAPSIZE 4

namespace Level {
	class Level {
	private:
		std::vector<Player*> m_Players;
		std::vector<Entity*> m_Entities;

		std::vector<Terrain::Terrain*> m_Terrains;
	public:
		Level();
		~Level();

		void AddPlayer(Player* p);
		void RemovePlayer(int entityID);
		int GetPlayerLevelForID(int entityID);
		Player* GetPlayerForID(int entityID);
		std::vector<Player*> GetPlayers();

		void AddEntity(Entity* e);
		void RemoveEntity(int entityID);
		int GetEntityLevelForID(int entityID);
		Entity* GetEntityForID(int entityID);
		std::vector<Entity*> GetEntities();

		int GetFreeEntityCode();

		std::vector<Terrain::Terrain*> GetTerrainsToRender();

		void Render(Rendering::RenderModule* module, int playerID);
		void Update();
		void Tick();
	};
}