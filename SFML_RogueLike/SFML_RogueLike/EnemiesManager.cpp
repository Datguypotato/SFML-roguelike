#include "EnemiesManager.h"

EnemiesManager::EnemiesManager(Enemy* enemy, std::vector<Entity*>* entities)
	:	currTimer(0.0f),
		maxTimer(6.0f)
{
	//this->enemies = enemies;
	this->enemy = enemy;
	this->entities = entities;
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

		float randomX = 1 + (rand() % 200);
		float randomY = 1 + (rand() % 200);

		entities->push_back(enemy->Clone());
	}
}
