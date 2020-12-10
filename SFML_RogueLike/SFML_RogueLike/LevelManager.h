#pragma once
#include <functional>
#include <cmath>

#include "Level.h"
#include "EnemiesManager.h"
#include "AnimatorController.h"

class LevelManager
{
public:
	LevelManager(std::function<void()> Changelevel, Player* p);
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
	std::map<int, sf::Texture*>* CreateTiles();
	//sf::RectangleShape transitionScreen;
	//sf::Vector2f transitionScale;

	float Lerp(float a, float b, float t);
	float lerpTime;
};

