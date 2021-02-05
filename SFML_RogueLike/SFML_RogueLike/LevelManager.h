#pragma once
#include <functional>
#include <cmath>
#include <filesystem>

#include "Level.h"
#include "EnemiesManager.h"
#include "AnimatorController.h"
#include "ItemButton.h"
#include "ItemBuilder.h"

class LevelManager
{
public:
	LevelManager(std::function<void()> Changelevel, Player* p, EnemiesManager* e);
	~LevelManager();

	void NextLevel(LootManager* lm);
	void SwitchLevel(int index, EnemiesManager* em, LootManager* lm);
	void CenterRectangleShape(sf::Vector2f newPos);

	void UpdateButtons(sf::Vector2f mousePos);
	void DrawButtons(sf::RenderWindow& window);

	void SetEndButtons();
	void EndButtonOnClick();

	Level* GetCurrentLevel();
	ItemButton* BuildItemButton(sf::Vector2f position);

private:
	std::vector<Level*> levels;
	int activeLevelIndex;

	EnemiesManager* em;
	Player* player;
	ItemBuilder* itemBuilder;

	bool buttonBuilt = false;
	bool chooseItem = false;
	std::vector<ItemButton*> buttons;

	std::vector<sf::Texture*> CreateTiles();

	float Lerp(float a, float b, float t);
	float lerpTime;
};

