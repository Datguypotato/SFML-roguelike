#pragma once
#include <vector>

#include "Enemy.h"

class EnemiesManager
{
public:
	EnemiesManager(std::vector<Enemy> enemies);
	~EnemiesManager();

	void Update(float deltaTime);

private:
	std::vector<Enemy> enemies;

	float currTimer;
	float maxTimer;
};

