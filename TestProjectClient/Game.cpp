#include "Game.h"

Game::Game(const char* title) : MangoesEngine(title, false) {
	m_Loading = true; 
	m_WaitingForLogin = false;
	Loop();
}

Game::~Game() {

}

void Game::Render() {
	m_RenderModule->PrepareRender();
	if (m_Loading) {
		const char* username = "dadafafgg";
		if (m_WaitingForLogin) {
			char buffer[BUFLEN];
			sockaddr_in from = m_Network->Recieve(buffer);

			std::string recv(buffer);

			if (!recv.compare(0, 2, "00")) {
				m_MainPlayerID = atoi(std::string(buffer).substr(2, 6).c_str());
				m_Level->AddPlayer(new Player(username, m_MainPlayerID));
				m_Packet = new Network::Packet(m_Network, m_Level);
				m_WaitingForLogin = false;
				m_Loading = false;
			}

		} else if (!m_WaitingForLogin) {
			int i = 0;
			while (i < 4000 * 100) {
				i++;
			}
			ResourceLoader rl;

			while (rl.LoadModels(m_RenderModule) == false) {
				m_RenderModule->PrepareRender();
				m_RenderModule->RenderWorld(m_Level->GetTerrainsToRender());
				m_RenderModule->RenderPostProccessEffects();
				m_RenderModule->EndRender();
			}

			while (rl.LoadLevel(m_Level) == false) {
				m_RenderModule->PrepareRender();
				m_RenderModule->RenderWorld(m_Level->GetTerrainsToRender());
				m_RenderModule->RenderPostProccessEffects();
				m_RenderModule->EndRender();
			}

			std::cout << "Ok, connecting!";
			m_Network = new Network::Network(false);

			std::ostringstream c;
			c << "00";
			c << "000000";
			c << username;

			std::cout << c.str();

			m_Network->Send("127.0.0.1", SERVERPORT, c.str().c_str());
			m_WaitingForLogin = true;
		}
	} else {
		m_Level->Render(m_RenderModule, m_MainPlayerID);
	}

	m_RenderModule->RenderWorld(m_Level->GetTerrainsToRender());
	m_RenderModule->RenderPostProccessEffects();
	m_RenderModule->EndRender();
	
}

void Game::Update() {
	if (m_WaitingForLogin == false && m_Loading == false) {
		if (m_RenderModule->IsKeyPressed(GLFW_KEY_ESCAPE)) m_RenderModule->SetCursor(!m_RenderModule->IsCursorFocused());

		float speed = 1.0f / 30.0f;
		glm::vec3 vel;
		glm::vec4 control;
		if (!m_RenderModule->IsCursorFocused()) {
			if (m_RenderModule->IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
				speed = 5.0f;
				control.w = 1;
			}


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

			m_RenderModule->GetCamera()->m_Rotation.x -= mouseMov.y * sensitivity;
			m_RenderModule->GetCamera()->m_Rotation.y -= mouseMov.x * sensitivity;

			m_PreviousMousePosition = mousePos;

			if (m_RenderModule->GetCamera()->m_Rotation.x > 90) m_RenderModule->GetCamera()->m_Rotation.x = 90;
			if (m_RenderModule->GetCamera()->m_Rotation.x < -90) m_RenderModule->GetCamera()->m_Rotation.x = -90;



		}

		glm::vec3 rot = m_RenderModule->GetCamera()->m_Rotation;

		m_Level->GetPlayerForID(m_MainPlayerID)->SetVelocity(vel);
		m_Level->GetPlayerForID(m_MainPlayerID)->SetRotation(glm::vec3(rot.x, 180 - rot.y, rot.z));

		std::ostringstream netSend;
		netSend << "02";

		std::ostringstream check;
		check << m_MainPlayerID << "";
		int x = 6;
		while (x - check.str().length() > 0) {
			netSend << "0";
			x--;
		}
		netSend << m_MainPlayerID;

		netSend << ((control.x < 0) ? "" : "0") << control.x << "L" << ((control.y < 0) ? "" : "0") << control.y << "L" << ((control.z < 0) ? "" : "0") << control.z << "L" << control.w << "L" << rot.x << "L" << rot.y << "L" << rot.z << "";

		m_Network->Send("127.0.0.1", SERVERPORT, netSend.str().c_str());
		m_Level->Update();
	}
}

void Game::Tick() {
	m_Level->Tick();
	std::cout << std::endl << m_FramesPerSecond << std::endl;
}