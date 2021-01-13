#pragma once
#include <math.h>

#include "Entity.h"
#include "Item.h"

class Collectable : public Entity
{
public:
	Collectable(std::vector<Animation*> animations, sf::Vector2f pos, Item* i);

	void Update(float deltaTime) override;
	//void OnCollision(sf::Vector2f direction);
	void Hover();

	Item* GetItem();

private:
	Item* item;

	float randomStartingPoint;
	float verticalSpeed = 3.0f;
	float amplitude = 0.04f;
	sf::Vector2f tempPos;
};

