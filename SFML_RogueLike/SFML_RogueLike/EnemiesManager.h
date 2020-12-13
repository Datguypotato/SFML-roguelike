#pragma once
#include <vector>

#include "Enemy.h"
#include "Slime.h"
#include "Ghost.h"
#include "Goblin.h"

class EnemiesManager
{
public:
	EnemiesManager(sf::RectangleShape* playerBody);
	~EnemiesManager();

	sf::Vector2f RandomPos();

	Slime* BuildSlime(sf::Vector2f spawnPos);
	Goblin* BuildGoblin(sf::Vector2f spawnPos);
	Ghost* BuildGhost(sf::Vector2f spawnPos);


private:
	sf::RectangleShape* playerBody;

	float currTimer;
	float maxTimer;
};

