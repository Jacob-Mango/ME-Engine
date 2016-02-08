#pragma once

#include "Rendering\Rendering.h"

#include "Physics\Physics.h"
#include "Level\Level.h"
#include "Network\Network.h"

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
protected:
	MangoesEngine(const char* title, bool isServer) {
		m_IsServer = isServer;
		if (m_IsServer == false) {
			m_RenderModule = new Rendering::RenderModule();
			int e = m_RenderModule->MakeWindow(1280, 720, title);
			if (e != 0) {
				exit(e);
			}
		} else {
			m_Network = new Network::Network(8888);
		}
		m_Level = new Level::Level();
	}

	void Loop() {
		utils::Timer timer = utils::Timer();
		float t = 0.0f;
		float updateTimer = 0.0f;
		float updateTick = 1.0f / 30.0f;
		unsigned int frames = 0;
		unsigned int updates = 0;
		while (m_CanLoop) {
			if (timer.elapsed() - updateTimer > updateTick) {
				updates++;
				updateTimer += updateTick;
				Update();
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

	virtual void Render() {
	}

	virtual void Update() {
	}

	virtual void Tick() {
	}
};