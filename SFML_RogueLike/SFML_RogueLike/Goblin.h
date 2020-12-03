#pragma once
#include "Enemy.h"

class Goblin : public Enemy
{
public:
	Goblin(std::vector<Animation*> animations, sf::Vector2f spawnPosition, sf::RectangleShape* playerbody);
	~Goblin();

	void Update(float deltaTime) override;

private:

	float windupAttackTime;
	float attackRange;
	bool isAttacking;
};

