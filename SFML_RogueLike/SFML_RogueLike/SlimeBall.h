#pragma once
#include "Entity.h"
#include "Player.h"

class SlimeBall : public Entity
{
public:
	SlimeBall(Player* p, std::vector<Animation*> animations, sf::Vector2f direction);


	void Update(float deltaTime) override;
	void OnCollision(sf::Vector2f direction) override { delete this; };

	void OnHit(const int damage) override;
	void OnDeath() override;

private:
	Player* player;
	sf::Vector2f direction;
};

