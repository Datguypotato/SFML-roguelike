#pragma once
#include <SFML/Graphics.hpp>
#include <tileson.hpp>
#include <vector>

#include "Player.h"
#include "Enemy.h"

#include "Level.h"
#include "LevelManager.h"

class GameManager
{
public:
	static GameManager* GetInstance();

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
	GameManager();
	~GameManager();
	static GameManager* instance;

	Player* BuildPlayer();

	sf::View* view;
	sf::RenderWindow* window;
	float totalTime;

	std::vector<fs::path> paths;
	LevelManager* levelmanager;

	Player* player;
	std::vector<Enemy> enemies;
};