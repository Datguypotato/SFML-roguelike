#pragma once
#include "functional"

#include "Level.h"

class LevelManager
{
public:
	LevelManager(std::map<int, sf::Texture*> tilset, std::vector<fs::path> paths, std::function<void()> Changelevel);
	~LevelManager();

	void NextLevel();
	void SwitchLevel(int index);

	Level* GetCurrentLevel();

private:
	std::vector<Level*> levels;
	int activeLevelIndex;
};

