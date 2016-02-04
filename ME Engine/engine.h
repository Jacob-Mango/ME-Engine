#pragma once

#define USE_WINDOWS

#include <rendering.h>
#include <physics.h>
#include <level.h>

#include "timer.h"

class MangoesEngine {
private:
	bool m_CanLoop = true;
	int m_FramesPerSecond;
	int m_UpdatesPerSecond;

	Rendering::RenderModule* m_RenderModule;
	Level::Level* m_Level;
protected:
	MangoesEngine() {
		m_RenderModule = new Rendering::RenderModule();
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

	virtual void Render(Rendering::RenderModule *module);
	virtual void Update();
	virtual void Tick();
};