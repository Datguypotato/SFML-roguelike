#pragma once
#include <vector>

#include "SlimeBase.h"
#include "SlimeBall.h"

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

	void Draw(sf::RenderWindow& window) override;
	std::vector<SlimeBall*> GetProjectiles() { return projectiles; }

private:
	void SwitchPattern();
	void Bite();
	void Shoot();

	SlimeBall* BuildSlimeBall(sf::Vector2f startPos);

	std::vector<SlimeBall*> projectiles;
	float jumpCooldown;
	float jumpSpeed;
	float bigJumpCoolDown;
	float bigJumpSpeed;
	bool isJumping;
	sf::Vector2f jumpDir;

	float patternTime;

	AttackPattern activePattern;
};