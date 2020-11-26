#include "LevelManager.h"

LevelManager::LevelManager(std::map<int, sf::Texture*> tileset, std::vector<fs::path> paths, std::function<void()> Changelevel, Player* p)
	:	activeLevelIndex(0)
{
	this->p = p;
	levels = std::vector<Level*>();
	for (auto path : paths)
	{
		levels.push_back(new Level(tileset, path, Changelevel));
	}
}

LevelManager::~LevelManager()
{
}

void LevelManager::NextLevel()
{
	LevelManager::SwitchLevel(activeLevelIndex + 1);
}

void LevelManager::SwitchLevel(int index)
{
	levels[activeLevelIndex]->Unload();
	activeLevelIndex++;
	levels[index]->Load(p);
}

Level* LevelManager::GetCurrentLevel()
{
	return levels[activeLevelIndex];
}
