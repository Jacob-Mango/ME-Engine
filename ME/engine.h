#pragma once

#include <ME Engine\Rendering Module\rendering.h>

#include <ME Engine\Physics Module\physics.h>
#include <ME Engine\Level Module\level.h>

#include "timer.h"

class MangoesEngine {
private:
	bool m_CanLoop = true;
	int m_FramesPerSecond;
	int m_UpdatesPerSecond;

	Rendering::RenderModule* m_RenderModule;
	Level::Level* m_Level;
protected:
	MangoesEngine(const char* title) {
		m_RenderModule = new Rendering::RenderModule();
		m_RenderModule->CreateWindow(1280, 720, title);
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
			Render(m_RenderModule);
			frames++;
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

	virtual void Render(Rendering::RenderModule* module) {

	}

	virtual void Update() {

	}

	virtual void Tick() {

	}
};