#pragma once
#include <vector>

#include "Enemy.h"
#include "Slime.h"

class EnemiesManager
{
public:
	EnemiesManager(sf::RectangleShape* playerBody, std::vector<Entity*>* entities);
	~EnemiesManager();

	void Update(float deltaTime);
	Slime* BuildSlime(sf::Vector2f spawnPos);

private:
	std::vector<Entity*>* entities;
	sf::RectangleShape* playerBody;

	float currTimer;
	float maxTimer;
};

