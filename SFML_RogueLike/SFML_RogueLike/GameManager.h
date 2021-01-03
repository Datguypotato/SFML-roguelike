#pragma once
#include <SFML/Graphics.hpp>
#include <tileson.hpp>
#include <vector>

#include "TimeEvent.h"
#include "LevelManager.h"
#include "EnemiesManager.h"
#include "Healthbar.h"
#include "Button.h"

#include "Player.h"
#include "Enemy.h"
#include "Inventory.h"
#include "Item.h"
#include "Collectable.h"

class GameManager
{
public:
	GameManager();

	void ResizeView();

	void Start();
	void Update(float deltaTime);
	void CheckCollision();
	void Draw();

	void NextLevel();

	sf::RenderWindow* GetWindow() { return window; }
	sf::View* GetView() { return view; }
	Player* GetPlayer() { return player; }

private:
	void OpenInventory();

	Player* BuildPlayer();
	std::vector<TimeEvent*> timedEvents;

	sf::View* view;
	sf::RenderWindow* window;
	float totalTime;

	LevelManager* levelmanager;
	EnemiesManager* em;

	Player* player;
	Inventory* inventory;
	Healthbar* healthbar;
	Button* bagIcon;
	std::vector<Collectable*> c;
};