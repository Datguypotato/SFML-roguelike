#pragma once
#include "Enemy.h"
#include <iostream>

class Slime : public Enemy
{
public:
	Slime(std::map<std::string, Animation*> animations, sf::Vector2f spawnPosition, sf::RectangleShape* playerBody);
	~Slime();

	void Update(float deltaTime) override;
	void OnCollision(sf::Vector2f direction);

private:

	float jumpHeight;
	float jumpRange;
	float jumpCooldown;
	float jumpCoolDownMax;

};