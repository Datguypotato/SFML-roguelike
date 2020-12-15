#pragma once
#include <SFML/Graphics.hpp>

#include "Collider.h"
#include "Entity.h"

class Player: public Entity
{
public:
	Player(std::vector<Animation*> animations, float speed, int attackDamage);
	Player(const Player& rhs);
	~Player();

	Player* Clone() const;

	void Update(float deltaTime) override;
	void Draw(sf::RenderWindow& window);

	Collider GetAttackBox();

private:
	sf::RectangleShape attackbox;

	std::vector<Entity*> inRange;
};