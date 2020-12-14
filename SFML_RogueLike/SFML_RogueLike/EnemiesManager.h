#pragma once
#include <vector>

#include "TimeEvent.h"
#include "Player.h"
#include "Enemy.h"
#include "Slime.h"
#include "Ghost.h"
#include "Goblin.h"

class EnemiesManager
{
public:
	EnemiesManager(Player* player);
	~EnemiesManager();

	void Update(float deltaTime);
	void CheckCollision(Entity* player);
	void Draw(sf::RenderWindow& window);

	sf::Vector2f RandomPos();

	Slime* BuildSlime(sf::Vector2f spawnPos, std::vector<TimeEvent*>* e);
	Goblin* BuildGoblin(sf::Vector2f spawnPos, std::vector<TimeEvent*>* e);
	Ghost* BuildGhost(sf::Vector2f spawnPos, std::vector<TimeEvent*>* e);

	void DamagePlayer(int damage);

private:
	std::vector<Enemy*> enemies;
	Player* player;
	sf::RectangleShape* playerBody;
};

