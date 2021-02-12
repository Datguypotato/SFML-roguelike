#pragma once
#include "SlimeBase.h"

class Slime : public SlimeBase
{
public:
	Slime(std::vector<Animation*> animations, sf::Vector2f spawnPosition, Player* player);
	Slime(sf::Vector2f textureSize, sf::Vector2f bodySize, int health, std::vector<Animation*> animations, Player* player, float speed, sf::Vector2f spawnPosition);
	~Slime();
	Slime(const Slime& rhs);

	void Update(float deltaTime) override;
	void OnCollision(sf::Vector2f direction);

	float GetJumpCooldown() { return jumpCooldown; }

protected:
	sf::Vector2f jumpDir;

	float jumpCooldown;
	float jumpCoolDownMax;

	bool isJumping;


};