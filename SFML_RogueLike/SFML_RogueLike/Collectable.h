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
	void Hover(float verticalSpeed, float amplitude);

	Item* GetItem();

private:
	Item* item;

	float randomStartingPoint;
	sf::Vector2f tempPos;
};

