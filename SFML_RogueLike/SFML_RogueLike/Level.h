#pragma once
#include <tileson.hpp>
#include <SFML/Graphics.hpp>

#include "Ground.h"
#include "Wall.h"
#include "LevelSwitcher.h"
#include "LevelSign.h"
#include "Player.h"
#include "EnemiesManager.h"
#include "LootManager.h"
#include "ShopKeeper.h"

class Level
{
public:
	Level(std::vector<sf::Texture*> tileSet, fs::path levelPath);
	Level(std::vector<sf::Texture*> tileSet, fs::path levelPath, std::function<void()> Changelevel);
	~Level();

	void Load(Player* p, EnemiesManager* em, LootManager* lm);
	void Unload();

	void UpdateShopkeeper(float deltaTime, sf::Vector2f mousePos, sf::Vector2f playerPos);
	void Draw(sf::RenderWindow& window);
	void LateDraw(sf::RenderWindow& window);

	void CheckCollision(Collider playerCollider);
	void CheckTrigger(Collider playerCollider, EnemiesManager em);

	bool isDoneLoading() { return doneLoading; }
	bool isStartLoading() { return startLoading; }

private:
	std::vector<std::string> CreateTextSigns();

	std::unique_ptr<tson::Map> map;
	std::vector<sf::Texture*> tileSet;
	fs::path levelPath;
	bool doneLoading;
	bool startLoading;

	std::vector<Ground> floors;
	std::vector<Wall> walls;
	std::vector<Wall> invisibleWalls;
	std::vector<LevelSwitcher> doors;
	std::vector<LevelSign*> interactables;
	std::vector<std::string> textSigns;
	ShopKeeper* shopkeeper;

	std::function<void()> Changelevel;
};

