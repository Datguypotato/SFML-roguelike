#pragma once
#include "Enemy.h"

class SlimeBase : public Enemy
{
public:
	SlimeBase(sf::Vector2f textureSize, sf::Vector2f bodySize, std::vector<Animation*> animations, Player* player, int health, int attackDamage, float speed, std::string n);

	void Update(float deltaTime) override;

	void JumpToPlayer();

protected:

	float jumpCooldown;
	bool isJumping;
	sf::Vector2f jumpDir;
};

