#pragma once
#include "SlimeBase.h"

enum class AttackPattern
{
	Move = 0,
	Projectile = 1,
	Jump = 2,
	Bite = 3,
};

class SlimeBoss : public SlimeBase
{
public:
	SlimeBoss(std::vector<Animation*> animations, sf::Vector2f spawnPosition, Player* player);

	void Update(float deltaTime);
	void OnHit(const int damage) override;
private:
	void SwitchPattern();

	float jumpCooldown;
	bool isJumping;
	sf::Vector2f jumpDir;

	float patternTime;

	AttackPattern activePattern;
};

