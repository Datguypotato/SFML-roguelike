#pragma once
#include <vector>

#include "TimeEvent.h"
#include "Player.h"
#include "Enemy.h"
#include "Slime.h"
#include "Ghost.h"
#include "Goblin.h"
#include "SlimeBoss.h"
#include "SlimeBall.h"

enum class EnemyType
{
	Ghost,
	Goblin,
	Slime,
	SlimeBoss
};
struct SpawnData
{
	SpawnData(EnemyType et, float t, sf::Vector2f pos)
	{
		spawnPos = pos;
		type = et;
		time = t;
	}

	sf::Vector2f spawnPos;
	EnemyType type;
	float time;
};
class EnemiesManager
{

public:
	EnemiesManager(Player* player);
	~EnemiesManager();

	void Update(float deltaTime);
	void CheckCollision(Entity* player);
	void Draw(sf::RenderWindow& window);

	sf::Vector2f RandomPos();

	Slime* BuildSlime(sf::Vector2f spawnPos);
	Goblin* BuildGoblin(sf::Vector2f spawnPos);
	Ghost* BuildGhost(sf::Vector2f spawnPos);
	SlimeBoss* BuildSlimeBoss(sf::Vector2f spawnPos);

	std::vector<Enemy*> GetEnemies() { return enemies; }
	void AddEnemyData(EnemyType et, float time, sf::Vector2f pos);

private:
	std::vector<Animation*> LoadSlimeAnimation();
	std::vector<TimeEvent*> timedEvents;

	std::vector<SpawnData*> enemiesData;
	std::vector<Enemy*> enemies;
	SlimeBoss* boss;
	Player* player;
	sf::RectangleShape* playerBody;
};

