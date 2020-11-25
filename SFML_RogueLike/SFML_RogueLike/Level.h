#pragma once
#include "tileson.hpp"
#include <SFML/Graphics.hpp>

#include <Ground.h>
#include <Wall.h>
#include <LevelSwitcher.h>

class Level
{
public:
	Level(std::map<int, sf::Texture*> tileSet, fs::path levelPath);
	~Level();

	void Load();
	void Draw(sf::RenderWindow& window);

	void CheckCollision(Collider playerCollider);
	void CheckTrigger(Collider playerCollider);

private:
	std::unique_ptr<tson::Map> map;
	std::map<int, sf::Texture*> tileSet;
	fs::path levelPath;

	std::vector<Ground> floor;
	std::vector<Wall> walls;
	std::vector<LevelSwitcher> doors;
};

