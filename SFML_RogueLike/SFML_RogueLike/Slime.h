#pragma once
#include "Enemy.h"

class Slime : public Enemy
{
public:
	Slime(std::vector<Animation*> animations, sf::Vector2f spawnPosition, sf::RectangleShape* playerBody);
	Slime(sf::Vector2f textureSize, sf::Vector2f bodySize, int health, std::vector<Animation*> animations, sf::RectangleShape* playerBody, float speed, sf::Vector2f spawnPosition);
	~Slime();
	Slime(const Slime& rhs);

	Slime* Clone() const override;
	void Update(float deltaTime) override;
	void OnCollision(sf::Vector2f direction);

	void JumpToPlayer();

	float GetJumpCooldown() { return jumpCooldown; }

protected:
	sf::Vector2f jumpDir;

	float jumpCooldown;
	float jumpCoolDownMax;

	bool isJumping;

	sf::SoundBuffer jumpSound;
};