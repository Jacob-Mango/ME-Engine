#include "Game.h"

#include <iostream>
#include <math.h>

Game::Game(const char* title) : MangoesEngine(title) {
	m_Loading = true; 
	Loop();
}

Game::~Game() {

}

void Game::Render(Rendering::RenderModule *module) {
	if (m_Loading) {
		module->AddModel("Resources/Models/ramp.obj");
		m_Loading = false;
	} else {
		module->PrepareRender();

		module->AddModelToRender(0, glm::mat4(0.0f));

		module->RenderWorld();
		module->RenderPostProccessEffects();
		module->EndRender();
	}
}

void Game::Update(Level::Level* level, Rendering::RenderModule* module) {
	float speed = 1.0f / 30.0f;
	glm::vec3 vel;

	if (module->IsKeyPressed(GLFW_KEY_W)) {
		vel.x += speed * sin(ToRadians(module->GetCamera()->m_Rotation.y));
		vel.z -= speed * cos(ToRadians(module->GetCamera()->m_Rotation.y));
	}
	else if (module->IsKeyPressed(GLFW_KEY_S)) {
		vel.x -= speed * sin(ToRadians(module->GetCamera()->m_Rotation.y));
		vel.z += speed * cos(ToRadians(module->GetCamera()->m_Rotation.y));
	}

	if (module->IsKeyPressed(GLFW_KEY_A)) {
		vel.x += speed * sin(ToRadians(module->GetCamera()->m_Rotation.y - 90));
		vel.z -= speed * cos(ToRadians(module->GetCamera()->m_Rotation.y - 90));
	}
	else if (module->IsKeyPressed(GLFW_KEY_D)) {
		vel.x += speed * sin(ToRadians(module->GetCamera()->m_Rotation.y + 90));
		vel.z -= speed * cos(ToRadians(module->GetCamera()->m_Rotation.y + 90));
	}

	if (module->IsKeyPressed(GLFW_KEY_SPACE)) {
		vel.y += speed;
	}
	else if (module->IsKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
		vel.y -= speed;
	}

	module->GetCamera()->m_Position += vel;

	float sensitivity = 50.0f / 100.0f;

	glm::vec2 mouseMov = module->GetMouseDelta();
	mouseMov.x = mouseMov.x > 0 ? 1 : mouseMov.x < 0 ? -1 : 0;
	mouseMov.y = mouseMov.y > 0 ? 1 : mouseMov.y < 0 ? -1 : 0;

	module->GetCamera()->m_Rotation.x -= mouseMov.y * sensitivity;
	module->GetCamera()->m_Rotation.y -= mouseMov.x * sensitivity;

	if (module->GetCamera()->m_Rotation.x > 90) module->GetCamera()->m_Rotation.x = 90;
	if (module->GetCamera()->m_Rotation.x < -90) module->GetCamera()->m_Rotation.x = -90;

	
}

void Game::Tick() {
	std::cout << m_FramesPerSecond << std::endl;
}