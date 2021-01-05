#pragma once
#include <tileson.hpp>
#include <SFML/Graphics.hpp>

#include "Ground.h"
#include "Wall.h"
#include "LevelSwitcher.h"
#include "Player.h"
#include "EnemiesManager.h"

class Level
{
public:
	Level(std::map<int, sf::Texture*>* tileSet, fs::path levelPath);
	Level(std::map<int, sf::Texture*>* tileSet, fs::path levelPath, std::function<void()> Changelevel);
	~Level();

	void Load(Player* p, EnemiesManager* em);
	void Unload();
	void Draw(sf::RenderWindow& window);

	void CheckCollision(Collider playerCollider);
	void CheckTrigger(Collider playerCollider);

	bool isDoneLoading() { return doneLoading; }
	bool isStartLoading() { return startLoading; }

private:
	std::unique_ptr<tson::Map> map;
	std::map<int, sf::Texture*>* tileSet;
	fs::path levelPath;
	bool doneLoading;
	bool startLoading;

	

	std::vector<Ground> floors;
	std::vector<Wall> walls;
	std::vector<LevelSwitcher> doors;

	std::function<void()> Changelevel;
};

