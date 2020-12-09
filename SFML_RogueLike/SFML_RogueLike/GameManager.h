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
	GameManager(sf::View view, Player p, LevelManager lm);
	~GameManager();

	void ResizeView(const sf::RenderWindow& window, sf::View& view);

	void Update(float deltaTime);
	void CheckCollision();
	void Draw();

	sf::RenderWindow* GetWindow() { return window; }
	Player GetPlayer() { return player; }

private:
	sf::View view;
	sf::RenderWindow* window;
	float totalTime;

	std::vector<fs::path> paths;
	LevelManager levelmanager;

	Player player;
	std::vector<Enemy> enemies;
};