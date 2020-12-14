#pragma once
#include <SFML/Graphics.hpp>
#include <tileson.hpp>
#include <vector>

#include "TimeEvent.h"
#include "LevelManager.h"
#include "EnemiesManager.h"

#include "Player.h"
#include "Enemy.h"

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

	void AddEvent(std::function<void()> callback, float interval);

private:
	Player* BuildPlayer();
	std::vector<TimeEvent*> timedEvents;

	sf::View* view;
	sf::RenderWindow* window;
	float totalTime;

	std::vector<fs::path> paths;
	LevelManager* levelmanager;
	EnemiesManager* em;

	Player* player;
};