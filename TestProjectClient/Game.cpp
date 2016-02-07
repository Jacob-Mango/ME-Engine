#include "Game.h"

#include <iostream>
#include <math.h>

Game::Game(const char* title) : MangoesEngine(title) {
	m_Loading = true; 
	Loop();
}

Game::~Game() {

}

void Game::Render() {
	if (m_Loading) {
		m_RenderModule->AddModel("Resources/Models/cube.obj");
		m_Loading = false;
	} else {
		m_RenderModule->PrepareRender();

		m_RenderModule->AddModelToRender(0, glm::mat4(1.0f));

		m_RenderModule->RenderWorld();
		m_RenderModule->RenderPostProccessEffects();
		m_RenderModule->EndRender();
	}
}

void Game::Update() {
	float speed = 1.0f / 30.0f;
	glm::vec3 vel;

	if (m_RenderModule->IsKeyPressed(GLFW_KEY_W)) {
		vel.x += speed * sin(ToRadians(m_RenderModule->GetCamera()->m_Rotation.y));
		vel.z -= speed * cos(ToRadians(m_RenderModule->GetCamera()->m_Rotation.y));
	}
	else if (m_RenderModule->IsKeyPressed(GLFW_KEY_S)) {
		vel.x -= speed * sin(ToRadians(m_RenderModule->GetCamera()->m_Rotation.y));
		vel.z += speed * cos(ToRadians(m_RenderModule->GetCamera()->m_Rotation.y));
	}

	if (m_RenderModule->IsKeyPressed(GLFW_KEY_A)) {
		vel.x += speed * sin(ToRadians(m_RenderModule->GetCamera()->m_Rotation.y - 90));
		vel.z -= speed * cos(ToRadians(m_RenderModule->GetCamera()->m_Rotation.y - 90));
	}
	else if (m_RenderModule->IsKeyPressed(GLFW_KEY_D)) {
		vel.x += speed * sin(ToRadians(m_RenderModule->GetCamera()->m_Rotation.y + 90));
		vel.z -= speed * cos(ToRadians(m_RenderModule->GetCamera()->m_Rotation.y + 90));
	}

	if (m_RenderModule->IsKeyPressed(GLFW_KEY_SPACE)) {
		vel.y += speed;
	}
	else if (m_RenderModule->IsKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
		vel.y -= speed;
	}

	m_RenderModule->GetCamera()->m_Position += vel;

	float sensitivity = 50.0f / 100.0f;

	glm::vec2 mouseMov = m_RenderModule->GetMouseDelta();
	mouseMov.x = mouseMov.x > 0.0f ? 1.0f : mouseMov.x < 0.0f ? -1.0f : 0.0f;
	mouseMov.y = mouseMov.y > 0.0f ? 1.0f : mouseMov.y < 0.0f ? -1.0f : 0.0f;

	m_RenderModule->GetCamera()->m_Rotation.x -= mouseMov.y * sensitivity;
	m_RenderModule->GetCamera()->m_Rotation.y -= mouseMov.x * sensitivity;

	if (m_RenderModule->GetCamera()->m_Rotation.x > 90) m_RenderModule->GetCamera()->m_Rotation.x = 90;
	if (m_RenderModule->GetCamera()->m_Rotation.x < -90) m_RenderModule->GetCamera()->m_Rotation.x = -90;

	
}

void Game::Tick() {
	std::cout << m_FramesPerSecond << std::endl;
}