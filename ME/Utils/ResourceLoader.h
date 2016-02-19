#pragma once

#include <string>
#include <sstream>

#include <tchar.h>

#include "..\Rendering\Rendering.h"
#include "..\Rendering\Model.h"

class ResourceLoader {
private:
int m_LoadModelNumber = 0;
int m_MaxModels = -1;

int m_LoadLevelNumber = 0;
int m_MaxLevels = -1;

int CheckHowManyModelsToLoad() {
	const TCHAR* parent_path = (const TCHAR*) "Resources\\Data\\";
	size_t len = _tcslen(parent_path);
	const size_t alloc_len = len + 3;
	TCHAR* sub_wild = new TCHAR[alloc_len];
	_tcscpy_s(sub_wild, alloc_len, parent_path);
	if (len && sub_wild[len - 1] != _T('\\')) { sub_wild[len++] = _T('\\'); }
	sub_wild[len++] = _T('*');
	sub_wild[len++] = _T('\0');

	WIN32_FIND_DATA fd;
	HANDLE hfind;
	int count = 0;
	if (INVALID_HANDLE_VALUE != (hfind = FindFirstFile(sub_wild, &fd))) {
		do {
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				const bool is_alias_dir = fd.cFileName[0] == _T('.') &&
					(!fd.cFileName[1] || (fd.cFileName[1] == _T('.') &&
					!fd.cFileName[2]));

				count += !is_alias_dir;
			}
		} while (FindNextFile(hfind, &fd));
		FindClose(hfind);
	}

	delete[] sub_wild;

	return count;
}
public:
bool LoadModels(Rendering::RenderModule* module) {
	if (m_MaxModels < 0) m_MaxModels = 2;// CheckHowManyModelsToLoad();

	std::ostringstream o;
	o << "Resources\\Data\\" << m_LoadModelNumber << "\\" << m_LoadModelNumber << ".obj";
	module->AddModel(o.str().c_str());

	std::ostringstream t;
	t << "Resources\\Data\\" << m_LoadModelNumber << "\\" << m_LoadModelNumber << ".png";
	module->AddTexture(t.str().c_str());

	// std::ostringstream d;
	// d << "Resources\\Data\\" << m_LoadModelNumber << "\\" << m_LoadModelNumber << ".dae";
	// module->AddModel(d.str().c_str());

	m_LoadModelNumber++;

	if (m_LoadModelNumber >= m_MaxModels) return true;
	else return false;
}

bool LoadLevel(Level::Level* level) {
	level->AddEntity(new Entity(glm::vec3(10, 0, 10), glm::vec3(0, 0, 0), 1, 0, true, 0.0f));

	return true;
}
};