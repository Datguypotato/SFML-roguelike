#pragma once
#include <SFML/Graphics.hpp>

#include "Collider.h"
#include "Entity.h"
#include "Enemy.h"

class Player: public Entity
{
public:
	Player(std::vector<Animation*> animations, float speed);
	Player(const Player& rhs);
	~Player();

	Player* Clone() const;

	void Update(float deltaTime) override;
	void Draw(sf::RenderWindow& window);

	Collider GetAttackBox();

private:
	sf::RectangleShape attackbox;

	std::vector<Enemy*> inRange;
};