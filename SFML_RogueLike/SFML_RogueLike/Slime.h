#pragma once
#include "Enemy.h"

class Slime : public Enemy
{
public:
	Slime(std::vector<Animation*> animations, sf::Vector2f spawnPosition, sf::RectangleShape* playerBody);
	~Slime();
	Slime(const Slime& rhs);

	Slime* Clone() const override;
	void Update(float deltaTime) override;
	void OnCollision(sf::Vector2f direction);

private:

	sf::Vector2f jumpDir;

	float jumpCooldown;
	float jumpCoolDownMax;

	bool isJumping;

	sf::SoundBuffer jumpBuffer;
};