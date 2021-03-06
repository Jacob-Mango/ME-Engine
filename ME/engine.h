#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "Rendering\Rendering.h"

#include "Level\Level.h"
#include "Network\Network.h"
#include "Network\Packet.h"

#include "Utils\Timer.h"

class MangoesEngine {
protected:
	bool m_CanLoop = true;
	int m_FramesPerSecond;
	int m_UpdatesPerSecond;
	Rendering::RenderModule* m_RenderModule;
	Level::Level* m_Level;

	bool m_IsServer;
	Network::Network* m_Network;
	Network::Packet* m_Packet;
protected:
	MangoesEngine(const char* title, bool isServer) {
		m_IsServer = isServer;
		if (m_IsServer == false) {
			m_RenderModule = new Rendering::RenderModule();
			int e = m_RenderModule->MakeWindow(1280, 720, title);
			printf("What is it? %d\n", e);
			if (e != 0) {
				exit(e);
			}
			m_Level = new Level::Level();
		} else {
			m_Level = new Level::Level();
			m_Network = new Network::Network(true);
			m_Packet = new Network::Packet(m_Network, m_Level);
		}
	}

	void Loop() {
		utils::Timer timer = utils::Timer();
		float t = 0.0f;
		float updateTimer = 0.0f;
		float updateTick = 1.0f / 30.0f;

		float delta = 1.0f;

		unsigned int frames = 0;
		unsigned int updates = 0;

		while (m_CanLoop) {
			if (m_IsServer == false) {
				m_CanLoop = m_RenderModule->ShouldClose() == false;
			}			
			
			if (timer.elapsed() - updateTimer > updateTick) {
				updates++;
				updateTimer += updateTick;
				Update(delta);
			}

			if (m_IsServer == false) {
				Render();
				frames++;
			}

			if (timer.elapsed() - t > 1.0f) {
				t += 1.0f;
				m_FramesPerSecond = frames;
				m_UpdatesPerSecond = updates;
				frames = 0;
				updates = 0;
				Tick();
			}
		}
	}

	virtual void Render() {}
	virtual void Update(float delta) {}
	virtual void Tick() {}
};