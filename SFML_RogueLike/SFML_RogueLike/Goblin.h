#pragma once
#include "Enemy.h"

class Goblin : public Enemy
{
public:
	Goblin(std::vector<Animation*> animations, sf::Vector2f spawnPosition, Player* player);
	~Goblin();

	void Update(float deltaTime) override;
	void Action();
	void Attack();

	void Draw(sf::RenderWindow& window) override;

private:

	float windupAttackTime;
	float attackRange;
	bool isAttacking;
};

