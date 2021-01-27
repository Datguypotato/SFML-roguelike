#pragma once
#include <functional>
#include <cmath>
#include <filesystem>

#include "Level.h"
#include "EnemiesManager.h"
#include "AnimatorController.h"

class LevelManager
{
public:
	LevelManager(std::function<void()> Changelevel, Player* p);
	~LevelManager();

	void NextLevel(EnemiesManager* em, LootManager* lm);
	void SwitchLevel(int index, EnemiesManager* em, LootManager* lm);
	void CenterRectangleShape(sf::Vector2f newPos);

	Level* GetCurrentLevel();

private:
	std::vector<Level*> levels;
	int activeLevelIndex;
	Player* p;

	std::vector<sf::Texture*> CreateTiles();

	float Lerp(float a, float b, float t);
	float lerpTime;
};

