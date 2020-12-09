#pragma once
#include <functional>
#include <cmath>

#include "Level.h"
#include "EnemiesManager.h"
#include "AnimatorController.h"

class LevelManager
{
public:
	LevelManager(std::map<int, sf::Texture*> tilset, std::vector<fs::path> paths, std::function<void()> Changelevel, Player* p, EnemiesManager* em);
	~LevelManager();

	void NextLevel();
	void SwitchLevel(int index);
	void CenterRectangleShape(sf::Vector2f newPos);

	Level* GetCurrentLevel();

private:
	std::vector<Level*> levels;
	int activeLevelIndex;
	Player* p;

	EnemiesManager* em;
	//sf::RectangleShape transitionScreen;
	//sf::Vector2f transitionScale;

	float Lerp(float a, float b, float t);
	float lerpTime;
};

