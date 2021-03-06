#pragma once
#include "Entity.h"
#include "Player.h"

class SlimeBall : public Entity
{
public:
	SlimeBall(std::vector<Animation*> animations, sf::Vector2f direction);
	SlimeBall(std::vector<Animation*> animations, sf::Vector2f direction, int dmg);


	void Update(float deltaTime) override;
	void OnCollision(sf::Vector2f direction) override { delete this; };

	void OnDeath() override;

private:
	sf::Vector2f direction;
};

