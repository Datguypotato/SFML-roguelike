#pragma once
#include <vector>

#include "Enemy.h"
#include "Slime.h"

class EnemiesManager
{
public:
	EnemiesManager(Enemy* enemy, std::vector<Entity*>* entities);
	~EnemiesManager();

	void Update(float deltaTime);

private:
	std::vector<Entity*>* entities;
	Enemy* enemy;

	float currTimer;
	float maxTimer;
};

