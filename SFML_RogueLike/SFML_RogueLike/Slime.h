#pragma once
#include "Entity.h"
#include <iostream>

class Slime : public Entity
{
public:
	Slime(std::map<std::string, Animation*> animations, sf::Vector2f spawnPosition);
	~Slime();

	void Update(float deltaTime) override;
	void OnCollision(sf::Vector2f direction);

private:

	float jumpHeight;
	float jumpRange;
	float jumpCooldown;
	float jumpCoolDownMax;
};