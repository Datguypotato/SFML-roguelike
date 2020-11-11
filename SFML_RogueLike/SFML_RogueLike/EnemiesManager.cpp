#include "EnemiesManager.h"

EnemiesManager::EnemiesManager(std::vector<Enemy> enemies)
	:	currTimer(0.0f),
		maxTimer(3.0f)
{
	this->enemies = enemies;
}

EnemiesManager::~EnemiesManager()
{
}

void EnemiesManager::Update(float deltaTime)
{
	currTimer -= deltaTime;

	if (currTimer <= 0.0f)
	{
		currTimer = maxTimer - currTimer;


	}
}
