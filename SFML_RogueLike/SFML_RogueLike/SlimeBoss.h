#pragma once
#include "Enemy.h"
#include "Slime.h"

enum class AttackPattern
{
	Projectile,
	Jump,
	Bite,
	Move
};

class SlimeBoss : public Slime
{
public:
	SlimeBoss(std::vector<Animation*> animations, sf::Vector2f spawnPosition, sf::RectangleShape* playerBody);

	void Update(float deltaTime);

private:
	AttackPattern activePattern;
};

