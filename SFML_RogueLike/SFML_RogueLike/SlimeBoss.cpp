#include "SlimeBoss.h"

SlimeBoss::SlimeBoss(std::vector<Animation*> animations, sf::Vector2f spawnPosition, sf::RectangleShape* playerBody)
	:	Slime(sf::Vector2f(250, 250), sf::Vector2f(200,200), 200, animations, playerBody, 50, spawnPosition)
{
	isAlive = true;
	jumpCoolDownMax = 0.5f;
	jumpCooldown = jumpCoolDownMax;
	isJumping = false;
	jumpDir = sf::Vector2f();
	activePattern = AttackPattern::Move;
}

void SlimeBoss::Update(float deltaTime)
{
	Slime::Update(deltaTime);
}