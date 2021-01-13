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

	void OnHit(const int damage) override;
	void OnDeath() override;

	sf::Vector2f GetSize() { return size; }
	void SetSize(sf::Vector2f v);

private:
	sf::Vector2f direction;
	sf::Vector2f size;
};

