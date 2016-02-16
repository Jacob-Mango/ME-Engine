#include "GUI.h"

namespace Rendering {

		GUI::~GUI() {
		}

		void GUI::Update() {
			for (unsigned int i = 0; i < m_GUIItems.size(); i++) {
				if (m_GUIItems[i]->m_Type == GUI_PANEL) {

				}
				else if (m_GUIItems[i]->m_Type == GUI_IMAGE) {

				}
				else if (m_GUIItems[i]->m_Type == GUI_BUTTON) {

				}
				else if (m_GUIItems[i]->m_Type == GUI_TEXTBOX) {

				} 
				m_GUIItems[i]->Update();
			}
		}
	
}