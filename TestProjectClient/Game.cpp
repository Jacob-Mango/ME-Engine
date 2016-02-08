#include "Game.h"



Game::Game(const char* title) : MangoesEngine(title, false) {
	m_Loading = true; 
	Loop();
}

Game::~Game() {

}

void Game::Render() {
	if (m_Loading) {
		m_RenderModule->AddModel("Resources/Models/ramp.obj");
		for (int i = 0; i < 4000 * 3; i++) {
			m_RenderModule->EndRender();
		}
		m_Network = new Network::Network("127.0.0.1", 8888);
		m_Network->Send("127.0.0.1", 8888, "00Jacob_Mango");

		char buffer[BUFLEN];
		sockaddr_in* from = new sockaddr_in();
		while (buffer[0] != '0' && buffer[1] != '0'){
			m_Network->Recieve(buffer);
			m_RenderModule->EndRender();
		}
		printf(buffer);
		std::cout << std::endl;

		m_Loading = false;
	}
	else {
		m_RenderModule->PrepareRender();

		m_RenderModule->AddModelToRender(0, glm::mat4(1.0f));

		m_RenderModule->RenderWorld();
		m_RenderModule->RenderPostProccessEffects();
		m_RenderModule->EndRender();
	}
}

void Game::Update() {
	m_Level->Update();

	float speed = 1.0f / 30.0f;
	glm::vec3 vel;
	glm::vec4 control;

	if (m_RenderModule->IsKeyPressed(GLFW_KEY_W)) {
		vel.x += speed * sin(ToRadians(m_RenderModule->GetCamera()->m_Rotation.y));
		vel.z -= speed * cos(ToRadians(m_RenderModule->GetCamera()->m_Rotation.y));
		control.z = 1;
	}
	else if (m_RenderModule->IsKeyPressed(GLFW_KEY_S)) {
		vel.x -= speed * sin(ToRadians(m_RenderModule->GetCamera()->m_Rotation.y));
		vel.z += speed * cos(ToRadians(m_RenderModule->GetCamera()->m_Rotation.y));
		control.z = -1;
	}

	if (m_RenderModule->IsKeyPressed(GLFW_KEY_A)) {
		vel.x += speed * sin(ToRadians(m_RenderModule->GetCamera()->m_Rotation.y - 90));
		vel.z -= speed * cos(ToRadians(m_RenderModule->GetCamera()->m_Rotation.y - 90));
		control.x = -1;
	}
	else if (m_RenderModule->IsKeyPressed(GLFW_KEY_D)) {
		vel.x += speed * sin(ToRadians(m_RenderModule->GetCamera()->m_Rotation.y + 90));
		vel.z -= speed * cos(ToRadians(m_RenderModule->GetCamera()->m_Rotation.y + 90));
		control.x = 1;
	}

	if (m_RenderModule->IsKeyPressed(GLFW_KEY_SPACE)) {
		vel.y += speed;
		control.y = 1;
	}
	else if (m_RenderModule->IsKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
		vel.y -= speed;
		control.y = -1;
	}

	m_RenderModule->GetCamera()->m_Position += vel;

	float sensitivity = 10.0f / 100.0f;
	glm::vec2 mousePos = m_RenderModule->GetMousePosition();
	glm::vec2 mouseMov = m_PreviousMousePosition - mousePos;

	// mouseMov.x = mouseMov.x > 0.0f ? 1.0f : mouseMov.x < 0.0f ? -1.0f : 0.0f;
	// mouseMov.y = mouseMov.y > 0.0f ? 1.0f : mouseMov.y < 0.0f ? -1.0f : 0.0f;

	m_RenderModule->GetCamera()->m_Rotation.x -= mouseMov.y * sensitivity;
	m_RenderModule->GetCamera()->m_Rotation.y -= mouseMov.x * sensitivity;

	m_PreviousMousePosition = mousePos;

	if (m_RenderModule->GetCamera()->m_Rotation.x > 90) m_RenderModule->GetCamera()->m_Rotation.x = 90;
	if (m_RenderModule->GetCamera()->m_Rotation.x < -90) m_RenderModule->GetCamera()->m_Rotation.x = -90;

	glm::vec3 rot = m_RenderModule->GetCamera()->m_Rotation;

	std::ostringstream netSend;
	netSend << "02" << control.x << "L" << control.y << "L" << control.z << "L" << control.w << "L" << rot.x << "L" << rot.y << "L" << rot.z << "";

	m_Network->Send("127.0.0.1", 8888, netSend.str().c_str());
}

void Game::Tick() {
	m_Level->Tick();
	std::cout << m_FramesPerSecond << std::endl;
}